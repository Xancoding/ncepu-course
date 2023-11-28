```vhdl
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity test is
	port(D:in std_logic_vector(0 to 7);
		  CLK: in std_logic;
		  Q:out std_logic_vector(0 to 7));
end entity test;

architecture lreg of test is
	begin
		process(clk)
			begin
				if (clk'event and clk='1') then
					Q<=D;
				else
				end if;
		end process;
end architecture lreg;
```

```vhdl
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity test is
	port(in2:in std_logic_vector(0 to 1);
		  out4:out std_logic_vector(0 to 3));
end entity test;

architecture ltest of test is
begin
	out4<="1110" when in2="00" else
			"1101" when in2="01" else
			"1011" when in2="10" else
			"0111" when in2="11" else
			"ZZZZ";
end architecture ltest;
```