#include <iostream>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

struct instr {
    char op;
    int val;
};

using ull = unsigned long long;

struct state {
    ull acc;
    int pc;
};

vector<instr> program;
set<int> visited;

int main(){
    string line;
    while(getline(cin, line)){
        string op;
        int val;
        stringstream ss(line);
        ss >> op >> val;
        program.push_back({.op=op[0], .val=val});
    }
    /*
    for(int i = 0; i < program.size(); i++){
        switch(program[i].op){
            case 'j':
                cout << "jmp ";
            break;
            case 'a':
                cout << "acc ";
            break;
            case 'n':
                cout << "nop ";
            break;
        }
        if(program[i].val >= 0){
            cout << "+";
        }
        cout << program[i].val << endl;
    }
    */
    state s({.acc=0, .pc=0});
    while(!visited.contains(s.pc)){
        visited.insert(s.pc);
        instr i = program[s.pc];
        cout << s.pc << ": " << i.op << " " << (i.val >= 0 ? string("+") : string("")) << i.val << endl;
        switch(i.op){
            case 'j':
                s.pc += i.val;
            break;
            case 'a':
                s.acc += i.val;
                s.pc += 1;
            break;
            case 'n':
                s.pc += 1;
            break;
        }
    }
    cout << "acc = " << s.acc << endl;
    return 0;
}
