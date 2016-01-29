/*
 * GHMS.cpp
 *
 * Created: 24-Feb-14 11:40:37 AM
 *  Author: Ameya
 */ 


#define F_CPU 1000000 // AVR clock frequency in Hz, used by util/delay.h
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#define dataport PORTC
#define rs 0
#define rw 1
#define en 2
#define sbit(reg,bit)	reg |= (1<<bit)
#define cbit(reg,bit)	reg &= ~(1<<bit)

void lcd_pow(int pow[])//lcd power up
{
	int i;
	 _delay_ms(16);
	for(i=0;i<4;i++)
	{
		cbit(PORTC,rs);
		cbit(PORTC,rw);
		sbit(PORTC,en);
		dataport=(pow[i]|0x04)&0xfc;
		 _delay_us(1);
		cbit(PORTC,en);
		if(i==0)
		_delay_ms(4.2);
		else
		_delay_us(150);
	}
}

void lcd_cmd(int cmd[])//lcd initialization
{
	int i;
	for(i=0;i<4;i++)
	{
		int temp;
		cbit(PORTC,rs);
		cbit(PORTC,rw);
		sbit(PORTC,en);
		dataport=(cmd[i]|0x04)&0xfc;
		_delay_us(1);
		cbit(PORTC,en);
		temp=cmd[i] & 0x0f;
		temp=temp<<4;
		sbit(PORTC,en);
		dataport=(temp|0x04)&0xfc;
		_delay_us(1);
		cbit(PORTC,en);
		if(i==3)
		_delay_ms(1.7);
		else
		_delay_us(150);
	}
}

void lcd_cmd(int cmd)//used for sending ddram addresses
{
	int temp;
	cbit(PORTC,rs);
	cbit(PORTC,rw);
	sbit(PORTC,en);
	dataport=(cmd|0x04)&0xfc;
	_delay_us(1);
	cbit(PORTC,en);
	temp=cmd & 0x0f;
	temp=temp<<4;
	sbit(PORTC,en);
	dataport=(temp|0x04)&0xfc;
	_delay_us(1);
	cbit(PORTC,en);
	if(cmd==0x01)
	_delay_ms(1.7);
	else
	_delay_us(150);
}

void lcd_msg(char msg[])//display data
{
	char temp;
	int i=0;
	while(msg[i]!='$')
	{
		sbit(PORTC,rs);
		cbit(PORTC,rw);
		sbit(PORTC,en);
		dataport=(msg[i]|0x05)&0xfd;
		_delay_us(1);
		cbit(PORTC,en);
		temp=msg[i]&0x0f;
		temp=temp<<4;
		sbit(PORTC,en);
		dataport=(temp|0x05)&0xfd;
		_delay_us(1);
		cbit(PORTC,en);
		_delay_us(150);
		i++;
	}
}

double format(double t)
{
	double t1;
	int t2,t3;
	char temp[5];
	t2=t;
	t1=t-t2;
	t3=t1*100;
	temp[0]=48+(t2/10);//48 is used to generate ascii code for nos 0-9
	temp[1]=48+(t2%10);
	temp[2]='.';
	temp[3]=48+(t3/10);
	temp[4]=48+(t3%10);
	temp[5]='$';
	lcd_msg(temp);
	return t;
}

double output(double p,char sel)
{
	double t;
	switch(sel)
	{
		case 't':ADMUX=0x00;
		break;
		case 'l':ADMUX=0x01;
		break;
		case 'm':ADMUX=0x02;
		break;
		case 'h':ADMUX=0x03;
		break;
	}
	
	sbit(ADCSRA,ADSC);
	while(ADCSRA & 0x40);
	t=ADC*(0.0048828125);
	switch(sel)
	{
		case 't':t=t*100;
		break;
		case 'h':t=(t*30)+0.5;
		break;
	}
	
	if (p!=t)
	{
		switch(sel)
		{
			case 't':lcd_cmd(0x8d);
			if(t<=20)
			{
				cbit(PORTD,6);//fan off
				sbit(PORTD,7);//heater on
			}
			else if(t>20 && t<40)
			{
				cbit(PORTD,6);//fan off
				cbit(PORTD,7);//heater off
			}

			else
			{
				sbit(PORTD,6);//fan on
				cbit(PORTD,7);//heater off
			}
			break;
			
			case 'l':lcd_cmd(0xc7);
			if(t<=0.7)
			cbit(PORTD,5);//bulb off
			else
			sbit(PORTD,5);//bulb on
			break;
			
			case 'm':lcd_cmd(0x9e);
			if(t<=2.68)
			sbit(PORTD,4);//sprinkler on
			else
			cbit(PORTD,4);//sprinkler off
			break;
			
			case 'h':lcd_cmd(0xde);
			if(t<=40)
			sbit(PORTD,3);//humidifier on
			else
			cbit(PORTD,3);//humidifier off
			break;
		}
		t=format(t);
	}	
return t;

}


int main(void)
{
	double t=-1,l=-1,m=-1,h=-1;//store previous values of each output
	int pow[]={0x30,0x30,0x30,0x20};//power up lcd
	int cmd[]={0x28,0x0c,0x06,0x01};// initialize lcd
	char fm1[]="TEMPERATURE:       C$";//fm1,2,3,4 fixed messages to be displayed on lcd
	char fm2[]="LIGHT:      V$";
	char fm3[]="MOISTURE:      V$";
	char fm4[]="HUMIDITY:      %$";
	fm1[18]=0xdf;//ascii for degree symbol
	
	DDRD=0xff;//making necessary ports output
	DDRC=0xff;
	
	ADCSRA=0x83;//enabling adc module and setting prescalar to 8(hence freq of acd clk=125khz)
	
	sbit(MCUCSR,JTD);//disabling jtag
	sbit(MCUCSR,JTD);
	
	lcd_pow(pow);//power up lcd
	lcd_cmd(cmd);// initialize lcd
	
	lcd_msg(fm1);//display fixed messages on lcd on proper lines
	lcd_cmd(0xc0);
	lcd_msg(fm2);
	lcd_cmd(0x94);
	lcd_msg(fm3);
	lcd_cmd(0xd4);
	lcd_msg(fm4);
	while(1)
    {
		t=output(t,'t');
		l=output(l,'l');
		m=output(m,'m');
		h=output(h,'h');
    }
	return 0;
}