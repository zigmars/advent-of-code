#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

using ull = unsigned long long;

ull arr[1000];
ull integ[1001];

bool sumOfTwo(int i){
    ull cur = arr[i];
    for(int o = 1; o < 25; o++){
        for(int o2 = o+1; o2 <= 25; o2++){
            if(i == 593){
                // cout << arr[i-o] << " + " << arr[i-o2] << " = " << arr[i-o]+arr[i-o2] << endl;
            }
            if(arr[i-o]+arr[i-o2] == cur){
                return true;
            }
        }
    }
    return false;
}

ull sum(int fromIdx, int toIdx){
    return integ[toIdx]-integ[fromIdx];
}

int main(){
    int i;
    ull theNumber;
    int tni;
    for(i = 0; i < 25; i++){
        cin >> arr[i];
    }
    for(;; i++){
        cin >> arr[i];
        if(!sumOfTwo(i)){
            // cout << i << ": " << arr[i] << endl;
            theNumber = arr[i];
            tni= i;
            break;
        }
    }
    integ[0] = 0;
    for(i = 1; i <= tni+1; i++){
        integ[i] = integ[i-1]+arr[i-1];
    }

    for(int fi = 0; fi <= tni; fi++){
        for(int ti = fi+1; ti <= tni+1; ti++){
            if(sum(fi, ti) == theNumber){
                ull sum = 0;
                ull minV = ULLONG_MAX, maxV = 0ULL;
                for(int i = fi; i < ti; i++){
                    minV = min(minV, arr[i]);
                    maxV = max(maxV, arr[i]);
                    // sum += arr[i];
                    // cout << i << ": + " << arr[i] << " = " << sum << endl;
                }
                // cout << "theNumber = " << theNumber << endl;
                // cout << fi << " " << ti-1 << endl;
                cout << minV << " + " << maxV << " = " << (minV+maxV) << endl;
                return 0;
            }
        }
    }
    return 0;
}
