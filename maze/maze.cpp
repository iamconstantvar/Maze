#include "maze.h"


void Maze::prepare_new_str(int row) {
    for (int i = 0; i < _cols; i++) {
        if (under_maze[row][i] == 1)
            new_str[i] = 0;
    }
}

void Maze::horizon_wall(int row) {
     for(int i = 0; i < _cols; i++){
        int maybe_wall = rand() % 2;
        if (maybe_wall == 1 && check_walls(new_str[i]) != 1)
            under_maze[row][i] = 1;
    }
    
}

int Maze::check_walls(int el) {
    int counter_1 = 0;
    for (int i = 0; i < _cols; i++) {
        if (new_str[i] == el)
            counter_1++;
    }
    return counter_1;

}

void Maze::check_hor_walls(int ro){
    for(int i = 0; i < _cols; i++) {
        if(count_hor_walls(ro, new_str[i]) == 0)
            under_maze[ro][i] = 0;
    }
}

int Maze::count_hor_walls(int ro, int el) {
    int c = 0;
    for(int i = 0; i < _cols; i++) {
        if(new_str[i] == el && under_maze[ro][i] == 0)
            c++;
    }
    return c;
}

void Maze::lots() {
    for( int i = 0; i < _cols; i++){
            if (new_str[i] == 0) {
                new_str[i] = (counter);
                counter++;
            }
    }
}

void Maze::vertical_wall(int row) {

    for(int i = 0; i < _cols - 1; i++){
        int maybe_wall = rand() % 2;
        if (maybe_wall == 1 || new_str[i] == new_str[i + 1]) {
            right_maze[row][i] = 1;
        }
        else
            merge(i, new_str[i]);
    }
    right_maze[row][_cols - 1] = 1;
    
}

void Maze::merge(int i, int el){
    int cord = new_str[i + 1];
    for (int j = 0; j < _cols; j++) {
        if (new_str[j] == cord)
            new_str[j] = el;
    }
}

void Maze::add_end(){
    lots();
    vertical_wall(_row - 1);
    check_end();
}

void Maze::check_end() {
    for (int i = 0; i < _cols - 1; i++) {
        if (new_str[i] != new_str[i + 1]) {
            right_maze[_row - 1][i] = 0;
            merge(i, new_str[i]);
        }
        under_maze[_row - 1][i] = 1;
    }
    under_maze[_row - 1][_cols - 1] = 1;
}


void Maze::generate_maze() {
    for( int i = 0; i < _cols; i++)
        new_str.push_back(0);
    for (int i = 0; i < (_row - 1); i++) {
        lots();
        vertical_wall(i);
        horizon_wall(i);
        check_hor_walls(i);
        prepare_new_str(i);
    }
    add_end();
    //right_maze[_row - 1][_cols - 1] = 1;
}

int** Maze::filling_maze() {
    generate_maze();
    for (int i = 0; i < _row; i++)
        for (int j = 0; j < _cols; j++) {
            maze[i][j] = 0;
        }  
    return maze;
}