#ifndef MAZE
#define MAZE

#include <vector>
#include"coordinates.h"


class Maze {
private:
    int _cols;
    int _row;
    int **under_maze;
    int **right_maze;
    int counter;
    int **maze;
    std::vector<int> new_str;
public:
    Maze(int lenght = 9, int wight = 9) : _cols(lenght), _row(wight) {
        under_maze = new int*[_row];
        right_maze = new int*[_row];
        counter = 1;
        for (size_t i = 0; i < _row; i++) {
            under_maze[i] = new int [_cols];
            right_maze[i] = new int[_cols];
        }
         for (size_t i = 0; i < _row; i++)
           { for (size_t j = 0; j < _cols; j++) {
                    under_maze[i][j] = 0;
                    right_maze[i][j] = 0;
                }
            }
        maze = new int*[_row];
        for (size_t i = 0; i <  _row; i++) {
            maze[i] = new int[_cols];
        }
     
       }
         ~Maze(){ 
            for(int i = 0; i < _row; i++) {
                delete [] under_maze[i];
                delete [] right_maze[i];
                delete [] maze[i];
            }
            delete [] under_maze;
            delete [] right_maze;
            delete [] maze;
    }
    int getLen() {return _cols;}
    int getRow() {return _row;}
    int** getUnder() {return under_maze;}
    int** getRight() {return right_maze;}
    void lots();
    int check_walls(int el);
    int count_hor_walls(int row, int el);
    void check_hor_walls(int row);
    void merge(int i, int el);
    void vertical_wall(int row);
    void horizon_wall(int row);
    void prepare_new_str(int row);
    void add_end();
    void check_end();
    void generate_maze();
    int** filling_maze();
};


#endif //MAZE
