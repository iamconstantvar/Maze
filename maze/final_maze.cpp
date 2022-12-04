#include "final_maze.h"
#include <queue>
#include <cstring>
#include <algorithm>


void Final_maze::find_common_exits(){
    std::vector<Exit> exits_of_room;
    Exit ex;
    for (int i = 0; i < rooms.size(); i++)
    {
        exits_of_room = rooms[i].getExits();
        for(int j = 0; j < exits_of_room.size(); j++) {
            ex = exits_of_room[j];
            for (int k = i + 1; k < rooms.size(); k++) {
                for(int n = 0; n < rooms[k].getExits().size(); n++) {
                if (ex == rooms[k].getExits()[n]) {
                    rooms_[i].push_back(std::make_pair(k, ex));
                    rooms_[k].push_back(std::make_pair(i, ex));
                    }
                }
            }
        }
    }
}

int Final_maze::check_maze() {
    int count = 0;
    int i = 0, j = 0;
    for( i = 0; i < _wig; i++)
        for(j = 0; j < _len; j++)
            count += (m[i][j] == 9) ? 0 : 1;
return count;
}

void Final_maze::filling_by_rooms() {
   while (check_maze() != 0)
        new_room();
    
}

int Final_maze::indentifier(){
    int y = _begin.getY();
    int x = _begin.getX();                                                 // 1 - горизонтальная комната,  0 - вертикальная комната
    if (x != (_wig - 1) && (under[x][y] == 1 || m[x + 1][y] == 9))         //условие горизонтальности комнаты
        return 1;
    if (y != (_len - 1) && (right[x][y] == 1 || m[x][y + 1] == 9)) {        //условие вертикальности комнаты
        return 0;
    }
    if (x == _wig - 1)
        return 1;
    if (y == _len - 1)
        return 0;
    return 0;
}


void Final_maze::new_room() {
    int x = indentifier();
    if (x == 1)
        create_hor_room();
    else
        create_ver_room();  
}

void Final_maze::create_begin() {
    int x = _begin.getX();
    int y = _begin.getY();
    if (y >= _len) {
        y = 0;
        x++;
    }
    x = (x > _wig - 1) ? 0 : x;
    while(m[x][y] == 9 && check_maze() != 0) {
    
        y++;
        if (y >= _len) {
        y = 0;
        x++;
    }
        x = (x > _wig - 1) ? 0 : x;
    }
    if (x > _wig - 1 && y > _len - 1){
        x = 0;
        y = 0;
    }

    Cord b(x, y);
    _begin = b;

}


void Final_maze::create_ver_room() {
    int y = _begin.getY();
    int x = _begin.getX();
    int x0 = x;
    int y0= y;
    int len = 0;
    std::vector<Exit> exits;
    Cord new_beg(x, y + 1);
    _begin = new_beg;
    int flag = 1;
    for(int i = x; x < _wig && m[x][y] != 9; x++) {
        len++;
        if (x == x0 && x > 0 && under[x - 1][y] == 0) {
            Exit tmp(x - 1, y, 0);
            exits.push_back(tmp);
        }
        if (y > 0) {
            flag = (right[x][y - 1] == 0) ? 0 : 1;                //если сверху есть горизонтальная граница, возвращем 0, иначе 1
        }
        else {
            flag = 1;
        }                                                       
        if (flag == 0){                         //если нет границы слева, +1 новый выход
            Exit tmp(x, y - 1, 1);
            exits.push_back(tmp);
        }
        if (right[x][y] == 0) {                         
            Exit tmp(x, y, 1);
            exits.push_back(tmp);
        }

        if (under[x][y] == 1) {
            m[x][y] = 9;
            break;
        }
        m[x][y] = 9;
    }
    if (x < _wig && y < _len && under[x][y] == 0) {                         //если нет границы снизу или сверху, +1 новый выход
            Exit tmp(x, y, 0);
            exits.push_back(tmp);
    }
    Cord b(x0, y + 1);
    _begin = b;
    create_begin();
    Room r(len, 0, exits, x0, y0, (rooms.size() + 1)% _count_of_types);
    rooms.push_back(r);  
    exits_room[rooms.size() - 1] = exits;
    
}

