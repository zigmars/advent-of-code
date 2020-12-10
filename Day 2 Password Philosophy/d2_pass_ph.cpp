#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using u8 = uint8_t;
// const u8 ALPHA_SIZE = 128;

// u8 dist[ALPHA_SIZE];

int main(){
    //vector<int> input;
    int goodCount = 0;
    while(!(cin.eof())){
        // memset(dist, 0, ALPHA_SIZE*sizeof(u8));
        unsigned int low, high;
        char ch, dch;
        string s;
        // "1-13"
        cin >> low >> dch >> high;
        cout << dch << " ";
        assert(low <= high);
        cout << low << " " << high << " ";
        // " z : "
        cin >> ch; cout << ch << " ";
        cin >> dch; cout << dch << " ";
        // "string\n"
        cin >> s;
        cout << s << endl;
        u8 cc = 0;
        for(u8 i = 0; i < s.length(); i++){
            assert('a' <= s[i] && s[i] <= 'z');
            if(s[i] == ch){
                cc++;
            }
        }
        if(low <= cc && cc <= high){
            cout << "good!" << endl;
            goodCount++;
        } else {
            cout << "bad!" << endl;
        }
    }
    cout << goodCount << endl;
    return 0;
}
