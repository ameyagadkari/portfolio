--game.vhd
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;
 
package game is

procedure brick(signal hpos_scr,vpos_scr,xpos,ypos,ball_x,ball_y: in integer; signal draw:out std_logic;signal r,g,b:out std_logic_vector(3 downto 0); signal coll_x,coll_y:out std_logic;signal ball_x_vel:in std_logic;signal ball_y_vel:in std_logic);

procedure bat(signal hpos_scr,vpos_scr, xpos,ypos:in integer; signal draw:out std_logic; signal r,g,b:out std_logic_vector(3 downto 0));

procedure ball(signal hpos_scr,vpos_scr, ball_x,ball_y:in integer; signal ball_row,ball_col:out integer);

procedure gameover(signal hpos_scr,vpos_scr, gameover_x,gameover_y:in integer; signal gameover_row,gameover_col:out integer);

procedure lives(signal hpos_scr,vpos_scr, lives_x,lives_y:in integer; signal lives_row,lives_col:out integer);

procedure welmes(signal hpos_scr,vpos_scr,welmes_x,welmes_y:in integer; signal welmes_row,welmes_col:out integer);

procedure winmes(signal hpos_scr,vpos_scr,winmes_x,winmes_y:in integer; signal winmes_row,winmes_col:out integer);

procedure paused(signal hpos_scr,vpos_scr,paused_x,paused_y:in integer; signal paused_row,paused_col:out integer);

end game;

package body game is

