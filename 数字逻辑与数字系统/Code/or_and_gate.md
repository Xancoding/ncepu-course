### OR_GATE
``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity or_gate is
	port(a, b: in bit; x: out bit);
end entity or_gate;

architecture logicfunction of or_gate is
begin
	x<=a or b;
end architecture logicfunction;
```
### AND_GATE
``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity and_gate is
	port(a, b: in bit; x: out bit);
end entity and_gate;

architecture and_function of and_gate is
begin
	x<=a and b;
end architecture and_function;
```
### OR_AND_GATE
``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity or_and_gate is
	port(in1, in2, in3, in4: in bit; out3: out bit);
end entity or_and_gate;

architecture logicfunction of or_and_gate is

component and_gate is
	port(a, b: in bit; x: out bit);
end component and_gate;

component or_gate is
	port(a, b: in bit; x: out bit);
end component or_gate;

signal out1, out2: bit;

begin
	g1: and_gate port map(a=>in1, b=>in2, x=>out1);
	g2: and_gate port map(a=>in3, b=>in4, x=>out2);
	g3: or_gate port map(a=>out1, b=>out2, x=>out3);
end architecture logicfunction;
```