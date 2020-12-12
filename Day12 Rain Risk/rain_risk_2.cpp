#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

using u8 = uint8_t;

enum class Dir : int {
    N = 0,
    E = 1,
    S = 2,
    W = 3
};

struct State {
    int x, y;
    void rotate(int deg){
        int rot = deg / 90;
        rot &= 3;
        for(u8 i = 0; i < rot; i++){
            rotateRight();
        }
    }
private:
    void rotateRight(){
        int x, y;
        /* rotation matrix for 90 degrees right
          {{x},{y}} =
        {{0, 1},
         {-1, 0}} *
         {{x_prev},{y_prev}};
         */
        x = this->y;
        y = -this->x;
        this->x = x;
        this->y = y;
    }
};

enum class Cmd : char {
    N = 'N',
    S = 'S',
    E = 'E',
    W = 'W',
    L = 'L',
    R = 'R',
    F = 'F'
};

int main(){
    string line;
    State wp = {.x=10, .y=1};
    State s = {.x=0, .y=0};
    while(cin >> line){
        stringstream ls(line);
        char c;
        int i;
        ls >> c >> i;
        switch((Cmd)c){
            case Cmd::N:
                wp.y += i;
                break;
            case Cmd::S:
                wp.y -= i;
                break;
            case Cmd::E:
                wp.x += i;
                break;
            case Cmd::W:
                wp.x -= i;
                break;
            case Cmd::L:
                wp.rotate(-i);
                break;
            case Cmd::R:
                wp.rotate(i);
                break;
            case Cmd::F:
                s.x += i*wp.x;
                s.y += i*wp.y;
                break;
            default:
                cout << "Error: unimplemented Cmd" << endl;
                exit(-1);
        }
        // cout << s.x << " " << s.y << endl;
        // cout << "waypoint: " << wp.x << " " << wp.y << endl;
    }
    cout << s.x << " " << s.y << endl;
    cout << abs(s.x) + abs(s.y) << endl;
    return 0;
}
