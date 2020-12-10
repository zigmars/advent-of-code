#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

using u8 = uint8_t;
using u32 = uint32_t;

vector<string> m;

int main(int argc, char* argv[]){
    int width = -1;
    while(!(cin.eof())){
        string s;
        cin >> s;
        if((int)s.length() < width){
            break;
        }
        if(width < 0){
            width = s.length();
        }
        m.push_back(s);
    }
    cout << "rowCount = " << m.size() << endl;

    u32 rd = atoi(argv[1]);
    u32 cd = atoi(argv[2]);
    u32 cnt = 0;
    for(u32 ri = 0, ci = 0;
            ri < m.size();
            ri += rd, ci = (ci+cd)%(m[0].length())
    ){
        cout << "ri, ci = " << ri << ", " << ci;
        if(m[ri][ci] == '#') {
            cout << "#";
            cnt++;
        }
        cout << endl;
    }
    cout << cnt << endl;
    return 0;
}
