# CalculatorPlusGeo

GUI app that performs like a desktop Calculator but also performs Geometry based calculations for a set list of shapes (Square, Rectangle, Circle, Triangle, Cube, Cuboid, Sphere, Right 3 Sided Pyramid, Right 4 Sided Pyramid).

NOTE:
Currently does not support precise answers for very large or very small numbers from expressions such as 53^14 ie (pow(53, 14)) or .3^13 ie (pow(.3, 13)), not tested but appears that this begins to happen in numbers over 25 digits on the system ran -> considering this Library for the future: https://github.com/kothariji/BhimIntegers (may not cover small numbers, need to research)

Expressions are parsed & calculated with the Shunting Yard Algorithm and Reverse Polish Notation
Shunting Yard wiki:https://en.wikipedia.org/wiki/Shunting_yard_algorithm 
RPN wiki: https://en.wikipedia.org/wiki/Reverse_Polish_notation

UI was created in the QT designer tool but some button handling was outside of the tool.
Qt docs -> https://doc.qt.io/

# Requirements to run

64bit system (built on Windows not tested for other platforms)

To run the debug build you need these .dll files in the folder with the .exe
Qt6Widgetsd.dll
Qt6Guid.dll
Qt6Cored.dll

additionally you need to add the Qt plugins folder to the .exe directory
for example add this folder to folder holding the .exe:
C:\Qt\6.6.1\msvc2019_64\plugins


# Long Term TODO

1. Could change RPNEval function to use two iterators and maybe not restart from beginning of the shuntyard queue?
1. Switch to token based formatting? <-- probably less complex
1. Large number implementation?