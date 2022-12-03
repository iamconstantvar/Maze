#include "picture.h"
#include <fstream>

/*template<class T>
inline void readParameter(istream& i, T& v) {
  i >> v;
};
*/
class Parsing {
private:
    int _len;
    int _wig;
    int _types;
    Cord _first_point;
    Cord _final_point;
    std::string name_of_file;
public:
    Parsing(std::string name = NULL, int l = 5, int w = 5, int t = 1):name_of_file(name), _len(l), _wig(w), _types(t){};
    void parse();
    int getLen(){return _len;}
    int getWid(){return _wig;}
    int getType() {return _types;}
    int key_of_data(std::string result);
    Cord& getFirst() {return _first_point;}
    Cord& getFinal() {return _final_point;}
};

int Parsing::key_of_data(std::string result) {
    
}

void Parsing::parse() {
    std::ifstream infile(name_of_file);
    if ( !infile ) {
            std::cout << "Error in opening file!" << std::endl;
            exit;
    }
    std::string token;
    std::string data_from_str;
    while(std::getline(infile, data_from_str, '\n')) {
        std::istringstream iss(data_from_str);

        std::string result;
        if( std::getline( iss, result , ':') ) {
            if( result == "lenght" || result == "длина" ) {
                std::getline(iss, token);
                _len = std::stoi(token);
            }
            else if( result == "wight"|| result == "ширина" ) {
                std::getline( iss, token);
                _wig = std::stoi(token);
            }
            else if( result == "colors" || result == "types" || result == "количество типов") {
                std::getline( iss, token);
                _types = std::stoi(token);
            }
            else if( result == "Begin" || result == "Начальная точка" || result == "End" || result == "Конечная точка") {
                int i = 0;
                int cords[2];
                while( std::getline( iss, token, ';' ) &&  i < 2) {
                    cords[i] = stoi(token);
                    i++;
                }
                (result == "Begin" || result == "Начальная точка") ? _first_point = Cord(cords[0], cords[1]) :
                _final_point = Cord(cords[0], cords[1]);
            }
        }
        data_from_str.clear();
        token.clear();
    }
    
    infile.close();
}

int main(int argc, char** argv) {
    int s;
    int length, wigth, color;
    Cord first_cord;
    Cord final_cord;
    if (argc < 2) {
        system("clear");
        while (!(std::cout << "Длина лабиринта:  \033[19G   ширина лабиринта: \033[18G") || 
        !(std::cin >> length) || length < 1 || !(std::cout << "\033[0;40H") || !(std::cin >> wigth) || wigth < 1) {
            system("clear");
            std::cin.clear();
            std::cin.ignore();
        }
        std::cout << "Введите количество типов покрытия" << std::endl; 
        std::cin >> color;
        std::cout << "Введите начальную точку пути: " << std::endl;
        std::cin >> first_cord;
        std::cout << "Введите конечную точку пути: " << std::endl;
        std::cin >> final_cord;
    }
    else {
        srand(time(NULL));
        Parsing new_maze(argv[1]);
        new_maze.parse();
        length = new_maze.getLen();
        wigth = new_maze.getWid();
        color = new_maze.getType();
        first_cord = new_maze.getFirst();
        final_cord = new_maze.getFinal();
    }
    Picture m(length, wigth, color);
    m.print();
    m.print_way(first_cord, final_cord);
    return 0;
}
