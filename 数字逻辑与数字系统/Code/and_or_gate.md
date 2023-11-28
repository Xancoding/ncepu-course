### AND3_GATE
``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity and3_gate is
    port(a, b, c: in bit; x: out bit);
end entity and3_gate;

architecture logicfunction of and3_gate is
begin
    x <= a and b and c;
end architecture logicfunction;
```
### AND2_GATE
``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity and2_gate is
    port(a, b: in bit; x: out bit);
end entity and2_gate;

architecture logicfunction of and2_gate is
begin
    x <= a and b;
end architecture logicfunction;
```
### OR3_GATE
``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity or3_gate is
    port(a, b, c: in bit; x: out bit);
end entity or3_gate;

architecture logicfunction of or3_gate is
begin
    x <= a or b or c;
end architecture logicfunction;
```
### AND_OR_GATE
``` VHDL
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity and_or_gate is
    port(in1, in2, in3, in4, in5, in6, in7: in bit; out4: out bit);
end entity and_or_gate;

architecture logicfunction of and_or_gate is

component and3_gate is
    port(a, b, c: in bit; x: out bit);
end component and3_gate;

component and2_gate is
    port(a, b: in bit; x: out bit);
end component and2_gate;

component or3_gate is
    port(a, b, c: in bit; x: out bit);
end component or3_gate;

signal out1, out2, out3: bit;

begin
    g1: and3_gate port map(a=>in1, b=>in2, c=>in3, x=>out1);
    g2: and3_gate port map(a=>in4, b=>in5, c=>in3, x=>out2);
    g3: and2_gate port map(a=>in6, b=>in7, x=>out3);
    g4: or3_gate port map(a=>out1, b=>out2, c=>out3, x=>out4);
end architecture and_or_gate;
```