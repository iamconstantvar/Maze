#include"coordinates.h"


std::istream& operator>> (std::istream &in, Cord &point) {
    char sep;
    in >> point._x;
    in >> sep;
    in >> point._y;
    return in;
}

Cord& Cord::operator=(Cord c) {
    _x = c.getX();
    _y = c.getY();
    return *this;
}

int Cord::operator== (Cord c) {
    if (_x == c.getX() && _y == c.getY())
        return 1;
    return 0;
}

Exit& Exit::operator=(Exit c) {
    _x = c.getX();
    _y = c.getY();
    _ind = c.getInd();
    return *this;
}
int Exit::operator== (Exit c) {
    if (_x == c.getX() && _y == c.getY() && _ind == c.getInd())
        return 1;
    return 0;
}
