#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>

using namespace std;

vector<string> values;
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
            string value = key_value.substr(pos+1, key_value.length()-(pos+1));
            if(!key.compare("byr")){
                values[0] = value;
            } else if(!key.compare("iyr")){
                values[1] = value;
            } else if(!key.compare("eyr")){
                values[2] = value;
            } else if(!key.compare("hgt")){
                values[3] = value;
            } else if(!key.compare("hcl")){
                values[4] = value;
            } else if(!key.compare("ecl")){
                values[5] = value;
            } else if(!key.compare("pid")){
                values[6] = value;
            }
        }
    }
    bool ret = includes(inFields.begin(), inFields.end(), 
            fields.begin(), fields.end());
    // cout << " | " << ret << endl;
    return ret;
}

bool validatePassport(){
    int byr = atoi(values[0].c_str());
    if(!(1920 <= byr && byr <= 2002)){
        // cout << "0" << endl;
        return false;
    }

    int iyr = atoi(values[1].c_str());
    if(!(2010 <= iyr && iyr <= 2020)){
        // cout << "1" << endl;
        return false;
    }

    int eyr = atoi(values[2].c_str());
    if(!(2020 <= eyr && eyr <= 2030)){
        // cout << "2" << endl;
        return false;
    }

    //int hgt = atoi(values[3]);
    stringstream ss(values[3]);
    string str;
    int hgt;
    ss >> hgt >> str;
    if(!str.compare("cm")){
        if(!(150 <= hgt && hgt <= 193)){
            // cout << "3a" << endl;
            return false;
        }
    } else if(!str.compare("in")){
        if(!(59 <= hgt && hgt <= 76)){
        // cout << "eb" << endl;
            return false;
        }
    } else {
        // cout << "3c" << endl;
        return false;
    }

    if(values[4].length() != 7 || values[4][0] != '#'){
        // cout << "4a" << endl;
        return false;
    }
    for(int i = 1; i < values[4].length(); i++){
        if(!(('0' <= values[4][i] && values[4][i] <= '9') || ('a' <= values[4][i] && values[4][i] <= 'f'))){
            // cout << "4b" << endl;
            return false;
        }
    }

    string hairs[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    bool match = false;
    for(int i = 0; i < 7; i++){
        if(!values[5].compare(hairs[i])){
            // cout << "5" << endl;
            match = true;
            break;
        }
    }
    if(!match){
        return false;
    }

    if(values[6].length() != 9){
        // cout << "6a" << endl;
        return false;
    }
    for(int i = 0; i < values[6].length(); i++){
        if(!('0' <= values[6][i] && values[6][i] <= '9')){
            // cout << "6b" << endl;
            return false;
        }
    }
    return true;
}

int main(){
    values.resize(7);
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
        }
        //cout << "=========================\n";
        string s = input.substr(prev_pos, pos-prev_pos);
        //cout << s << endl;
        //cout << "=========================\n";
        prev_pos = pos + 2;
        iter++;
        if(checkPassport(s) && validatePassport()){
            count++;
        }
        if(lastPassport){
            break;
        }
    }
    cout << count << endl;
    return 0;
}
