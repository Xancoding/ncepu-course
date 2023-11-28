``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity and_gate is
	port(a,b,c:in bit; x: out bit);
end entity and_gate;

architecture logicfunction of and_gate is
begin
	x<=a and b and c;
end architecture logicfunction;
```