#include "picture.h"
#include <cmath>

using namespace cv;

void Picture::print(){
    _maze.find_common_exits();
    img += cv::Scalar(EXITS);
    color_of_room();
    print_rooms();
    print_exits();
    imwrite("maze.png", img); 
}

Scalar randomColor(int h) {   
    double s = rand() % 360 / 100.;
    double l = 0.85;
    double r = 0, g = 0, b = 0;
	double c = (1 - fabs(2 * l - 1)) * s ;
    double x = c * (1 - fabs(fmod((h / 60.0), 2) - 1));
    double m = l - c / 2;
    if (h >= 0 && h < 60) {
        r = c;
        g = x;
    }
    else if (h >= 60 && h < 120) {
        r = x;
        g = c;
    }
    else if (h >= 120 && h < 180) {
        g = c;
        b = x;
    }
    else if (h >= 180 && h < 240) {
        g = x;
        b = c;
    }
    else if (h >= 240 && h < 300) {
        r = x;
        b = c;
    }
    else if (h >= 300 && h < 360) {
        r = c;
        b = x;
    }
    int R = (r + m) * 255;
    int G = (g + m) * 255;
    int B = (b + m) * 255;
    return Scalar(B, G, R);   
}

void Picture::print_rooms(){
    int ind;
    int l;
    int w;
    int x0;
    int y0;
    for (int j = 0; j < rooms.size(); j++) {
        ind = rooms[j].getInd(); 
        if (ind == 1) {
            w = _line;
            l = rooms[j].getLen() * _line;
        }
        else {
            l = _line;
            w = rooms[j].getLen() * _line;
        }
        x0 = rooms[j].getBegin().getY() * _line;
        y0 = rooms[j].getBegin().getX() * _line;
        rectangle(img, Point(x0, y0), Point(x0 + l, y0 + w),  Scalar(WALLS), _widht);
        rectangle(img, Point(x0 + _widht, y0 + _widht), Point(x0 + l - _widht, y0 + w - _widht),  color[rooms[j].getType()], -1);
    }
}

void Picture::color_of_room() {
    std::vector<int> hue;
    int step = 360 / _colors;
    int interval = 0;
    color.push_back(Scalar(200, 200, 200));
    for (int i = 0; i < _colors - 1; i++) {
        hue.push_back(rand() % step + interval);
        interval += step;
    }
    for (int i = 0; i < _colors - 1; i++) {
        color.push_back(randomColor(hue[i]));
    }
}

void Picture::print_way(Cord &first_point, Cord &final_point) {
    int x0, y0, y, x, x_cord, y_cord, x0_cord, y0_cord;
    _maze.find_path(_maze.find_room(first_point), _maze.find_room(final_point));
    int x_first = (first_point.getX() - 1) * _line + _line / 2;
    int y_first = (first_point.getY() - 1) * _line + _line / 2;
    int x_final = (final_point.getX() - 1) * _line + _line / 2;
    int y_final = (final_point.getY() - 1) * _line + _line / 2;
    Exit exit_of_room;
    Cord current_room(first_point.getX() - 1, first_point.getY() - 1);
    x0_cord = first_point.getX()*_line - _line / 2;
    y0_cord = first_point.getY()*_line - _line / 2;
    circle(img, Point(x_first, y_first), _line / 5, Scalar(WAY), -1);
    circle(img, Point(x_final, y_final), _line / 5, Scalar(WAY), -1);
    for (int c = 0; c < _maze.getWay().size() - 1; c++) {
        for(int i = 0; i < _maze.getRoomsConnect()[_maze.getWay()[c]].size(); i++) {
            if (_maze.getRoomsConnect()[_maze.getWay()[c]][i].first == _maze.getWay()[c+1]) {
                exit_of_room = _maze.getRoomsConnect()[_maze.getWay()[c]][i].second;
                break;
            }
        }
        x = exit_of_room.getY();
        y = exit_of_room.getX();        
        x0 = current_room.getX();
        y0 = current_room.getY();
        
        if(rooms[_maze.getWay()[c]].getInd()) {
            if(!exit_of_room.getInd()) {
                x_cord = x * _line + _line / 2;
                (y0_cord > y*_line + _line) ? (y_cord = y*_line + _line / 2) : (y_cord = y*_line + 3 * _line / 2); 
                line(img, Point(x0_cord, y0_cord), Point(x_cord, y0_cord), Scalar(WAY), _widht);
                line(img, Point(x_cord, y0_cord), Point(x_cord, y_cord), Scalar(WAY), _widht);
                x0_cord = x_cord;
                y0_cord = y_cord;
                Cord tmp(x,y);
                current_room = tmp;
            }
            else{
                (x0_cord > x*_line + _line) ? (x_cord = x*_line + _line / 2) : (x_cord = x*_line + 3 * _line / 2);
                line(img, Point(x0_cord, y0_cord), Point(x_cord, y0_cord), Scalar(WAY), _widht);
                x0_cord = x_cord;
                Cord tmp(x, y0);
                current_room = tmp;
            }
        }
        else{
            if(exit_of_room.getInd()) {
                (x0_cord > x*_line + _line) ? (x_cord = x*_line + _line / 2) : (x_cord = x*_line + 3 * _line / 2);
                y_cord = y*_line + _line / 2;
                line(img, Point(x0_cord, y0_cord), Point(x0_cord, y_cord), Scalar(WAY), _widht);
                line(img, Point(x0_cord, y_cord), Point(x_cord, y_cord), Scalar(COLOR_YUV2GRAY_420), _widht);
                x0_cord = x_cord;
                y0_cord = y_cord;
                Cord tmp(x,y);
                current_room = tmp;
            }
            else{
                (y0_cord >= y*_line + _line) ? (y_cord = y*_line  +  _line / 2) : (y_cord = y*_line  +  _line); 
                line(img, Point(x0_cord, y0_cord), Point(x0_cord, y_cord), Scalar(WAY), _widht);
                y0_cord = y_cord;
                Cord tmp(x0,y);
                current_room = tmp;      
            }
        }
    }
    if (y0_cord > y_final) {
        swap(y0_cord, y_final);
        swap(x0_cord, x_final);
    }
    line(img, Point(x0_cord, y0_cord), Point(x_final, y0_cord), Scalar(WAY), _widht);
    line(img, Point(x_final, y0_cord), Point(x_final, y_final), Scalar(WAY), _widht);
    imwrite("maze_way.png", img);
}


void Picture::print_exits(){
    int ind;
    int flag;
    int udlr;
    int x_e, y_e;
    for (int j = 0; j < rooms.size(); j++) {
        ind = rooms[j].getInd();
        for(int i = 0; i < rooms[j].getExits().size(); i++) {
            x_e = rooms[j].getExits()[i].getY();
            y_e = rooms[j].getExits()[i].getX();
            udlr = rooms[j].getExits()[i].getInd();
            if (udlr == 0) {                                        //горизонтальный выход
                    rectangle(img, Point(x_e*_line + _widht, y_e * _line + _line - _widht),
                     Point(x_e * _line + _line - _widht, y_e * _line + _line + _widht), color[rooms[j].getType()], -1);
                }
            else {                                                  //вертикальный выход
                    rectangle(img, Point(x_e * _line +  _line - _widht, y_e * _line + _widht), 
                    Point(x_e * _line + _line + _widht, y_e * _line + _line - _widht), color[rooms[j].getType()], -1);
            }
        }
    }
}
