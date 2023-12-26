/*GUI app that performs like a desktop Calculator but also performs Geometry based
calculations for a set list of shapes (Square, Rectangle, Circle, Triangle, Cube, 
Cuboid, Sphere, Right 3 Sided Pyramid, Right 4 Sided Pyramid).*/

#include "CalculatorPlusGeo.hpp"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CalculatorPlusGeo win;
    win.show();
    return QApplication::exec();
}
