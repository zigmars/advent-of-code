#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <regex>

using namespace std;

struct Bus {
    int id;
    int idx;
    Bus(int id, int idx) : id(id), idx(idx){}
};

using ull = unsigned long long;
using ll = long long;

ull extendedEuclidean(ull a, ull b, ll & a_mul, ll & b_mul){
    if(a == 0){
        a_mul = 0;
        b_mul = 1;
        return b;
    } else {
        ull q = b/a; // b = q*a + r // q = b div a
        ull r = b - q*a; 			// r = b mod a
        ll x, y;
        ull gcd = extendedEuclidean(r, a, x, y);
        a_mul = y - (ll)q * x;
        b_mul = x;
        return gcd;
    }
}

int main(){
    vector<Bus> input;
    string line;
    int timestamp;
    cin >> timestamp >> line;

    regex re("(\\d|x)+");
    auto busIds = sregex_iterator(line.begin(), line.end(), re);
    auto b_end = sregex_iterator();
    auto b_beg = busIds;
    int idx = 0;
    ll prod = 1;
    for(sregex_iterator bi = b_beg; bi != b_end; bi++, idx++){
        smatch m = *bi;
        string ms = m.str();
        if(ms[0] != 'x'){
            stringstream ss(ms);
            int id;
            ss >> id;
            prod *= id;
            input.push_back(Bus(id, idx));
        }
    }
    cout << "prod = " << prod << endl;
    ll res = 0;
    for(Bus b : input){
        // https://en.wikipedia.org/wiki/Chinese_remainder_theorem#Existence_(direct_construction)
        ll prod_sub = prod/((ll)b.id);
        ll mul, tmp;
        extendedEuclidean(prod_sub, b.id, mul, tmp);
        cout << mul << endl;
        ll newPart = (b.id-(b.idx%b.id))*mul*prod_sub;
        res += newPart;
        cout << "res: " << res << endl;
    }
    if(res < 0LL){
        res = res % prod;
        res += prod;
    }
    res = res % prod;
    cout << "res = " << res << endl;
    cout << "Check:" << endl;
    for(auto i : input){
        cout << i.idx << ": " << i.id << " " << (res+i.idx)%((ull)i.id) << endl;
    }
    return 0;
}
