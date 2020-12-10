#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;
using u64 = uint64_t;

int dist[4] = {0};
int main(){
    vector<int> in;
    vector<vector<int> > splits;
    int tmp;
    while(cin >> tmp){
        in.push_back(tmp);
        cout << in[in.size()-1] << endl;
    }
    sort(in.begin(), in.end());
    for(auto v : in){
        cout << v << endl;
    }
    vector<int> split;
    int prevValue = 0;
    split.push_back(prevValue);
    for(auto v : in){
        switch(v-prevValue){
            case 1:
                dist[1]++;
                split.push_back(v);
                break;
            case 3:
                splits.push_back(split);
                split.clear();
                split.push_back(v);
                dist[3]++;
                break;
            default:
                cout << "Error: diff other than 1 or 3" << endl;
                exit(-1);
        }
        prevValue = v;
    }
    if(split.size()){
        splits.push_back(split);
    }
    // diff for highest adapter to phone
    dist[3]++;
    cout << "Count of 1s: " << dist[1] << " \n";
    cout << "Count of 3s: " << dist[3] << endl;
    cout << "Result: " << dist[1]*dist[3] << endl;
    u64 result = 1;
    for(auto ss : splits){
        switch(ss.size()){
            case 1:
            case 2:
                break;
            case 3:
            case 4:
                // only ends should be always left for connection to both ends
                // for each of middle elements there is independent binary
                // choice to insert it or not
                result *= 1<<(ss.size()-2);
                break;
            case 5:
                // need at least one of the middle elements left, hence the (0,0,0)
                // choice is not an option
                cout << "2**3-1 = " << (1ULL<<(ss.size()-2))-1 << endl;
                result *= (1ULL<<(ss.size()-2))-1;
                break;
            default:
                cout << "Error: greater than 5 elements in split" << endl;
                exit(-1);
        }
        for(auto s : ss){
            cout << s << " ";
        }
        cout << endl;
    }
    cout << "result: " << result << endl;
    return 0;
}
