#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <map>
#include <bitset>

using ull = unsigned long long;
using u64 = ull;
using u8 = unsigned char;

using namespace std;

int main(){
    string line;
    map<u64, ull> mem;
    u64 dntouchMask = 0, touchOne = 0, touchZero = 0;
    map<u8, u8> addrMask;
    while(getline(cin, line)){
        cout << line << endl;
        if(line[1] == 'a'){
            // Mask
            string mask = line.substr(7, 36);
            addrMask.clear();
            dntouchMask = 0;
            touchZero = 0;
            touchOne = 0;
            int bCnt = 0;
            for(int i = 0, b = 35; i < 36; i++,b--){
                switch(mask[i]){
                    case 'X':
                        dntouchMask |= (1ULL<<b);
                        addrMask[bCnt] = b;
                        bCnt++;
                        break;
                    case '0':
                        touchZero |= (1ULL<<b);
                        break;
                    case '1':
                        touchOne |= (1ULL<<b);
                        break;
                }
            }
            cout << "bCnt = " << bCnt << endl;
            //cout << "dnt: " << bitset<36>(dntouchMask) << endl;
            cout << "t1: " << bitset<36>(touchOne) << endl;
            cout << "t0: " << bitset<36>(touchZero) << endl;
        } else if(line[1] == 'e'){
            const regex re("^mem\\[(\\d+)\\] = (\\d+)$");
            smatch m;
            u64 addr, val;
            if ( regex_search(line, m, re) ){
                //cout << m[1] << " : " << m[2] << endl;
                stringstream ss(m[1]);
                ss >> addr;
                ss = stringstream(m[2]);
                ss >> val;
                //cout << "mem[" << addr << "] = " << val << endl;
            } else {
                cout << "Error: regex no match" << endl;
                exit(-1);
            }
            cout << "t1 & ad: " << bitset<36>(touchOne | addr) << endl;
            cout << "~t0 & prev: " << bitset<36>((~touchZero & addr) | (touchOne | addr)) << endl;
            cout << "~dnt & prev: " << bitset<36>(~dntouchMask & ((~touchZero & addr) | (touchOne | addr))) << endl;
            cout << "addr = " << addr << endl;
            cout << "addr = " << bitset<36>(addr) << endl;
            addr = ~dntouchMask & ((~touchZero & addr) | (touchOne | addr));
            cout << "addr = " << addr << endl;
            cout << "addr = " << bitset<36>(addr) << endl;

            u64 floatBitRange = 1ULL<<addrMask.size();
            cout << "floatBitRange : " << floatBitRange << endl;
            for(u64 i = 0; i < floatBitRange; i++){
                u64 modAddr = addr;
                for(int b = 0; b < addrMask.size(); b++){
                    if( (1<<b) & i){
                        modAddr |= (1ULL<<addrMask[b]);
                    }
                }
                cout << "modAddr = " << modAddr << endl;
                mem[modAddr] = val;//((dntouchMask & val) | touchOne ) & ~touchZero;
            }
            //cout << "final[" << addr << "] = " << mem[addr] << endl;
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
