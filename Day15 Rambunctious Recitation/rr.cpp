#include <iostream>
#include <map>
#include <set>

using namespace std;

using u32 = uint32_t;

map<u32, u32> lastIdx;

u32 next(u32 val, u32 idx){
    u32 ret;
    //cout << "v: " << val << " i:" << idx << endl;
    if(lastIdx.contains(val)){
        ret = idx - lastIdx[val];
    } else {
        ret = 0;
    }
    lastIdx[val] = idx;
    return ret;
}

int main(){
    // if last number
    u32 curIdx, cur, nextVal;
    while(cin >> cur){
        cout << curIdx << ": " << cur << endl;
        nextVal = next(cur, curIdx);
        curIdx++;
    }
    for(; curIdx <= 2020; curIdx++){
        cur = nextVal;
        cout << curIdx << ": " << cur << endl;
        nextVal = next(cur, curIdx);
    }
    return 0;
}
