#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <map>
#include <bitset>

using ull = unsigned long long;
using u64 = ull;

using namespace std;

int main(){
    string line;
    map<int, ull> mem;
    u64 dntouchMask = 0, touchOne = 0, touchZero = 0;
    while(getline(cin, line)){
        cout << line << endl;
        if(line[1] == 'a'){
            // Mask
            string mask = line.substr(7, 36);
            dntouchMask = 0;
            touchZero = 0;
            touchOne = 0;
            for(int i = 0, b = 35; i < 36; i++,b--){
                switch(mask[i]){
                    case 'X':
                        dntouchMask |= (1ULL<<b);
                        break;
                    case '0':
                        touchZero |= (1ULL<<b);
                        break;
                    case '1':
                        touchOne |= (1ULL<<b);
                        break;
                }
            }
            cout << "dnt: " << bitset<36>(dntouchMask) << endl;
            cout << "t1: " << bitset<36>(touchOne) << endl;
        } else if(line[1] == 'e'){
            const regex re("^mem\\[(\\d+)\\] = (\\d+)$");
            smatch m;
            u64 addr, val;
            if ( regex_search(line, m, re) ){
                cout << m[1] << " : " << m[2] << endl;
                stringstream ss(m[1]);
                ss >> addr;
                ss = stringstream(m[2]);
                ss >> val;
                cout << "mem[" << addr << "] = " << val << endl;
            } else {
                cout << "Error: regex no match" << endl;
                exit(-1);
            }
            cout << "dnt & v: " << bitset<36>(dntouchMask & val) << endl;
            cout << "t1 & v: " << bitset<36>(touchOne & val) << endl;
            mem[addr] = ((dntouchMask & val) | touchOne ) & ~touchZero;
            cout << "final[" << addr << "] = " << mem[addr] << endl;
        }
    }
    ull sum = 0;
    for(auto &m : mem){
        bitset<36> bs(m.second);
        cout << m.first << " :\t" << m.second << " " << bs << endl;
        sum += m.second;
    }
    cout << sum << endl;
    return 0;
}
