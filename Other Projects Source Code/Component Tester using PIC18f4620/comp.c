#pragma  config OSC = INTIO67,WDT = OFF,MCLRE = OFF,PBADEN = OFF
#include <pic18f4620.h>

#define rs PORTCbits.RC0
#define en PORTCbits.RC1
#define rst PORTDbits.RD3

#define r1 PORTBbits.RB7
#define r2 PORTBbits.RB6
#define r3 PORTBbits.RB5
#define r4 PORTBbits.RB4
#define c1 PORTBbits.RB3
#define c2 PORTBbits.RB2
#define c3 PORTBbits.RB1
#define c4 PORTBbits.RB0

void delay(int j) {
    int i;
    while (j != 0) {
        for (i = 0; i < 100; i++);
        j--;
    }
}

void lcd_pow(int pow[]) {
    int i;
    delay(450);
    for (i = 0; i < 4; i++) {
        rs = 0;
        en = 1;
        PORTD = pow[i];
        delay(10);
        en = 0;
        delay(45);
    }
}

void lcd_cmd(int cmd[]) {
    int i;
    for (i = 0; i < 4; i++) {
        int temp;
        rs = 0;
        en = 1;
        PORTD = cmd[i];
        delay(1);
        en = 0;
        delay(1);
        temp = cmd[i] & 0x0f;
        temp = temp << 4;
        en = 1;
        PORTD = temp;
        delay(1);
        en = 0;
        delay(10);
    }
}

void lcd_clear(int cmd) {
    int temp;
    rs = 0;
    en = 1;
    PORTD = cmd;
    delay(1);
    en = 0;
    delay(1);
    temp = cmd & 0x0f;
    temp = temp << 4;
    en = 1;
    PORTD = temp;
    delay(1);
    en = 0;
    delay(10);
}

void lcd_msg(char msg[]) {
    char t;
    int k = 0;
    while (msg[k] != '%') {
        rs = 1;
        en = 1;
        PORTD = msg[k];
        delay(1);
        en = 0;
        t = msg[k]&0x0f;
        t = t << 4;
        en = 1;
        PORTD = t;
        delay(1);
        en = 0;
        delay(10);
        k++;
    }
}

void lcd_welmes() {
    char msg1[] = "IC%";
    char msg2[] = "TESTER%";
    char msg3[] = "BY%";
    char msg4[] = "AS DS GS%";
    lcd_clear(0x87);
    lcd_msg(msg1);
    lcd_clear(0xc5);
    lcd_msg(msg2);
    lcd_clear(0x97);
    lcd_msg(msg3);
    lcd_clear(0xd4);
    lcd_msg(msg4);
}

void lcd_disp2(int choose) {
    char msg1[] = "JK1 IS OK%";
    char msg2[] = "JK1 IS BAD%";
    char msg3[] = "JK2 IS OK%";
    char msg4[] = "JK2 IS BAD%";
    char msg5[] = "D1 IS OK%";
    char msg6[] = "D1 IS BAD%";
    char msg7[] = "D2 IS OK%";
    char msg8[] = "D2 IS BAD%";
    switch (choose) {
        case 1: lcd_msg(msg1);
            lcd_clear(0xc0);
            break;
        case 2: lcd_msg(msg2);
            lcd_clear(0xc0);
            break;
        case 3: lcd_msg(msg3);
            break;
        case 4: lcd_msg(msg4);
            break;
        case 5: lcd_msg(msg5);
            lcd_clear(0xc0);
            break;
        case 6: lcd_msg(msg6);
            lcd_clear(0xc0);
            break;
        case 7: lcd_msg(msg7);
            break;
        case 8: lcd_msg(msg8);
            break;
    }
}

void lcd_disp1(int choose) {
    char msg1[] = "MUX 8:1 IS OK%";
    char msg2[] = "MUX 8:1 IS BAD%";
    char msg3[] = "DEC 3:8 IS OK%";
    char msg4[] = "DEC 3:8 IS BAD%";
    char msg5[] = "FA 2BIT IS OK%";
    char msg6[] = "FA 2BIT IS BAD%";
    switch (choose) {
        case 1: lcd_msg(msg1);
            break;
        case 2: lcd_msg(msg2);
            break;
        case 3: lcd_msg(msg3);
            break;
        case 4: lcd_msg(msg4);
            break;
        case 5: lcd_msg(msg5);
            break;
        case 6: lcd_msg(msg6);
            break;
    }
}

void lcd_disp_inv(int choose) {
    char msg1[] = "1:OK  %";
    char msg2[] = "2:OK%";
    char msg3[] = "3:OK  %";
    char msg4[] = "4:OK%";
    char msg5[] = "5:OK  %";
    char msg6[] = "6:OK%";
    char msg7[] = "1:BAD  %";
    char msg8[] = "2:BAD%";
    char msg9[] = "3:BAD  %";
    char msg10[] = "4:BAD%";
    char msg11[] = "5:BAD  %";
    char msg12[] = "6:BAD%";
    switch (choose) {
        case 1: lcd_msg(msg1);
            break;
        case 2: lcd_msg(msg2);
            lcd_clear(0xc0);
            break;
        case 3: lcd_msg(msg3);
            break;
        case 4: lcd_msg(msg4);
            lcd_clear(0x90);
            break;
        case 5: lcd_msg(msg5);
            break;
        case 6: lcd_msg(msg6);
            break;
        case 7: lcd_msg(msg7);
            break;
        case 8: lcd_msg(msg8);
            lcd_clear(0xc0);
            break;
        case 9: lcd_msg(msg9);
            break;
        case 10: lcd_msg(msg10);
            lcd_clear(0x90);
            break;
        case 11: lcd_msg(msg11);
            break;
        case 12: lcd_msg(msg12);
            break;
    }
}

