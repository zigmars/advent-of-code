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
    int time;
    Bus(int id, int timestamp) : id(id), time(((timestamp + id-1)/id)*id){}
    bool operator<(Bus b){
        return this->time < b.time;
    }
};

int main(){
    vector<Bus> input;
    string line;
    int timestamp;
    cin >> timestamp >> line;
    regex re("\\d+");
    auto busIds = sregex_iterator(line.begin(), line.end(), re);
    auto b_end = sregex_iterator();
    auto b_beg = busIds;
    for(sregex_iterator bi = b_beg; bi != b_end; bi++){
        smatch m = *bi;
        string ms = m.str();
        stringstream ss(ms);
        int id;
        ss >> id;
        input.push_back(Bus(id, timestamp));
        cout << id << " ";
    }
    cout << endl;
    //vector<int> output(input.size());
    //transform(input.begin(), input.end(), output.begin(), [=](int a){return ((timestamp + a-1)/a)*a;});
    for(auto o : input){
        cout << "(" << o.id << "," << o.time << ") ";
    }
    cout << endl;
    sort(input.begin(), input.end());
    for(auto o : input){
        cout << "(" << o.id << "," << o.time << ") ";
    }
    cout << endl;
    cout << input[0].id * (input[0].time-timestamp) << endl;
    return 0;
}
