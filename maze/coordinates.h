#ifndef COORDINATES
#define COORDINATES

#include <iostream>


class Cord{                                   //класс координат
protected:
    int _x, _y;
public:
    Cord(int x = 0, int y = 0): _x(x), _y(y){}
    int getX(){return _x;}
    int getY(){return _y;}
    Cord& operator=(Cord c);
    int operator==(Cord c);
    friend std::istream& operator>> (std::istream &in, Cord &point);
};


class Exit: public Cord{        //класс выхода
private:
    int _ind;                   //1 - вертикальный выход, 0 - горизонтальный 
public:
    Exit(int x = 0, int y = 0, int ind = 0): _ind(ind){
        _x = x;
        _y = y;
    }
    int getInd(){return _ind;}
    int operator==(Exit c);
    Exit& operator=(Exit c);
};

#endif //COORDINATES
