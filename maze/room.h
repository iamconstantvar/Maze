#ifndef ROOM
#define ROOM

#include <iostream>
#include "maze.h"



class Room{
private:
    int _len;
    int _ind;
    std::vector<Exit> exits;
    Cord _begin;
    int _type;
public:
    Room(int len, int ind, std::vector<Exit> exit, int x, int y, int t): _len(len), _ind(ind), exits(exit), _type(t){
        Cord b(x, y);
        _begin = b;
    }
    Cord getBegin() {return _begin;}
    std::vector<Exit> getExits(){return exits;}
    int getLen(){return _len;}
    int getInd(){return _ind;}
    int getType() {return _type;}
};

#endif //ROOM
