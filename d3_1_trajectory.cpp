#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

using u8 = uint8_t;

int main(int argc, char* argv[]){
    if (argc < 3){
        cout << "< 2 arguments\n";
        return -1;
    }
    int rd = atoi(argv[1]);
    int cd = atoi(argv[2]);
    stringstream ss;
    int width = 0, ri = 0, ci = 0;
    int total = 0;
    while(!(cin.eof())){
        string s;
        cin >> s;
        if(s.length() < width){
            break;
        }
        if(ri % rd){
            ri += 1;
            continue;
        }
        if (s[ci] == '#'){
            total++;
        }
        ri += 1;
        ci += cd;
        if (width == 0){
            width = s.length();
            cout << "width = " << width << endl;
        } else {
            ci = ci % width;
        }
    }
    cout << total << endl;
    cout << "ri = " << ri << endl;
    return 0;
}
