#ifndef FINAL_MAZE
#define FINAL_MAZE

#include <iostream>
#include <map>
#include "room.h"

class Final_maze{                                   //класс лабиринта с комнатами
private:
    int _len;
    int _wig;
    int _count_of_types;
    Maze maze;
    int** m;
    int** under;
    int** right;
    std::vector<Room> rooms;
    Cord _begin;
    std::map<int, std::vector<Exit>> exits_room;                //выходы из комнат
    std::map<int, std::vector<std::pair<int, Exit>>> rooms_;    //структура для хранения связей между комнатами: номер_комнаты (номер связанной комнаты, выход в данную комнату)
    std::vector<int> path;
public:
    Final_maze(int len, int wig, int count): _len(len), _wig(wig), _count_of_types(count), maze(len, wig), _begin(0,0){
        m = maze.filling_maze();
        under = maze.getUnder();
        right = maze.getRight();
    }
    ~Final_maze(){
    }
    std::vector<Room> getRooms() {return rooms;}            //получение вектора комнат лабиринта
    void filling_by_rooms();                                //разделение лабиринта на комнаты
    void new_room();                                        //создание одной комнаты
    int indentifier();                                      // определение типа комнаыты: 1 - горизонтальная, 0 - вертикоальная
    void create_begin();                                    //определение точки начала комнаты
    void create_hor_room();                                 //создание горизонтальной комнаты
    void create_ver_room();                                 //создание вертикальной комнаты
    int check_maze();                                       //проверка факт полного разбиения на комнаты(нет областей, не принадлежащих комнатам)
    void find_common_exits();                               //поиск общих выходов комнат       
    void find_path(int first_room, int final_room);         //поиск пути в лабиринте по 2 заданным номерам
    int find_room(Cord &first);                             //поиск комнаты по заданной точке
    std::vector<int> getWay(){return path;}                 //получение пути
    std::map<int, std::vector<std::pair<int, Exit>>> getRoomsConnect(){return rooms_;}      //получение связи между комнатами
};


#endif //FINAL_MAZE
