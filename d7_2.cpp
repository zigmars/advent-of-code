#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <utility>

using namespace std;

unordered_map<string, int> nameMap;
// map<string, int> nameMap;

struct BagDependency {
    int bagIdx, bagCount;
    //BagDependency();
};

struct Node {
    vector<BagDependency> bags;
    int outCount;
    int inCount;
    Node(int inCount, int outCount) 
        : outCount(outCount), inCount(inCount),
        bags(vector<BagDependency>()) {}
    Node() : bags(vector<BagDependency>()), outCount(0), inCount(0) {}
};

vector<Node> vertex;

using ull = unsigned long long;
ull countTotalBags(int bagIdx){
    // count in the bagIdx bag first
    ull sum = 1; // serves as base case as well
    //cout << bagIdx << "]: \n";
    for(auto b : vertex[bagIdx].bags){
        ull total = countTotalBags(b.bagIdx);
        //cout << "[" << b.bagIdx << "]: " << b.bagCount << "x " << total << "\n";
        sum += total * b.bagCount;
    }
    //cout << sum << endl;
    return sum;
}

int main(){
    //vertex.resize(1000);
    int nodeIdx = 0, lineIdx = 0;
    vector<string> input;
    //  vector<vector<BagDependency> > bagDep;
    string line;
    const char separator[] = " bags contain ";
    while(getline(cin, line)){
        input.push_back(line);
        size_t pos = line.find(separator);
        if(pos == string::npos){
            cout << "Line: " << lineIdx << "Error: \"contain \" not found" << endl;
            exit(-1);
        }
        int fromIdx = nodeIdx;
        string key = line.substr(0, pos);
        nameMap[key] = fromIdx;
        nodeIdx++;
        //int bagCount;
        int count = 0;
        for(size_t newPos = line.find(", ", pos); ((newPos = line.find(", ", pos)) != string::npos) || ((newPos = line.find(".", pos)) != string::npos); pos = newPos+2){
            count++;
        }
        vertex.push_back(Node(0, count));
        /*
        }
        */
    }
    for(int i = 0; i < vertex.size(); i++){
        size_t pos = input[i].find(separator)+sizeof(separator)-1;
        if(input[i].find("bags contain no other bags.") != string::npos){
            continue;
        }
        for(size_t newPos = input[i].find(", ", pos); ((newPos = input[i].find(", ", pos)) != string::npos) || ((newPos = input[i].find(".", pos)) != string::npos); pos = newPos+2){
            string depStr = input[i].substr(pos, newPos-pos);
            size_t intEnd = depStr.find(" ");
            int bagCount = atoi(depStr.substr(0, intEnd).c_str());
            size_t nameEnd = depStr.find(" bag");
            string bagName = depStr.substr(intEnd+1, nameEnd-(intEnd+1));
            // cout << bagName << " " << bagCount << endl;
            int bagIdx = nameMap[bagName];
            vertex[i].bags.push_back({.bagIdx=bagIdx, .bagCount=bagCount});
            vertex[bagIdx].inCount++;
            //vertex[i].outCount++;
        }
    }
    for(int i = 0; i < vertex.size(); i++){
        //cout << i << ": in " << vertex[i].inCount << " out " << vertex[i].outCount << ":";
        for(auto b : vertex[i].bags){
            //cout << " " << b.bagIdx << " (" << b.bagCount << ")";
        }
        //cout << endl;
    }

    int root = nameMap["shiny gold"];
    cout << countTotalBags(root)-1 << endl;
    return 0;
}
