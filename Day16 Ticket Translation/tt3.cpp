#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <climits>
#include <cmath>

using namespace std;

struct Range{
    Range(const int begin, const int end) : b(begin), e(end) {}
    Range(const int begin, const int end, const int id) : b(begin), e(end) {}
    int b, e;
    bool operator<(const Range& other){
        return (this->b == other.b && this->e < other.e) || this->b < other.b;
    }
    bool contains(int val){
        return b<= val && val <= e;
    }
};

struct DualRange {
    Range r[2];
    int rangeId;
    string name;
    bool contains(int val){
        return r[0].contains(val) || r[1].contains(val);
    }
};

struct FieldCheck {
    FieldCheck(vector<bool> fc) : c(fc) {};
    bool operator<(FieldCheck fc){
        return hamDist() < fc.hamDist();
    }
    vector<bool> c;
    int idx;
    int hamDist() const {
        return std::count(c.begin(), c.end(), true);
    }
};

vector<DualRange> drange;
vector<vector<int> > tickets;
vector<int> myTicket;

bool isGloballyValid(int val){
    for(auto r : drange){
        if(r.contains(val)){
            return true;
        }
    }
    return false;
}

void printRange(){
    for(auto& r : drange){
        cout << "(" << r.r[0].b << ".." << r.r[0].e << " | ";
        cout << r.r[1].b << ".." << r.r[1].e << ")" << endl;
    }
    cout << endl;
}

void printVec(vector<int> v){
    for(const auto& i : v){
        cout << i << " ";
    }
}

int main(){
    // read field definitions
    string line;
    while(getline(cin, line) && line != ""){
        static int rangeId = 0;
        const regex re("(.*):\\s*(\\d+)-(\\d+) or (\\d+)-(\\d+)");
        smatch m;
        if ( regex_search(line, m, re) ){
            stringstream ss(m[2].str() + " " + string(m[3]) + " " + string(m[4]) + " " + string(m[5]));
            int b1, e1, b2, e2;
            ss >> b1 >> e1 >> b2 >> e2;
            // cout << "(" << b1 << " : " << e1 <<"), ";
            // cout << "(" << b2 << " : " << e2 <<")" << endl;
            drange.push_back({Range(b1, e1), Range(b2, e2), rangeId, m[1].str()});
        }
        rangeId++;
    }
    printRange();

    /*
    // print out ranges
    for(const auto& t : drange){
        cout << t.r[0].b << " " << t.r[0].e << " " << t.r[1].b << " " << t.r[1].e << endl;
    }
    */

    // read my ticket
    while(getline(cin, line)){
        if(line == ""){
            continue;
        }
        const regex re("\\d+");
        smatch m;
        if ( !regex_search(line, m, re) ){
            continue;
        }
        auto beg = sregex_iterator(line.begin(), line.end(), re);
        auto end = sregex_iterator();
        for(sregex_iterator bi = beg; bi != end; bi++){
            m = *bi;
            stringstream ss(m.str());
            int val;
            ss >> val;
            myTicket.push_back(val);
        }
        break;
    }

    // read nearby tickets
    while(getline(cin, line)){
        if(line == ""){
            continue;
        }
        const regex re("\\d+");
        smatch m;
        if ( !regex_search(line, m, re) ){
            continue;
        }
        static int idx = 0;
        auto beg = sregex_iterator(line.begin(), line.end(), re);
        auto end = sregex_iterator();
        bool valid = true;
        vector<int> curTick;
        for(sregex_iterator bi = beg; bi != end; bi++){
            m = *bi;
            string ms = m.str();
            stringstream ss(ms);
            int val;
            ss >> val;
            if(!isGloballyValid(val)){
                valid = false;
                break;
            }
            curTick.push_back(val);
        }
        if(valid){
            tickets.push_back(curTick);
            cout << idx << ": ";
            printVec(curTick);
            cout << endl;
        }
        idx++;
    }

    // count of rows after filtering invalid
    cout << "tickets.size() = " << tickets.size() << endl;

    // for each field form a vector of possible matching columns
    // init all values to 1/true at start
    int checkFieldCount = tickets[0].size();
    vector<FieldCheck> check(checkFieldCount, FieldCheck(vector<bool>(tickets[0].size(), true)));
    // save original index
    for(int fIdx = 0; fIdx < checkFieldCount; fIdx++){
        check[fIdx].idx = fIdx;
    }
    for(int fIdx = 0; fIdx < checkFieldCount; fIdx++){
        // for each column & row:
        for(int rIdx = 0; rIdx < tickets.size(); rIdx++){
            for(int cIdx = 0; cIdx < tickets[0].size(); cIdx++){
                // check validity of field: value must be inside range
                if(!drange[fIdx].contains(tickets[rIdx][cIdx])){
                    check[fIdx].c[cIdx] = 0;
                }
            }
        }
    }

    // sort by increasing hamming distance 
    sort(check.begin(), check.end());

    // deduce by exclusion possibility matrix check[][] to permutation matrix
    int fIdx = 0;
    for(const auto& v : check){
        int cIdx = 0;
        for(const auto& b : v.c){
            cout << (int)b;
            if(b){
                if(v.hamDist() != 1){
                    cout << "error: not unique" << endl;
                    exit(-1);
                }
                for(int fi = fIdx+1; fi < check.size(); fi++){
                    check[fi].c[cIdx] = 0;
                }
            }
            cIdx++;
        }
        cout << endl;
        fIdx++;
    }
    cout << endl;

    // re-sort back to original order
    sort(check.begin(), check.end(), [](const FieldCheck& a, const FieldCheck& b){return a.idx < b.idx;});

    // read from perm matrix check[][] and form mapping from column idx to field idx
    map<int, int> fieldToCol;
    for(int fIdx = 0; fIdx < checkFieldCount; fIdx++){
        for(int cIdx = 0; cIdx  < checkFieldCount; cIdx++){
            if(check[fIdx].c[cIdx]){
                fieldToCol[fIdx] = cIdx;
            }
        }
    }

    /*
    // print out permutations
    for(const auto& v : check){
        for(const auto& b : v.c){
            cout << (int)b;
        }
        cout << endl;
    }
    */

    // calc product as answer
    unsigned long long prod = 1;
    for(int fi = 0; fi < min(6, (int)check.size()); fi++){
        int val = myTicket[fieldToCol[fi]];
        cout << drange[fi].name << ": ";
        cout << val << endl;
        prod *= val;
    }
    cout << prod << endl;

    return 0;
}