void lcd_disp(int choose) {
    char msg1[] = "GATE 1 IS OK%";
    char msg2[] = "GATE 2 IS OK%";
    char msg3[] = "GATE 3 IS OK%";
    char msg4[] = "GATE 4 IS OK%";
    char msg5[] = "GATE 1 IS BAD%";
    char msg6[] = "GATE 2 IS BAD%";
    char msg7[] = "GATE 3 IS BAD%";
    char msg8[] = "GATE 4 IS BAD%";
    switch (choose) {
        case 1: lcd_msg(msg1);
            lcd_clear(0xc0);
            break;
        case 2: lcd_msg(msg2);
            lcd_clear(0x90);
            break;
        case 3: lcd_msg(msg3);
            lcd_clear(0xd0);
            break;
        case 4: lcd_msg(msg4);
            break;
        case 5: lcd_msg(msg5);
            lcd_clear(0xc0);
            break;
        case 6: lcd_msg(msg6);
            lcd_clear(0x90);
            break;
        case 7: lcd_msg(msg7);
            lcd_clear(0xd0);
            break;
        case 8: lcd_msg(msg8);
            break;
    }
}

void chk_and() {
    TRISAbits.RA0 = 0; //gate1
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 1;

    TRISAbits.RA3 = 0; //gate2
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 1;

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC3 = 0; //gate3
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 1;

    TRISCbits.RC6 = 0; //gate4
    TRISCbits.RC7 = 0;
    TRISDbits.RD0 = 1;


    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA0 = PORTAbits.RA1 = 1; //gate1
    delay(1);
    if (PORTAbits.RA2 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA2 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 1;
    delay(1);
    if (PORTAbits.RA2 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA2 == 0)
        lcd_disp(1);
    else {
        lcd_disp(5);
        goto next;
    }

next:
    PORTAbits.RA3 = PORTAbits.RA5 = 1; //gate2
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 0)
        lcd_disp(2);
    else {
        lcd_disp(6);
        goto next1;
    }

next1:
    PORTCbits.RC6 = PORTCbits.RC7 = 1; //gate3
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 0)
        lcd_disp(3);
    else {
        lcd_disp(7);
        goto next2;
    }

next2:
    PORTCbits.RC3 = PORTCbits.RC4 = 1; //gate4
    delay(1);
    if (PORTCbits.RC5 == 1) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = PORTCbits.RC4 = 0;
    delay(1);
    if (PORTCbits.RC5 == 0) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = 0;
    PORTCbits.RC4 = 1;
    delay(1);
    if (PORTCbits.RC5 == 0) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = 1;
    PORTCbits.RC4 = 0;
    delay(1);
    if (PORTCbits.RC5 == 0)
        lcd_disp(4);
    else {
        lcd_disp(8);
        goto next3;
    }


next3:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_or() {
    TRISAbits.RA0 = 0; //gate1
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 1;

    TRISAbits.RA3 = 0; //gate2
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 1;

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC3 = 0; //gate3
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 1;

    TRISCbits.RC6 = 0; //gate4
    TRISCbits.RC7 = 0;
    TRISDbits.RD0 = 1;


    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA0 = PORTAbits.RA1 = 1; //gate1
    delay(1);
    if (PORTAbits.RA2 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA2 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 1;
    delay(1);
    if (PORTAbits.RA2 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA2 == 1)
        lcd_disp(1);
    else {
        lcd_disp(5);
        goto next;
    }

next:
    PORTAbits.RA3 = PORTAbits.RA5 = 1; //gate2
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1)
        lcd_disp(2);
    else {
        lcd_disp(6);
        goto next1;
    }

next1:
    PORTCbits.RC6 = PORTCbits.RC7 = 1; //gate3
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1)
        lcd_disp(3);
    else {
        lcd_disp(7);
        goto next2;
    }

next2:
    PORTCbits.RC3 = PORTCbits.RC4 = 1; //gate4
    delay(1);
    if (PORTCbits.RC5 == 1) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = PORTCbits.RC4 = 0;
    delay(1);
    if (PORTCbits.RC5 == 0) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = 0;
    PORTCbits.RC4 = 1;
    delay(1);
    if (PORTCbits.RC5 == 1) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = 1;
    PORTCbits.RC4 = 0;
    delay(1);
    if (PORTCbits.RC5 == 1)
        lcd_disp(4);
    else {
        lcd_disp(8);
        goto next3;
    }

next3:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_nand() {
    TRISAbits.RA0 = 0; //gate1
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 1;

    TRISAbits.RA3 = 0; //gate2
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 1;

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC3 = 0; //gate3
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 1;

    TRISCbits.RC6 = 0; //gate4
    TRISCbits.RC7 = 0;
    TRISDbits.RD0 = 1;


    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA0 = PORTAbits.RA1 = 1; //gate1
    delay(1);
    if (PORTAbits.RA2 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA2 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 1;
    delay(1);
    if (PORTAbits.RA2 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA2 == 1)
        lcd_disp(1);
    else {
        lcd_disp(5);
        goto next;
    }

next:
    PORTAbits.RA3 = PORTAbits.RA5 = 1; //gate2
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1)
        lcd_disp(2);
    else {
        lcd_disp(6);
        goto next1;
    }

next1:
    PORTCbits.RC6 = PORTCbits.RC7 = 1; //gate3
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1)
        lcd_disp(3);
    else {
        lcd_disp(7);
        goto next2;
    }