procedure brick(signal hpos_scr,vpos_scr, xpos,ypos,ball_x,ball_y: in integer; signal draw:out std_logic;signal r,g,b:out std_logic_vector(3 downto 0); signal coll_x,coll_y: out std_logic;signal ball_x_vel:in std_logic; signal ball_y_vel:in std_logic) is--Procedure to assign draw,rgb,collision signals of all bricks
	begin
		if(hpos_scr>=xpos and hpos_scr<xpos+40 and vpos_scr>=ypos and vpos_scr<ypos+20)then
			draw<='1';
			r<="1001";
			g<="0101";
			b<="1101";
		else
			draw<='0';
			r<="0000";
			g<="0000";
			b<="0000";
		end if;

		if(ypos=ball_y+12) then		--top edge collision detection
			if(ball_x>=xpos-9 and ball_x<=xpos+36) then--for other top edge pixel collision change velocity in y alone
				coll_y<='1';
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			elsif(ball_x>=xpos-14 and ball_x<=xpos-10)then
				if(ball_y_vel='1' and ball_x_vel='1')then--if ball is coming down and moving right and colliding with top left corner pixel it should change velocity in both x & y
					coll_x<='1';
					coll_y<='1';
				elsif(ball_y_vel='1' and ball_x_vel='0')then--if ball is coming down and moving left and colliding with top left corner pixel it should change velocity in y alone
					coll_y<='1';
				elsif(ball_y_vel='0' and ball_x_vel='1')then--if ball is going up and moving right and colliding with top left corner pixel it should change velocity in x alone
					coll_x<='1';
				else
					null;
				end if;
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			elsif(ball_x>=xpos+37 and ball_x<=xpos+41)then
				if(ball_y_vel='1' and ball_x_vel='0')then--if ball is coming down and moving left and colliding with top right corner pixel it should change velocity in both x & y
					coll_x<='1';
					coll_y<='1';
				elsif(ball_y_vel='1' and ball_x_vel='1')then--if ball is coming down and moving right and colliding with top right corner pixel it should change velocity in y alone
					coll_y<='1';
				elsif(ball_y_vel='0' and ball_x_vel='0')then--if ball is going up and moving left and colliding with top right corner pixel it should change velocity in x alone
					coll_x<='1';
				else
					null;
				end if;		
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			else
				null;
			end if;
		else
			null;
		end if;

		if(ypos+19=ball_y) then		--bottom edge collision detection
			if(ball_x>=xpos-9 and ball_x<=xpos+36) then--for other bottom edge pixel collision change velocity in y alone
				coll_y<='1';
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			elsif(ball_x>=xpos-14 and ball_x<=xpos-10)then
				if(ball_y_vel='0' and ball_x_vel='1')then--if ball is going up and moving right and colliding with bottom left corner pixel it should change velocity in both x & y
					coll_x<='1';
					coll_y<='1';
				elsif(ball_y_vel='0' and ball_x_vel='0')then--if ball is going up and moving left and colliding with bottom left corner pixel it should change velocity in y alone
					coll_y<='1';
				elsif(ball_y_vel='1' and ball_x_vel='1')then--if ball is coming down and moving right and colliding with bottom left corner pixel it should change velocity in x alone
					coll_x<='1';
				else
					null;
				end if;
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			elsif(ball_x>=xpos+37 and ball_x<=xpos+41)then
				if(ball_y_vel='0' and ball_x_vel='0')then--if ball is going up and moving left and colliding with bottom right corner pixel it should change velocity in both x & y
					coll_x<='1';
					coll_y<='1';
				elsif(ball_y_vel='0' and ball_x_vel='1')then--if ball is going up and moving right and colliding with bottom right corner pixel it should change velocity in y alone
					coll_y<='1';
				elsif(ball_y_vel='1' and ball_x_vel='0')then--if ball is coming down and moving left and colliding with bottom right corner pixel it should change velocity in x alone
					coll_x<='1';
				else
					null;
				end if;		
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			else
				null;
			end if;
		else
			null;
		end if;
		
		if(ball_x>=xpos-15 and ball_x<=xpos-11) then		--left edge collision detection
			if(ball_y>=ypos-9 and ball_y<=ypos+16) then--for other left edge pixel collision change velocity in x alone
				coll_x<='1';
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			elsif(ball_y>=ypos-11 and ball_y<=ypos-10)then
				if(ball_y_vel='0' and ball_x_vel='1')then--if ball is going up and moving right and colliding with left top corner pixel it should change velocity in x alone
					coll_x<='1';
				elsif(ball_y_vel='1' and ball_x_vel='1')then--if ball is coming down and moving right and colliding with left top corner pixel it should change velocity in both x & y
					coll_x<='1';
					coll_y<='1';
				else
					null;
				end if;
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			elsif(ball_y>=ypos+17 and ball_y<=ypos+18)then
				if(ball_y_vel='0' and ball_x_vel='1')then--if ball is going up and moving right and colliding with left bottom corner pixel it should change velocity in both x & y
					coll_x<='1';
					coll_y<='1';
				elsif(ball_y_vel='1' and ball_x_vel='1')then--if ball is coming down and moving right and colliding with left bottom corner pixel it should change velocity in x alone
					coll_x<='1';
				else
					null;
				end if;
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			else
				null;
			end if;
		else
			null;
		end if;

		if(ball_x>=xpos+37 and ball_x<=xpos+41) then		--right edge collision detection
			if(ball_y>=ypos-9 and ball_y<=ypos+16) then--for other right edge pixel collision change velocity in x alone
				coll_x<='1';
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			elsif(ball_y>=ypos-11 and ball_y<=ypos-10)then
				if(ball_y_vel='1' and ball_x_vel='0')then--if ball is coming down and moving left and colliding with right top corner pixel it should change velocity in both x & y
					coll_x<='1';
					coll_y<='1';
				elsif(ball_y_vel='0' and ball_x_vel='0')then--if ball is going up and moving left and colliding with right top corner pixel it should change velocity in x alone
					coll_x<='1';
				else
					null;
				end if;
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			elsif(ball_y>=ypos+17 and ball_y<=ypos+18)then
				if(ball_y_vel='1' and ball_x_vel='0')then--if ball is coming down and moving left and colliding with right bottom corner pixel it should change velocity in x alone
					coll_x<='1';
				elsif(ball_y_vel='0' and ball_x_vel='0')then--if ball is going up and moving left and colliding with right bottom corner pixel it should change velocity in both x & y
					coll_x<='1';
					coll_y<='1';
				else
					null;
				end if;
				draw<='0';
				r<="0000";
				g<="0000";
				b<="0000";
			else
				null;
			end if;
		else
			null;
		end if;
		
	end brick;


