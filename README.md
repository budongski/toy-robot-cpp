# toy robot coding challenge

## Description and requirements:

The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. There are no  
other obstructions on the table surface. The robot is free to roam around the surface of the table, but must be prevented  
from falling to destruction. Any movement that would result in the robot falling from the table must be prevented,  
however further valid movement commands must still be allowed.  
Create a console application that can read in commands of the following form -  
  
PLACE X,Y,F  
MOVE  
LEFT  
RIGHT  
REPORT  
  
PLACE will put the toy robot on the table in position X,Y and facing NORTH, SOUTH, EAST or WEST. The origin (0,0)  
can be considered to be the SOUTH WEST most corner. It is required that the first command to the robot is a PLACE  
command, after that, any sequence of commands may be issued, in any order, including another PLACE command. The  
application should discard all commands in the sequence until a valid PLACE command has been executed.  
MOVE will move the toy robot one unit forward in the direction it is currently facing.  
LEFT and RIGHT will rotate the robot 90 degrees in the specified direction without changing the position of the robot.  
REPORT will announce the X,Y and F of the robot. This can be in any form, but standard output is sufficient.  
A robot that is not on the table can choose to ignore the MOVE, LEFT, RIGHT and REPORT commands.  
Input can be from a file, or from standard input, as the developer chooses.  
  
### Constraints
The toy robot must not fall off the table during movement. This also includes the initial placement of the toy robot. Any  
move that would cause the robot to fall must be ignored.  

### Visual Studio projects included. Compiles on vs2019 toolset, C++ 17.

### Design
ToyRobotSim class in the testapp project provides a high level view of the design and important components.

https://github.com/budongski/toy-robot-cpp/blob/611c33968094a4c519b70c237244d3119c53c04a/src/toyrobotsim_testapp/toyrobotsim.cpp#L40-L137


