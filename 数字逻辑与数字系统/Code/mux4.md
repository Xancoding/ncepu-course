``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity mux4 is
	port(d0, d1, d2, d3, a, b: in std_logic; q: out std_logic);
end entity mux4;

architecture logicfunction of mux4 is
signal sel: std_logic_vector(1 downto 0);
begin
	sel<=a&b;
	q<=d0 when sel="00" else
	   d1 when sel="01" else
	   d2 when sel="10" else
	   d3 when sel="11" else
		           'Z';
end architecture logicfunction;
```

```vhdl
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity test is
	port(clk, x, clr: in std_logic;
		  z: out std_logic);
end entity test;

architecture ltest of test is
	type states is (s0, s1, s2);
	signal next_state:states;
begin
	process(clk, clr)
	begin
		if clr='1' then
			next_state<=s0;
		elsif(clk'event and clk='1') then
			case next_state is
				when s0=>
					if x='0' then
						z<='0';
						next_state<=s0;
					else
						z<='0';
						next_state<=s1;
					end if;
				when s1=>
					if x='0' then
						z<='0';
						next_state<=s0;
					else
						z<='0';
						next_state<=s1;
					end if;
				when s2=>
					if x='0' then
						z<='0';
						next_state<=s0;
					else
						z<='0';
						next_state<=s1;
					end if;
			end case;
		end if;
	end process;
end architecture ltest;
```