--Brick_Breaker.vhd
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity brick_breaker is--Top level design entity
	port(clk:in std_logic;
			r_shift,l_shift,start,resetgame,pause:in std_logic;
			level_select:in std_logic_vector(2 downto 0);
			hsync,vsync:out std_logic;
			r,g,b:out std_logic_vector(3 downto 0));
end brick_breaker;

architecture brick_breaker_arch of brick_breaker is
	
	component sync is--Synchronization component synchronizing every signal @~25.175Mhz
		port(clk_s:in std_logic;
				r_shift,l_shift,start,resetgame,pause:in std_logic;
				level_select:in std_logic_vector(2 downto 0);
				hsync,vsync:out std_logic;
				r,g,b:out std_logic_vector(3 downto 0));
	end component;
	
	component pll is--PLL component to generate ~25.175Mhz clock
        port (
            clk_in_clk  : in  std_logic := 'X'; -- clk
            reset_reset : in  std_logic := 'X'; -- reset
            clk_out_clk : out std_logic         -- clk
        );
    end component pll;
	 	
	signal reset,clk_s:std_logic;
	begin
		
		S1: sync port map(clk_s,r_shift,l_shift,start,resetgame,pause,level_select,hsync,vsync,r,g,b);
		u0 : component pll
        port map (
            clk_in_clk  => clk,  --  clk_in.clk
            reset_reset => reset, --   reset.reset
            clk_out_clk => clk_s  -- clk_out.clk
        );	
end brick_breaker_arch;