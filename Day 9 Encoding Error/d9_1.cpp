#include <iostream>

using namespace std;

using ull = unsigned long long;

ull arr[1000];

bool sumOfTwo(int i){
    ull cur = arr[i];
    for(int o = 1; o < 25; o++){
        for(int o2 = o+1; o2 <= 25; o2++){
            if(i == 593){
                cout << arr[i-o] << " + " << arr[i-o2] << " = " << arr[i-o]+arr[i-o2] << endl;
            }
            if(arr[i-o]+arr[i-o2] == cur){
                return true;
            }
        }
    }
    return false;
}

int main(){
    int i;
    for(i = 0; i < 25; i++){
        cin >> arr[i];
    }
    for(;; i++){
        cin >> arr[i];
        if(!sumOfTwo(i)){
            cout << i << ": " << arr[i] << endl;
            break;
        }
    }

    return 0;
}
