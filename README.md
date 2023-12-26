# CalculatorPlusGeo

GUI app that performs like a desktop Calculator but also performs Geometry based calculations for a set list of shapes (Square, Rectangle, Circle, Triangle, Cube, Cuboid, Sphere, Right 3 Sided Pyramid, Right 4 Sided Pyramid).

NOTE:
Currently does not support precise answers for very large or very small numbers from expressions such as 53^14 ie (pow(53, 14)) or .3^13 ie (pow(.3, 13)), not tested but appears that this begins to happen in numbers over 25 digits on the system ran -> considering this Library for the future: https://github.com/kothariji/BhimIntegers (may not cover small numbers, need to research)

Expressions are parsed / calculated with the Shunting Yard Algorithm and Reverse Polish Notation -> example: https://brilliant.org/wiki/shunting-yard-algorithm/

UI was created in the QT designer tool but some button handling was outside of the tool.
Qt docs -> https://doc.qt.io/

# Requirements

Qt 6.6.1


# TODO list

1. Linting.
2. Double check comments.
3. Add commas to expression browser?
4. Fix window size.