procedure bat(signal hpos_scr,vpos_scr, xpos,ypos:in integer; signal draw:out std_logic; signal r,g,b:out std_logic_vector(3 downto 0)) is--Procedure to assign draw,rgb signals of the bat

begin
		
	if(hpos_scr>=xpos and hpos_scr<xpos+50 and vpos_scr>=ypos and vpos_scr<ypos+4)then
		draw<='1';
		r<="1111";
		g<="1111";
		b<="1111";
	else
		draw<='0';
		r<="0000";
		g<="0000";
		b<="0000";
	end if;
end bat;

procedure ball(signal hpos_scr,vpos_scr, ball_x,ball_y:in integer; signal ball_row,ball_col:out integer) is--Procedure to map current pixel location to BALL_ROM's row/col
	begin

		if((ball_x<=hpos_scr) and (hpos_scr<ball_x+13) and (ball_y<=vpos_scr) and (vpos_scr<ball_y+13)) then
			ball_row <= vpos_scr - ball_y;
			ball_col <= hpos_scr - ball_x;
		else
			null;
		end if; 
end ball;

procedure gameover(signal hpos_scr,vpos_scr,gameover_x,gameover_y:in integer; signal gameover_row,gameover_col:out integer) is--Procedure to map current pixel location to GAMEOVER_ROM's row/col
	begin

		if((gameover_x<=hpos_scr) and (hpos_scr<gameover_x+472) and (gameover_y<=vpos_scr) and (vpos_scr<gameover_y+90)) then
			gameover_row <= vpos_scr - gameover_y;
			gameover_col <= hpos_scr - gameover_x;
		else
			null;
		end if; 
end gameover;

procedure lives(signal hpos_scr,vpos_scr,lives_x,lives_y:in integer; signal lives_row,lives_col:out integer) is--Procedure to map current pixel location to LIVES_ROM's row/col
	begin

		if((lives_x<=hpos_scr) and (hpos_scr<lives_x+92) and (lives_y<=vpos_scr) and (vpos_scr<lives_y+25)) then
			lives_row <= vpos_scr - lives_y;
			lives_col <= hpos_scr - lives_x;
		else
			null;
		end if; 
end lives;

procedure welmes(signal hpos_scr,vpos_scr,welmes_x,welmes_y:in integer; signal welmes_row,welmes_col:out integer) is--Procedure to map current pixel location to WELCOME_ROM's row/col
	begin

		if((welmes_x<=hpos_scr) and (hpos_scr<welmes_x+496) and (welmes_y<=vpos_scr) and (vpos_scr<welmes_y+390)) then
			welmes_row <= vpos_scr - welmes_y;
			welmes_col <= hpos_scr - welmes_x;
		else
			null;
		end if; 
end welmes;

procedure winmes(signal hpos_scr,vpos_scr,winmes_x,winmes_y:in integer; signal winmes_row,winmes_col:out integer) is--Procedure to map current pixel location to WIN_ROM's row/col
	begin

		if((winmes_x<=hpos_scr) and (hpos_scr<winmes_x+460) and (winmes_y<=vpos_scr) and (vpos_scr<winmes_y+130)) then
			winmes_row <= vpos_scr - winmes_y;
			winmes_col <= hpos_scr - winmes_x;
		else
			null;
		end if; 
end winmes;

procedure paused(signal hpos_scr,vpos_scr,paused_x,paused_y:in integer; signal paused_row,paused_col:out integer) is--Procedure to map current pixel location to PAUSE_ROM's row/col
	begin

		if((paused_x<=hpos_scr) and (hpos_scr<paused_x+384) and (paused_y<=vpos_scr) and (vpos_scr<paused_y+76)) then
			paused_row <= vpos_scr - paused_y;
			paused_col <= hpos_scr - paused_x;
		else
			null;
		end if; 
end paused;

end game;