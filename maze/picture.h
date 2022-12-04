#ifndef PICTURE
#define PICTURE

#include "final_maze.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#define WALLS 0, 0, 0
#define EXITS 255, 255, 255
#define WAY 100, 20, 25


static int widht = 900;

class Picture{
private:
    Final_maze _maze;
    std::vector<Room> rooms;
    std::vector<cv::Scalar> color;
    cv::Mat img;
    int _len, _wig;
    int _line;
    int _widht;
    int _colors;
public:
    Picture(int len, int wig, int colors) : _maze(len, wig, colors), _len(len), _wig(wig), _colors(colors){
        _line = (len > wig) ? (widht / len) : (widht / wig);
        int l = len * _line *(1 + 0.003);
        _widht = l * 0.003;
        _widht= (_widht < 2 || _widht >= _line / 3) ? 2 : _widht;
        cv::Mat iimg(wig * _line + _widht, l, CV_8UC3);
        img = iimg;
        _maze.filling_by_rooms();
        rooms = _maze.getRooms();
    }
    void print();
    void print_rooms();
    void print_exits();
    void print_way(Cord &first_point, Cord &final_point);
    void color_of_room();
};



#endif //PICTURE