next2:
    PORTCbits.RC3 = PORTCbits.RC4 = 1; //gate3
    delay(1);
    if (PORTCbits.RC5 == 0) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = PORTCbits.RC4 = 0;
    delay(1);
    if (PORTCbits.RC5 == 1) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = 0;
    PORTCbits.RC4 = 1;
    delay(1);
    if (PORTCbits.RC5 == 1) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = 1;
    PORTCbits.RC4 = 0;
    delay(1);
    if (PORTCbits.RC5 == 1)
        lcd_disp(4);
    else {
        lcd_disp(8);
        goto next3;
    }

next3:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_nor() {
    TRISAbits.RA0 = 1; //gate1
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 0;

    TRISAbits.RA3 = 1; //gate2
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 0;

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC3 = 1; //gate4
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 0;

    TRISCbits.RC6 = 1; //gate3
    TRISCbits.RC7 = 0;
    TRISDbits.RD0 = 0;


    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA1 = PORTAbits.RA2 = 1; //gate1
    delay(1);
    if (PORTAbits.RA0 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA1 = PORTAbits.RA2 = 0;
    delay(1);
    if (PORTAbits.RA0 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA1 = 0;
    PORTAbits.RA2 = 1;
    delay(1);
    if (PORTAbits.RA0 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA1 = 1;
    PORTAbits.RA2 = 0;
    delay(1);
    if (PORTAbits.RA0 == 0)
        lcd_disp(1);
    else {
        lcd_disp(5);
        goto next;
    }

next:
    PORTEbits.RE0 = PORTAbits.RA5 = 1; //gate2
    delay(1);
    if (PORTAbits.RA3 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTEbits.RE0 = PORTAbits.RA5 = 0;
    delay(1);
    if (PORTAbits.RA3 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTEbits.RE0 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTAbits.RA3 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTEbits.RE0 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTAbits.RA3 == 0)
        lcd_disp(2);
    else {
        lcd_disp(6);
        goto next1;
    }

next1:
    PORTDbits.RD0 = PORTCbits.RC7 = 1; //gate3
    delay(1);
    if (PORTCbits.RC6 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTDbits.RD0 = PORTCbits.RC7 = 0;
    delay(1);
    if (PORTCbits.RC6 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTDbits.RD0 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTCbits.RC6 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTDbits.RD0 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTCbits.RC6 == 0)
        lcd_disp(3);
    else {
        lcd_disp(7);
        goto next2;
    }

next2:
    PORTCbits.RC4 = PORTCbits.RC5 = 1; //gate4
    delay(1);
    if (PORTCbits.RC3 == 0) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC4 = PORTCbits.RC5 = 0;
    delay(1);
    if (PORTCbits.RC3 == 1) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC4 = 0;
    PORTCbits.RC5 = 1;
    delay(1);
    if (PORTCbits.RC3 == 0) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC4 = 1;
    PORTCbits.RC5 = 0;
    delay(1);
    if (PORTCbits.RC3 == 0)
        lcd_disp(4);
    else {
        lcd_disp(8);
        goto next3;
    }


next3:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_nand3() {
    TRISAbits.RA0 = 0; //gate1
    TRISAbits.RA1 = 0;
    TRISCbits.RC3 = 0;
    TRISCbits.RC4 = 1;

    TRISAbits.RA2 = 0; //gate2
    TRISAbits.RA3 = 0;
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 1;

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC5 = 0; //gate3
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
    TRISDbits.RD0 = 1;


    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA0 = PORTAbits.RA1 = PORTCbits.RC3 = 1; //gate1
    delay(1);
    if (PORTCbits.RC4 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = PORTAbits.RA1 = PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 0;
    PORTCbits.RC3 = 1;
    delay(1);
    if (PORTCbits.RC4 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 1;
    PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 1;
    PORTCbits.RC3 = 1;
    delay(1);
    if (PORTCbits.RC4 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 0;
    PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 0;
    PORTCbits.RC3 = 1;
    delay(1);
    if (PORTCbits.RC4 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 1)
        lcd_disp(1);
    else {
        lcd_disp(5);
        goto next;
    }

next:
    PORTAbits.RA2 = PORTAbits.RA3 = PORTAbits.RA5 = 1; //gate2
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = PORTAbits.RA3 = PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1)
        lcd_disp(2);
    else {
        lcd_disp(6);
        goto next1;
    }

next1:
    PORTCbits.RC5 = PORTCbits.RC6 = PORTCbits.RC7 = 1; //gate3
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = PORTCbits.RC6 = PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 1;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 1;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 1;
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1)
        lcd_disp(3);
    else {
        lcd_disp(7);
        goto next2;
    }
next2:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_nor3() {
    TRISAbits.RA0 = 0; //gate1
    TRISAbits.RA1 = 0;
    TRISCbits.RC3 = 0;
    TRISCbits.RC4 = 1;

    TRISAbits.RA2 = 0; //gate2
    TRISAbits.RA3 = 0;
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 1;

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC5 = 0; //gate3
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;
    TRISDbits.RD0 = 1;


    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA0 = PORTAbits.RA1 = PORTCbits.RC3 = 1; //gate1
    delay(1);
    if (PORTCbits.RC4 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = PORTAbits.RA1 = PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 0;
    PORTCbits.RC3 = 1;
    delay(1);
    if (PORTCbits.RC4 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 1;
    PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 1;
    PORTCbits.RC3 = 1;
    delay(1);
    if (PORTCbits.RC4 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 0;
    PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 0;
    PORTCbits.RC3 = 1;
    delay(1);
    if (PORTCbits.RC4 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 1;
    PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 0)
        lcd_disp(1);
    else {
        lcd_disp(5);
        goto next;
    }

next:
    PORTAbits.RA2 = PORTAbits.RA3 = PORTAbits.RA5 = 1; //gate2
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = PORTAbits.RA3 = PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 0;
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA2 = 1;
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 0)
        lcd_disp(2);
    else {
        lcd_disp(6);
        goto next1;
    }

next1:
    PORTCbits.RC5 = PORTCbits.RC6 = PORTCbits.RC7 = 1; //gate3
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = PORTCbits.RC6 = PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 0;
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 1;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 1;
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC5 = 1;
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 0)
        lcd_disp(3);
    else {
        lcd_disp(7);
        goto next2;
    }
next2:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_not() {
    TRISAbits.RA0 = 0; //gate1
    TRISAbits.RA1 = 1;


    TRISAbits.RA2 = 0; //gate2
    TRISAbits.RA3 = 1;

    TRISAbits.RA5 = 0; //gate3
    TRISEbits.RE0 = 1;

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC3 = 0; //gate6
    TRISCbits.RC4 = 1;

    TRISCbits.RC5 = 0; //gate5
    TRISCbits.RC6 = 1;

    TRISCbits.RC7 = 0; //gate4
    TRISDbits.RD0 = 1;


    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA0 = 1; //gate1
    delay(1);
    if (PORTAbits.RA1 == 0) {
    } else {
        lcd_disp_inv(7);
        goto next;
    }
    PORTAbits.RA0 = 0;
    delay(1);
    if (PORTAbits.RA1 == 1)
        lcd_disp_inv(1);
    else {
        lcd_disp_inv(7);
        goto next;
    }

next:
    PORTAbits.RA2 = 1; //gate2
    delay(1);
    if (PORTAbits.RA3 == 0) {
    } else {
        lcd_disp_inv(8);
        goto next1;
    }
    PORTAbits.RA2 = 0;
    delay(1);
    if (PORTAbits.RA3 == 1)
        lcd_disp_inv(2);
    else {
        lcd_disp_inv(8);
        goto next1;
    }

next1:
    PORTAbits.RA5 = 1; //gate3
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp_inv(9);
        goto next2;
    }
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1)
        lcd_disp_inv(3);
    else {
        lcd_disp_inv(9);
        goto next2;
    }

next2:
    PORTCbits.RC7 = 1; //gate4
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp_inv(10);
        goto next3;
    }
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1)
        lcd_disp_inv(4);
    else {
        lcd_disp_inv(10);
        goto next3;
    }

next3:
    PORTCbits.RC5 = 1; //gate5
    delay(1);
    if (PORTCbits.RC6 == 0) {
    } else {
        lcd_disp_inv(11);
        goto next4;
    }
    PORTCbits.RC5 = 0;
    delay(1);
    if (PORTCbits.RC6 == 1)
        lcd_disp_inv(5);
    else {
        lcd_disp_inv(11);
        goto next4;
    }

next4:
    PORTCbits.RC3 = 1; //gate6
    delay(1);
    if (PORTCbits.RC4 == 0) {
    } else {
        lcd_disp_inv(12);
        goto next5;
    }
    PORTCbits.RC3 = 0;
    delay(1);
    if (PORTCbits.RC4 == 1)
        lcd_disp_inv(6);
    else {
        lcd_disp_inv(12);
        goto next5;
    }

next5:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_mux81() {
    TRISAbits.RA3 = 0; //data lines
    TRISAbits.RA2 = 0;
    TRISAbits.RA1 = 0;
    TRISAbits.RA0 = 0;
    TRISCbits.RC3 = 0;
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 0;
    TRISCbits.RC6 = 0;

    TRISDbits.RD1 = 0; //select lines
    TRISDbits.RD0 = 0;
    TRISCbits.RC7 = 0;


    TRISAbits.RA5 = 1; //output
    TRISEbits.RE0 = 1; //inv output

    TRISEbits.RE1 = 0; //enable

    TRISEbits.RE2 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    PORTEbits.RE2 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTEbits.RE1 = 1;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTEbits.RE1 = 0;

    PORTDbits.RD1 = PORTDbits.RD0 = PORTCbits.RC7 = 1;
    PORTCbits.RC6 = 1;
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTCbits.RC6 = 0;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp1(2);
        goto next;
    }

    PORTDbits.RD1 = PORTDbits.RD0 = PORTCbits.RC7 = 0;
    PORTAbits.RA3 = 1;
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTAbits.RA3 = 0;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp1(2);
        goto next;
    }

    PORTDbits.RD1 = 0;
    PORTDbits.RD0 = 0;
    PORTCbits.RC7 = 1;
    PORTAbits.RA2 = 1;
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTAbits.RA2 = 0;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp1(2);
        goto next;
    }

    PORTDbits.RD1 = 0;
    PORTDbits.RD0 = 1;
    PORTCbits.RC7 = 0;
    PORTAbits.RA1 = 1;
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp1(2);
        goto next;
    }

    PORTDbits.RD1 = 0;
    PORTDbits.RD0 = 1;
    PORTCbits.RC7 = 1;
    PORTAbits.RA0 = 1;
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTAbits.RA0 = 0;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp1(2);
        goto next;
    }

    PORTDbits.RD1 = 1;
    PORTDbits.RD0 = 0;
    PORTCbits.RC7 = 0;
    PORTCbits.RC3 = 1;
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTCbits.RC3 = 0;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp1(2);
        goto next;
    }

    PORTDbits.RD1 = 1;
    PORTDbits.RD0 = 0;
    PORTCbits.RC7 = 1;
    PORTCbits.RC4 = 1;
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTCbits.RC4 = 0;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp1(2);
        goto next;
    }

    PORTDbits.RD1 = 1;
    PORTDbits.RD0 = 1;
    PORTCbits.RC7 = 0;
    PORTCbits.RC5 = 1;
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp1(2);
        goto next;
    }
    PORTCbits.RC5 = 0;
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1)
        lcd_disp1(1);
    else {
        lcd_disp1(2);
        goto next;
    }

next:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_dec38() {
    TRISCbits.RC3 = 1; //output lines
    TRISCbits.RC4 = 1;
    TRISCbits.RC5 = 1;
    TRISCbits.RC6 = 1;
    TRISCbits.RC7 = 1;
    TRISDbits.RD0 = 1;
    TRISDbits.RD1 = 1;
    TRISEbits.RE1 = 1;

    TRISAbits.RA3 = 0; //enable lines
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 0;

    TRISAbits.RA2 = 0; //select lines
    TRISAbits.RA1 = 0;
    TRISAbits.RA0 = 0;

    TRISEbits.RE2 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    PORTEbits.RE2 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA3 = 1;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTEbits.RE0 = 0;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 0;
    PORTEbits.RE0 = 1;

    PORTAbits.RA2 = 0;
    PORTAbits.RA1 = 0;
    PORTAbits.RA0 = 0;
    delay(1);
    if (PORTCbits.RC3 == 0 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA2 = 0;
    PORTAbits.RA1 = 0;
    PORTAbits.RA0 = 1;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 0 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA2 = 0;
    PORTAbits.RA1 = 1;
    PORTAbits.RA0 = 0;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 0 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA2 = 0;
    PORTAbits.RA1 = 1;
    PORTAbits.RA0 = 1;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 0 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA2 = 1;
    PORTAbits.RA1 = 0;
    PORTAbits.RA0 = 0;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 0 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA2 = 1;
    PORTAbits.RA1 = 0;
    PORTAbits.RA0 = 1;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 0 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA2 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA0 = 0;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 0 && PORTEbits.RE1 == 1) {
    } else {
        lcd_disp1(4);
        goto next;
    }

    PORTAbits.RA2 = 1;
    PORTAbits.RA1 = 1;
    PORTAbits.RA0 = 1;
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1 && PORTCbits.RC5 == 1 && PORTCbits.RC6 == 1 && PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1 && PORTDbits.RD1 == 1 && PORTEbits.RE1 == 0)
        lcd_disp1(3);
    else {
        lcd_disp1(4);
        goto next;
    }

next:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_xor() {
    TRISAbits.RA0 = 0; //gate1
    TRISAbits.RA1 = 0;
    TRISAbits.RA2 = 1;

    TRISAbits.RA3 = 0; //gate2
    TRISAbits.RA5 = 0;
    TRISEbits.RE0 = 1;

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC3 = 0; //gate4
    TRISCbits.RC4 = 0;
    TRISCbits.RC5 = 1;

    TRISCbits.RC6 = 0; //gate3
    TRISCbits.RC7 = 0;
    TRISDbits.RD0 = 1;


    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA0 = PORTAbits.RA1 = 1; //gate1
    delay(1);
    if (PORTAbits.RA2 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA2 == 0) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 1;
    delay(1);
    if (PORTAbits.RA2 == 1) {
    } else {
        lcd_disp(5);
        goto next;
    }
    PORTAbits.RA0 = 1;
    PORTAbits.RA1 = 0;
    delay(1);
    if (PORTAbits.RA2 == 1)
        lcd_disp(1);
    else {
        lcd_disp(5);
        goto next;
    }

next:
    PORTAbits.RA3 = PORTAbits.RA5 = 1; //gate2
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 0) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = 0;
    PORTAbits.RA5 = 1;
    delay(1);
    if (PORTEbits.RE0 == 1) {
    } else {
        lcd_disp(6);
        goto next1;
    }
    PORTAbits.RA3 = 1;
    PORTAbits.RA5 = 0;
    delay(1);
    if (PORTEbits.RE0 == 1)
        lcd_disp(2);
    else {
        lcd_disp(6);
        goto next1;
    }

next1:
    PORTCbits.RC6 = PORTCbits.RC7 = 1; //gate3
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 0) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = 0;
    PORTCbits.RC7 = 1;
    delay(1);
    if (PORTDbits.RD0 == 1) {
    } else {
        lcd_disp(7);
        goto next2;
    }
    PORTCbits.RC6 = 1;
    PORTCbits.RC7 = 0;
    delay(1);
    if (PORTDbits.RD0 == 1)
        lcd_disp(3);
    else {
        lcd_disp(7);
        goto next2;
    }

next2:
    PORTCbits.RC3 = PORTCbits.RC4 = 1; //gate4
    delay(1);
    if (PORTCbits.RC5 == 0) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = PORTCbits.RC4 = 0;
    delay(1);
    if (PORTCbits.RC5 == 0) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = 0;
    PORTCbits.RC4 = 1;
    delay(1);
    if (PORTCbits.RC5 == 1) {
    } else {
        lcd_disp(8);
        goto next3;
    }
    PORTCbits.RC3 = 1;
    PORTCbits.RC4 = 0;
    delay(1);
    if (PORTCbits.RC5 == 1)
        lcd_disp(4);
    else {
        lcd_disp(8);
        goto next3;
    }

