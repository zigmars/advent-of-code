#include <iostream>
#include <algorithm>

using namespace std;

int dist[4] = {0};
int main(){
    vector<int> in;
    int tmp;
    while(cin >> tmp){
        in.push_back(tmp);
        cout << in[in.size()-1] << endl;
    }
    sort(in.begin(), in.end());
    for(auto v : in){
        cout << v << endl;
    }
    int prevValue = 0;
    for(auto v : in){
        switch(v-prevValue){
            case 1:
            case 3:
                dist[v-prevValue] += 1;
                break;
            default:
                cout << "Error: diff other than 1 or 3" << endl;
                exit(-1);
        }
        prevValue = v;
    }
    // diff for highest adapter to phone
    dist[3]++;
    cout << "Count of 1s: " << dist[1] << " \n";
    cout << "Count of 3s: " << dist[3] << endl;
    cout << "Result: " << dist[1]*dist[3] << endl;
    return 0;
}
