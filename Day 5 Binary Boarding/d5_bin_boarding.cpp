#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main(){
    string line;
    int maxId = -1;
    while(!cin.eof()){
        cin >> line;
        int id = 0;
        for(char c : line){
            id <<= 1;
            if(c == 'B' || c == 'R'){
                id |= 1;
            }
        }
        maxId = max(maxId, id);
        cout << id << endl;
    }
    cout << "maxId = " << maxId << endl;
    return 0;
}
