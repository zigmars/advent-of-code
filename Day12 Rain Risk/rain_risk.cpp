#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

using u8 = uint8_t;

enum class Dir : int {
    N = 0,
    S = 2,
    E = 1,
    W = 3
};

struct State {
    int x, y;
    Dir d;
    void rotate(int deg){
        deg /= 90;
        deg %= 4;
        deg += 4;
        deg %= 4;
        d = static_cast<Dir>(static_cast<int>(d) +  deg);
        d = static_cast<Dir>(static_cast<int>(d) % 4U);
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
    State s = {.x=0, .y=0, .d=Dir::E};
    while(cin >> line){
        stringstream ls(line);
        char c;
        int i;
        ls >> c >> i;
        switch((Cmd)c){
            case Cmd::N:
                s.y += i;
                break;
            case Cmd::S:
                s.y -= i;
                break;
            case Cmd::E:
                s.x += i;
                break;
            case Cmd::W:
                s.x -= i;
                break;
            case Cmd::L:
                s.rotate(-i);
                break;
            case Cmd::R:
                s.rotate(i);
                break;
            case Cmd::F:
                switch(s.d){
                    case Dir::N:
                        s.y += i;
                        break;
                    case Dir::S:
                        s.y -= i;
                        break;
                    case Dir::E:
                        s.x += i;
                        break;
                    case Dir::W:
                        s.x -= i;
                        break;
                }
                break;
            default:
                cout << "Error: unimplemented Cmd" << endl;
                exit(-1);
        }
    }
    cout << s.x << " " << s.y << endl;
    cout << abs(s.x) + abs(s.y) << endl;
    return 0;
}
