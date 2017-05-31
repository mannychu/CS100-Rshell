UCR CS100 Legacy Shell
================

Authors
-------
Immanuel Chu
ichu003@ucr.edu

David Weber 
dwebe003@ucr.edu

Repository
--------
http://github.com/mannychu/rshell.git

Summary
--------
***rshell*** is a pseudo bash replica. It is a command shell prompt that is able to 
implement native BASH commands. The program reads in valid commands from user input
and executes them how a normal BASH would.

Commands Syntax:
```
executable [ argumentList ] [ connector cmd ]
```
Available Connectors:
```
&& , || , ;
```
Comments are also supported in ***rshell***. 
To define a comment, place "#" before the command and everything after "#" will be commented.

Connector Descriptions
--------
&& (AND) - given two valid commands, the second executes if and only if the first command succeeds. <br/>
|| (OR) - given two valid commands, the second executes if and only if the first command fails.
<br/>
; (SEMICOLON) - given two valid commands, both successfully execute.<br/>

Test Scripts
--------
To test ***rshell*** we have created multiple testing scripts to ensure our program functions as expected. 

To run a script, navigate into the tests directory and enter the following:
```
./<script_name>
```
List of available scripts

```
single_command.sh...........tests single commands
multi_command.sh............tests commands with connectors (&&, ||, and/or ;)
commented_command.sh........tests commands containing comments
exit.sh.....................tests exit and commands with exit
test_test.sh................tests the test command
precedence_test.sh..........tests the precedence boundaries
```

Running rshell
--------
In order to run ***rshell***, open up your terminal and type these commands after navigating
to your desired directory.
```
1. git clone https://github.com/mannychu/rshell.git
2. cd rshell
3. make
4. ./bin/rshell
```
Congratulations! ***rshell*** is now running and you are not able to run BASH commands


Bugs
--------
None...so far...

Licensing Information
--------
GNU GENERAL PUBLIC LICENSE

Version 3, 29 June 2007

***rshell*** - a pseudo bash terminal program

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.