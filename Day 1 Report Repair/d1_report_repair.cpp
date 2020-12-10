#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int table[3000] = {0};

int main(){
    //vector<int> input;
    while(!(cin.eof())){
        int n;
        cin >> n;
        //input.push_back(n);
        table[n] = 1;
    }
    // sort(input.begin(), input.end());
    // for()
    for(int i = 0; i < 1011; i++){
        if(table[i] == 1 && table[2020-i] == 1){
            cout << i << " x " << (2020-i) << " = " << i*(2020-i) << endl;
        }
    }
    return 0;
}
