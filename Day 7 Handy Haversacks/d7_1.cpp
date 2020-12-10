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
        cout << i << ": in " << vertex[i].inCount << " out " << vertex[i].outCount << ":";
        for(auto b : vertex[i].bags){
            cout << " " << b.bagIdx << " (" << b.bagCount << ")";
        }
        cout << endl;
    }
/*
    for(const auto& it : nameMap){
        cout << it.first << " " << it.second << endl;
    }
    */
    //queue<int> q;

    // Generate reversed edge DAG
    vector<Node> rev(vertex.size());
    for(int i = 0; i < vertex.size(); i++){

        for( auto b : vertex[i].bags ){
            rev[b.bagIdx].bags.push_back({.bagIdx=i, .bagCount=0});
            rev[b.bagIdx].inCount = vertex[b.bagIdx].outCount;
        }
    }
    for(int i = 0; i < rev.size(); i++){
        cout << i << ": in " << rev[i].inCount << " out " << rev[i].bags.size() << ":";
        for(auto b : rev[i].bags){
            cout << " " << b.bagIdx << " (" << b.bagCount << ")";
        }
        cout << endl;
    }
    // BFS the reversed DAG
    queue<int> order;
    map<int, bool> seen;
    int root = nameMap["shiny gold"];
    order.push(root);
    for(int cur = root;!order.empty();){
        for(auto b : rev[cur].bags){
            if(!seen[b.bagIdx]){
                cout << b.bagIdx << endl;
                order.push(b.bagIdx);
            }
        }
        seen[cur] = true;
        cur = order.front();
        order.pop();
    }
    seen.erase(root);
    unordered_map<int, string> revMap;
    for(auto nm : nameMap){
        revMap[nm.second] = nm.first;
    }
    for(auto s : seen){
        cout << s.first << " " << revMap[s.first] << endl;
    }
    cout << seen.size() << endl;
    return 0;
}
