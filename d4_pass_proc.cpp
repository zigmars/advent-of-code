#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

bool checkPassport(const string& s){
    set<string> fields({"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"});//, "cid"});
    set<string> inFields;
    stringstream ss(s);
    string key_value;
    // cout << s << "\n\t | ";
    while(!ss.eof()){
        ss >> key_value;
        size_t pos = key_value.find(':');
        if(pos != string::npos){
            string key = key_value.substr(0, pos);
            // cout << key << " ";
            inFields.insert(key);
        }
    }
    bool ret = includes(inFields.begin(), inFields.end(), 
            fields.begin(), fields.end());
    // cout << " | " << ret << endl;
    return ret;
}
int main(){
    string input, line;
    while (getline(cin, line))
    {
        input += line + '\n';
    }
    //cout << input << endl;
    int iter = 0;
    int count = 0;
    bool lastPassport = false;
    for(size_t pos = 0, prev_pos = 0; 
            true;
        ){
        pos = input.find("\n\n", prev_pos);
        if (pos == string::npos){
           if(prev_pos < input.length()-1){
               lastPassport = true;
                pos = input.length()-1;
           } else {
                break;
           }
        }        //cout << "=========================\n";
        string s = input.substr(prev_pos, pos-prev_pos);
        //cout << s << endl;
        //cout << "=========================\n";
        prev_pos = pos + 2;
        iter++;
        if(checkPassport(s)){
            count++;
        }
        if(lastPassport){
            break;
        }
    }
    cout << count << endl;
    return 0;
}
