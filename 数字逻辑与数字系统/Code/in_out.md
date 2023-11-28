``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity in_out is
	port(in1, in2, in3, in4, in5, in6, in7: in bit;x: out bit);
end entity in_out;

architecture logicfunction of in_out is
begin
	x<=(in1 and in2 and in3)or(in4 and in5)or(in6 and in7);
end architecture logicfunction;
```