void Final_maze::create_hor_room() {
    int y = _begin.getY();
    int x = _begin.getX();
    int len = 0;
    std::vector<Exit> exits;
    int flag, f = 0;
    int x0 = x;
    int y0= y;
    for(int y_l = y; y_l < _len && m[x][y_l] != 9; y_l++) {
        len++;
        if (y_l == y0 && y_l > 0 && right[x][y_l - 1] == 0) {
            Exit tmp(x, y_l - 1, 1);
            exits.push_back(tmp);
        }
        if (x > 0) {
            flag = (under[x - 1][y_l] == 0) ? 0 : 1;                //если сверху есть горизонтальная граница, возвращем 0, иначе 1
        }
        else {
            flag = 1;
        }                                               
        if (flag == 0){                         //если нет границы снизу или сверху, +1 новый выход
            Exit tmp(x - 1, y_l, 0);
            exits.push_back(tmp);
        }
        if (under[x][y_l] == 0){                         //если нет границы снизу или сверху, +1 новый выход
            Exit tmp(x, y_l, 0);
            exits.push_back(tmp);
        }

        if (right[x][y_l] == 1) {
            m[x][y_l] = 9;
            f = 1;
            break;
        }
        m[x][y_l] = 9;
        y++;
    }
    if (f == 0) {
        y--;
    }
    if (x < _wig && y < _len && right[x][y] == 0) {                         //если нет границы снизу или сверху, +1 новый выход
            Exit tmp(x, y, 1);
            exits.push_back(tmp);
    }
    Room r(len, 1, exits, x0, y0, (rooms.size() + 1)% _count_of_types);
    rooms.push_back(r);
    Cord new_beg(x, y + 1);
    _begin = new_beg;
    create_begin();
    exits_room[rooms.size() - 1] = exits;
}

int Final_maze:: find_room(Cord &first) {
    int ind;
    int number_of_room;
    int x0, y0, len;
    int x = first.getX();
    int y = first.getY();
    for( int i = 0; i < rooms.size(); i++) {
        ind = rooms[i].getInd();
        x0 = rooms[i].getBegin().getY();
        y0 = rooms[i].getBegin().getX();
        len = rooms[i].getLen();
       if ( x - 1 >= x0  && y - 1 >=  y0) {
            if (ind == 1) {
                if (x - 1 < x0 + len  && y - 1 == y0) {
                    number_of_room = i;
                    break;
                }
            }
            else {
                if (x - 1 == x0 && y - 1 <  y0 + len) {
                    number_of_room = i;
                    break;
                }
            }
       }
    }
    return number_of_room;
}

void Final_maze::find_path(int first_room, int final_room) {
    find_common_exits();
    bool visited[rooms.size()];
    memset(visited, false, rooms_.size());
    std::vector<int>pred(rooms.size(), -1);
    std::vector<int> dist(rooms.size(), rooms.size()); 
    std::queue<int> q;
    dist[first_room] = 0;
    pred[first_room] = -1;
    visited[first_room] = true;
    q.push(first_room);
    int v, k;
    while(!q.empty()) {
        v = q.front();
        q.pop();
        for(int i = 0; i < rooms_[v].size(); i++) {
            k = rooms_[v][i].first;
            if(!visited[k]) {
                q.push(k);
                visited[k] = true;
                dist[k] = dist[v] + 1;
                pred[k] = v;
            }
        }
    }
    int cur = final_room;
    while (pred[cur] != -1) {
        cur = pred[cur];
        path.push_back(cur);
    }
    std::reverse(path.begin(), path.end());
    path.push_back(final_room);
}

