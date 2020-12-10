#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

vector<string> group;
int dist[(int)'z'+1] = {0};
int ans[(int)'z'+1] = {0};

int main(){
    cout << "sizeof(ans) = " << sizeof(ans) << endl;
    string input, line;
    while (getline(cin, line) || cin.eof())
    {
        if(line.compare("")){
            group.push_back(line);
        }
        if(!line.compare("") || cin.eof()){
            memset(ans, 0, sizeof(ans));
            for(string p : group){
                //cout << p << endl;
                for(char q : p){
                    ans[q] += 1;
                    //cout << q << ":" << ans[q] << " ";
                }
            }
            //cout << endl;
            for(char c = 'a'; c <= 'z'; c++){
                dist[c] += (ans[c] == group.size()) ? 1 : 0;
                //cout << dist[c] << endl;
            }
            group.clear();
            if(cin.eof()){
                break;
            }
        }
    }
    int sum = 0;
    for(char c = 'a'; c <= 'z'; c++){
        //cout << dist[c] << " ";
        sum += dist[c];
    }
    //cout << endl;
    cout << sum << endl;
    return 0;
}
