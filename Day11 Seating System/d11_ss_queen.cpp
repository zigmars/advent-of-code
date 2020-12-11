#include <iostream>
#include <vector>

using namespace std;

vector<string> seats;
int lineLen;

using s8 = int8_t;
using u8 = uint8_t;

struct Pos {
    u8 x,y;
    bool occupied;
};

vector<Pos> checkPos;

void printField(const vector<string> &seats){
    for(auto s : seats){
        cout << s << endl;
    }
}

bool queenOcc(const vector<string> &seats, int r, s8 dr, int c, s8 dc){
    //cout << "r,c = " << r << ", " << c << endl;
    do {
        r += dr;
        c += dc;
        //cout << r << ", " << c << endl;
    } while(seats[r][c] != 'x' && seats[r][c] != '#' && seats[r][c] != 'L');
    bool ret = seats[r][c] == '#';
    checkPos.push_back({.x=c, .y=r, .occupied=ret});
    return ret;
}

int occQueenSeats(const vector<string> &s, int r, int c){
    checkPos.clear();
    int count = \
            queenOcc(s,r,-1,c,-1) + queenOcc(s,r,-1,c,0) +  queenOcc(s,r,-1,c,+1)+
            queenOcc(s,r, 0,c,-1) +/*queenOcc(s,r,0,c,0)+*/ queenOcc(s,r,0,c,+1)+
            queenOcc(s,r,+1,c,-1) + queenOcc(s,r,+1,c,0) +  queenOcc(s,r,+1,c,+1);
    // cout << "qC(" << r << "," << c << "): " << count << endl;
    return count;
}

void markField(vector<string> &s, int r, int c){
    s[r][c] = 'z';
    occQueenSeats(s, r, c);
    for(Pos p : checkPos){
        s[p.y][p.x] = p.occupied ? '+' : 'O';
    }
    printField(s);
}

vector<string> iterate(const vector<string> &seats){
    vector<string> newSeats(seats);
    for(int r = 1; r < seats.size()-1; r++){
        // cout << newSeats[r] << endl;
        for(int c = 1; c <= lineLen; c++){
            //cout << "r,c:" << r << "," << c << "\t";
            int occSeats = occQueenSeats(seats, r,c);
            //cout << "r,c:" << r << "," << c << endl;
            if(seats[r][c] == 'L' && occSeats == 0){
                newSeats[r][c] = '#';
            } else if (seats[r][c] == '#' && occSeats >= 5){
                newSeats[r][c] = 'L';
            }
        }
    }
    return newSeats;
}

int countOccupied(const vector<string> &s){
    int cnt = 0;
    for(auto l : s){
        for(auto c : l){
            cnt += (c == '#');
        }
    }
    return cnt;
}

int main(){
    string line;
    bool firstLine = true;
    while(cin >> line){
        if(firstLine){
            lineLen = line.length();
            cout << "lineLen: " << lineLen << endl;
            seats.push_back(string(lineLen+2, 'x'));
            firstLine = false;
        }
        if(line == ""){
            break;
        }
        seats.push_back(string("x")+line+string("x"));
    }
    seats.push_back(string(lineLen+2, 'x'));

    printField(seats);
    cout << endl;
    for(vector<string> newSeats = iterate(seats); newSeats != seats; seats = newSeats, newSeats = iterate(seats)){
        printField(newSeats);
        cout << endl;
    }
    printField(seats);
    cout << endl;
    cout << countOccupied(seats) << endl;
    return 0;
}
