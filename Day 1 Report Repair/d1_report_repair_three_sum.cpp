#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define SUM (2020)
int table[SUM+100] = {0};

int main(){
    vector<int> input;
    int count = 0;
    while(!(cin.eof())){
        int n;
        cin >> n;
        input.push_back(n);
        table[n] = 1;
        count++;
    }
    sort(input.begin(), input.end());
    // for()
    for(int i = 0; i < count && input[i] <= SUM/2; i++){
        int rest = SUM-input[i];
        if( rest < 0 ) {
            continue;
        }
        for(int j = i; j < count && input[j] <= rest/2; j++){
            if( rest-input[j] >= 0 && table[rest-input[j]] == 1){
                cout << input[i] << " x " << 
                    input[j] << " x " << 
                    (rest-input[j]) << " = " << 
                    input[i]*input[j]*(rest-input[j]) << endl;
            }
        }
    }
    return 0;
}