next3:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_fa2bit() {
    TRISCbits.RC4 = 1; //s1
    TRISAbits.RA0 = 1; //s0

    TRISCbits.RC6 = 1; //cout

    TRISCbits.RC3 = 0; //b1
    TRISCbits.RC2 = 0; //a1
    TRISAbits.RA2 = 0; //b0
    TRISAbits.RA1 = 0; //a0


    TRISAbits.RA5 = 0; //cin

    TRISAbits.RA3 = 0; //vcc
    TRISCbits.RC5 = 0; //gnd

    PORTAbits.RA3 = 1; //vcc
    PORTCbits.RC5 = 0; //gnd

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 0; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 0; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 0 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 0; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 0 && PORTAbits.RA0 == 1) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 0; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 0; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 0) {
    } else {
        lcd_disp1(6);
        goto next;
    }

    PORTAbits.RA5 = 1; //cin
    PORTCbits.RC3 = 1; //b1
    PORTCbits.RC2 = 1; //a1
    PORTAbits.RA2 = 1; //b0
    PORTAbits.RA1 = 1; //a0
    delay(1);

    if (PORTCbits.RC6 == 1 && PORTCbits.RC4 == 1 && PORTAbits.RA0 == 1)
        lcd_disp1(5);
    else {
        lcd_disp1(6);
        goto next;
    }

next:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_jkff() {
    TRISAbits.RA0 = 0; //clk1
    TRISAbits.RA1 = 0; //preset1
    TRISAbits.RA2 = 0; //clear1
    TRISAbits.RA3 = 0; //j1
    TRISCbits.RC2 = 0; //k1
    TRISCbits.RC3 = 1; //q1
    TRISCbits.RC4 = 1; //q1bar

    TRISAbits.RA5 = 0; //vcc
    TRISCbits.RC5 = 0; //gnd

    TRISEbits.RE0 = 0; //clk2
    TRISEbits.RE1 = 0; //preset2
    TRISEbits.RE2 = 0; //clear2
    TRISDbits.RD1 = 0; //j2
    TRISCbits.RC6 = 0; //k2
    TRISCbits.RC7 = 1; //q2
    TRISDbits.RD0 = 1; //q2bar

    PORTAbits.RA5 = 1; //vcc
    PORTCbits.RC5 = 0; //gnd

    PORTAbits.RA1 = 0; //preset1
    PORTAbits.RA2 = 1; //clear1
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 0) {
    } else {
        lcd_disp2(2);
        goto next;
    }

    PORTAbits.RA1 = 1; //preset1
    PORTAbits.RA2 = 0; //clear1
    delay(1);
    if (PORTCbits.RC3 == 0 && PORTCbits.RC4 == 1) {
    } else {
        lcd_disp2(2);
        goto next;
    }

    PORTAbits.RA1 = 0; //preset1
    PORTAbits.RA2 = 0; //clear1
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 1) {
    } else {
        lcd_disp2(2);
        goto next;
    }

    PORTAbits.RA1 = 1; //preset1
    PORTAbits.RA2 = 1; //clear1
    PORTAbits.RA0 = 1; //clk1
    delay(1);
    PORTAbits.RA3 = 1; //j1
    PORTCbits.RC2 = 0; //k1
    PORTAbits.RA0 = 0; //clk1
    delay(5);
    PORTAbits.RA0 = 1; //clk1
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 0) {
    } else {
        lcd_disp2(2);
        goto next;
    }

    PORTAbits.RA3 = 0; //j1
    PORTCbits.RC2 = 1; //k1
    PORTAbits.RA0 = 0; //clk1
    delay(5);
    PORTAbits.RA0 = 1; //clk1
    delay(1);
    if (PORTCbits.RC3 == 0 && PORTCbits.RC4 == 1) {
    } else {
        lcd_disp2(2);
        goto next;
    }

    PORTAbits.RA3 = 0; //j1
    PORTCbits.RC2 = 0; //k1
    PORTAbits.RA0 = 0; //clk1
    delay(5);
    PORTAbits.RA0 = 1; //clk1
    delay(1);
    if (PORTCbits.RC3 == 0 && PORTCbits.RC4 == 1) {
    } else {
        lcd_disp2(2);
        goto next;
    }

    PORTAbits.RA3 = 1; //j1
    PORTCbits.RC2 = 1; //k1
    PORTAbits.RA0 = 0; //clk1
    delay(5);
    PORTAbits.RA0 = 1; //clk1
    delay(1);
    if (PORTCbits.RC3 == 1 && PORTCbits.RC4 == 0)
        lcd_disp2(1);
    else {
        lcd_disp2(2);
        goto next;
    }

