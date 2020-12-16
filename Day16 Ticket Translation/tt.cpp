#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

struct Range{
    Range(int begin, int end) : b(begin), e(end) {}
    int b, e;
    bool operator<(const Range& other){
        return (this->b == other.b && this->e < other.e) || this->b < other.b;
    }
    bool contains(int val){
        return b<= val && val <= e;
    }
};

vector<Range> range;

bool isValid(int val){
    for(auto r : range){
        if(r.contains(val)){
            return true;
        }
    }
    return false;
}

void mergeRanges(){
    Range prev(-10,-10);
    vector<Range> rangeCopy(range);
    range.clear();
    for(auto& r : rangeCopy){
        if(r.b <= prev.e+1){
            if(r.e > prev.e){
                range[range.size()-1].e = r.e;
            }
        } else {
            range.push_back(r);
        }
        prev = r;
    }
}

void printRange(){
    for(auto& r : range){
        cout << "(" << r.b << "," << r.e << ") ";
    }
    cout << endl;
}

int main(){
    string line;
    unsigned long long erroreousSum = 0;
    while(getline(cin, line) && line != ""){
        const regex re(".*:\\s*(\\d+)-(\\d+) or (\\d+)-(\\d+)");
        smatch m;
        if ( regex_search(line, m, re) ){
            stringstream ss(string(m[1]) + " " + string(m[2]) + " " + string(m[3]) + " " + string(m[4]));
            int b1, e1, b2, e2;
            ss >> b1 >> e1 >> b2 >> e2;
            cout << "(" << b1 << " : " << e1 <<"), ";
            cout << "(" << b2 << " : " << e2 <<")" << endl;
            range.push_back(Range(b1, e1));
            range.push_back(Range(b2, e2));
        }
    }
    printRange();
    sort(range.begin(), range.end());
    printRange();
    mergeRanges();
    printRange();
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
        auto b_beg = sregex_iterator(line.begin(), line.end(), re);
        auto b_end = sregex_iterator();
        bool valid = true;
        for(sregex_iterator bi = b_beg; bi != b_end; bi++){
            m = *bi;
            string ms = m.str();
            stringstream ss(ms);
            int val;
            ss >> val;
            if(!isValid(val)){
                cout << idx << ": " << val << endl;
                valid = false;
                erroreousSum += val;
            }
        }
        if(!valid){

        }
        idx++;
    }
    cout << erroreousSum << endl;
    return 0;
}
