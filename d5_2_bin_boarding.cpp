#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

bool dist[1050] = {false};
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
        dist[id] = true;
        maxId = max(maxId, id);
        //cout << id << endl;
    }
    for(int i = 0; i < maxId; i++){
        if(!dist[i]){
            cout << i << endl;
        }
    }
    cout << "maxId = " << maxId << endl;
    return 0;
}