next:
    PORTEbits.RE1 = 0; //preset2
    PORTEbits.RE2 = 1; //clear2
    delay(1);
    if (PORTCbits.RC7 == 1 && PORTDbits.RD0 == 0) {
    } else {
        lcd_disp2(4);
        goto next1;
    }

    PORTEbits.RE1 = 1; //preset2
    PORTEbits.RE2 = 0; //clear2
    delay(1);
    if (PORTCbits.RC7 == 0 && PORTDbits.RD0 == 1) {
    } else {
        lcd_disp2(4);
        goto next1;
    }

    PORTEbits.RE1 = 0; //preset2
    PORTEbits.RE2 = 0; //clear2
    delay(1);
    if (PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1) {
    } else {
        lcd_disp2(4);
        goto next1;
    }

    PORTEbits.RE1 = 1; //preset2
    PORTEbits.RE2 = 1; //clear2
    PORTEbits.RE0 = 1; //clk2
    delay(1);
    PORTDbits.RD1 = 1; //j2
    PORTCbits.RC6 = 0; //k2
    PORTEbits.RE0 = 0; //clk2
    delay(5);
    PORTEbits.RE0 = 1; //clk2
    delay(1);
    if (PORTCbits.RC7 == 1 && PORTDbits.RD0 == 0) {
    } else {
        lcd_disp2(4);
        goto next1;
    }

    PORTDbits.RD1 = 0; //j2
    PORTCbits.RC6 = 1; //k2
    PORTEbits.RE0 = 0; //clk2
    delay(5);
    PORTEbits.RE0 = 1; //clk2
    delay(1);
    if (PORTCbits.RC7 == 0 && PORTDbits.RD0 == 1) {
    } else {
        lcd_disp2(4);
        goto next1;
    }

    PORTDbits.RD1 = 0; //j2
    PORTCbits.RC6 = 0; //k2
    PORTEbits.RE0 = 0; //clk2
    delay(5);
    PORTEbits.RE0 = 1; //clk2
    delay(1);
    if (PORTCbits.RC7 == 0 && PORTDbits.RD0 == 1) {
    } else {
        lcd_disp2(4);
        goto next1;
    }

    PORTDbits.RD1 = 1; //j2
    PORTCbits.RC6 = 1; //k2
    PORTEbits.RE0 = 0; //clk2
    delay(5);
    PORTEbits.RE0 = 1; //clk2
    delay(1);
    if (PORTCbits.RC7 == 1 && PORTDbits.RD0 == 0)
        lcd_disp2(3);
    else {
        lcd_disp2(4);
        goto next1;
    }
next1:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void chk_dff() {
    TRISAbits.RA0 = 0; //clear1
    TRISAbits.RA1 = 0; //d1
    TRISAbits.RA2 = 0; //clk1
    TRISAbits.RA3 = 0; //preset1
    TRISAbits.RA5 = 1; //q1
    TRISEbits.RE0 = 1; //q1bar

    TRISEbits.RE1 = 0; //gnd
    TRISCbits.RC2 = 0; //vcc

    TRISCbits.RC3 = 0; //clear2
    TRISCbits.RC4 = 0; //d2
    TRISCbits.RC5 = 0; //clk2
    TRISCbits.RC6 = 0; //preset2
    TRISCbits.RC7 = 1; //q2
    TRISDbits.RD0 = 1; //q2bar

    PORTEbits.RE1 = 0; //gnd
    PORTCbits.RC2 = 1; //vcc

    PORTAbits.RA0 = 1; //clear1
    PORTAbits.RA3 = 0; //preset1
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp2(6);
        goto next;
    }

    PORTAbits.RA0 = 0; //clear1
    PORTAbits.RA3 = 1; //preset1
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp2(6);
        goto next;
    }

    PORTAbits.RA0 = 0; //clear1
    PORTAbits.RA3 = 0; //preset1
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 1) {
    } else {
        lcd_disp2(6);
        goto next;
    }

    PORTAbits.RA0 = 1; //clear1
    PORTAbits.RA3 = 1; //preset1
    PORTAbits.RA2 = 0; //clk1
    delay(1);
    PORTAbits.RA1 = 1; //d1
    PORTAbits.RA2 = 1; //clk1
    delay(5);
    PORTAbits.RA2 = 0; //clk1
    delay(1);
    if (PORTAbits.RA5 == 1 && PORTEbits.RE0 == 0) {
    } else {
        lcd_disp2(6);
        goto next;
    }

    PORTAbits.RA1 = 0; //d1
    PORTAbits.RA2 = 1; //clk1
    delay(5);
    PORTAbits.RA2 = 0; //clk1
    delay(1);
    if (PORTAbits.RA5 == 0 && PORTEbits.RE0 == 1)
        lcd_disp2(5);
    else {
        lcd_disp2(6);
        goto next;
    }

next:
    PORTCbits.RC3 = 1; //clear2
    PORTCbits.RC6 = 0; //preset2
    delay(1);
    if (PORTCbits.RC7 == 1 && PORTDbits.RD0 == 0) {
    } else {
        lcd_disp2(8);
        goto next1;
    }

    PORTCbits.RC3 = 0; //clear2
    PORTCbits.RC6 = 1; //preset2
    delay(1);
    if (PORTCbits.RC7 == 0 && PORTDbits.RD0 == 1) {
    } else {
        lcd_disp2(8);
        goto next1;
    }

    PORTCbits.RC3 = 0; //clear2
    PORTCbits.RC6 = 0; //preset2
    delay(1);
    if (PORTCbits.RC7 == 1 && PORTDbits.RD0 == 1) {
    } else {
        lcd_disp2(8);
        goto next1;
    }

    PORTCbits.RC3 = 1; //clear2
    PORTCbits.RC6 = 1; //preset2
    PORTCbits.RC5 = 0; //clk2
    delay(1);
    PORTCbits.RC4 = 1; //d2
    PORTCbits.RC5 = 1; //clk2
    delay(5);
    PORTCbits.RC5 = 0; //clk2
    delay(1);
    if (PORTCbits.RC7 == 1 && PORTDbits.RD0 == 0) {
    } else {
        lcd_disp2(8);
        goto next1;
    }

    PORTCbits.RC4 = 0; //d2
    PORTCbits.RC5 = 1; //clk2
    delay(5);
    PORTCbits.RC5 = 0; //clk2
    delay(1);
    if (PORTCbits.RC7 == 0 && PORTDbits.RD0 == 1)
        lcd_disp2(7);
    else {
        lcd_disp2(8);
        goto next1;
    }

