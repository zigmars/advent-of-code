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
state s({.acc=0, .pc=0});

bool programTerminates(vector<instr> program){
    while(!visited.contains(s.pc) && s.pc < program.size()){
        visited.insert(s.pc);
        instr i = program[s.pc];
        //cout << i.op << " " << (i.val >= 0 ? string("+") : string("")) << i.val << endl;
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
    return (s.pc == program.size());
}
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

    bool endConditionDone = false;
    auto endCondition = [](){
        instr i = program[s.pc];
        return (i.op == 'n' && i.val + s.pc == program.size()) || (i.op == 'j' && s.pc == program.size()-1);
    };
    for(int modPc = 0; modPc < program.size(); modPc++){
        vector<instr> modProgram(program);
        if(program[modPc].op == 'a'){
            continue;
        }
        modProgram[modPc].op ^= ('j' ^ 'n');
        s = {.acc=0, .pc=0};
        visited.clear();
        bool terminated = programTerminates(modProgram);
        if(terminated){
            cout << "modPc = " << modPc << endl;
            cout << s.pc << " " << s.acc << endl;
            //break;
        }
    }


    //cout << "acc = " << s.acc << endl;
    return 0;
}