next1:
    while (1) {
        if (rst == 1) {
            lcd_clear(0x01);
            lcd_welmes();
            break;
        }
    }
}

void ipdisp(char temp) {
    char msg1[] = "7486 %";
    char msg2[] = "7482 %";
    char msg3[] = "7408 %";
    char msg4[] = "7432 %";
    char msg5[] = "7404 %";
    char msg6[] = "7400 %";
    char msg7[] = "7402 %";
    char msg8[] = "7410 %";
    char msg9[] = "7427 %";
    char msg10[] = "7476 %";
    char msg11[] = "7474 %";
    char msg12[] = "74151%";
    char msg13[] = "74138%";
    switch (temp) {
        case 'c':lcd_msg(msg1);
            break;
        case '0':lcd_msg(msg2);
            break;
        case '=':lcd_msg(msg3);
            break;
        case '+':lcd_msg(msg4);
            break;
        case '1':lcd_msg(msg5);
            break;
        case '2':lcd_msg(msg6);
            break;
        case '3':lcd_msg(msg7);
            break;
        case '-':lcd_msg(msg8);
            break;
        case '4':lcd_msg(msg9);
            break;
        case '5':lcd_msg(msg10);
            break;
        case '6':lcd_msg(msg11);
            break;
        case '*':lcd_msg(msg12);
            break;
        case '7':lcd_msg(msg13);
            break;
        default:return;
    }
}

void keyscan() {
    int cmd = 0x01;
    char temp = 'p';
    lcd_clear(0x80);
    r1 = r2 = r3 = r4 = 1;
    while (1) {
        r1 = 0;
        if (c1 == 0) {
            lcd_clear(cmd);
            temp = '7';
            ipdisp(temp);
        } else if (c2 == 0) {
            return;
        } else if (c3 == 0) {
            return;
        } else if (c4 == 0) {
            break;
        }
        r1 = 1;

        r2 = 0;
        if (c1 == 0) {
            lcd_clear(cmd);
            temp = '4';
            ipdisp(temp);
        } else if (c2 == 0) {
            lcd_clear(cmd);
            temp = '5';
            ipdisp(temp);
        } else if (c3 == 0) {
            lcd_clear(cmd);
            temp = '6';
            ipdisp(temp);
        } else if (c4 == 0) {
            lcd_clear(cmd);
            temp = '*';
            ipdisp(temp);
        }
        r2 = 1;

        r3 = 0;
        if (c1 == 0) {
            lcd_clear(cmd);
            temp = '1';
            ipdisp(temp);
        } else if (c2 == 0) {
            lcd_clear(cmd);
            temp = '2';
            ipdisp(temp);
        } else if (c3 == 0) {
            lcd_clear(cmd);
            temp = '3';
            ipdisp(temp);
        } else if (c4 == 0) {
            lcd_clear(cmd);
            temp = '-';
            ipdisp(temp);
        }
        r3 = 1;


        r4 = 0;
        if (c1 == 0) {
            lcd_clear(cmd);
            temp = 'c';
            ipdisp(temp);
        } else if (c2 == 0) {
            lcd_clear(cmd);
            temp = '0';
            ipdisp(temp);
        } else if (c3 == 0) {
            lcd_clear(cmd);
            temp = '=';
            ipdisp(temp);
        } else if (c4 == 0) {
            lcd_clear(cmd);
            temp = '+';
            ipdisp(temp);
        }
        r4 = 1;
    }
    switch (temp) {
        case 'c':lcd_clear(cmd);
            chk_xor(); //ic7486
            break;
        case '0':lcd_clear(cmd); //ic7482
            chk_fa2bit();
            break;
        case '=':lcd_clear(cmd); //ic7408
            chk_and();
            break;
        case '+':lcd_clear(cmd); //ic7432
            chk_or();
            break;
        case '1':lcd_clear(cmd); //ic7404
            chk_not();
            break;
        case '2':lcd_clear(cmd); //ic7400
            chk_nand();
            break;
        case '3':lcd_clear(cmd); //ic7402
            chk_nor();
            break;
        case '-':lcd_clear(cmd); //ic7410
            chk_nand3();
            break;
        case '4':lcd_clear(cmd); //ic7427
            chk_nor3();
            break;
        case '5':lcd_clear(cmd); //ic7476
            chk_jkff();
            break;
        case '6':lcd_clear(cmd); //ic7474
            chk_dff();
            break;
        case '*':lcd_clear(cmd); //ic74151
            chk_mux81();
            break;
        case '7':lcd_clear(cmd); //ic74138
            chk_dec38();
            break;
        default:return;
    }
}

void main() {

    int pow[] = {0x30, 0x30, 0x30, 0x20};
    int cmd[] = {0x28, 0x0c, 0x06, 0x01};
    OSCCON = 0x73;
    OSCTUNE = 0x40;
    while(OSCCONbits.IOFS==0);

    ADCON1 = 0x0f;
    TRISDbits.RD7 = 0;
    TRISDbits.RD6 = 0;
    TRISDbits.RD5 = 0;
    TRISDbits.RD4 = 0;
    TRISDbits.RD3 = 1;

    TRISCbits.RC0 = 0;
    TRISCbits.RC1 = 0;

    TRISB = 0x0f;

    lcd_pow(pow);
    lcd_cmd(cmd);
    lcd_welmes();

    while (1) {
        keyscan();
    }
}