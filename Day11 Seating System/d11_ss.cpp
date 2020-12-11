#include <iostream>
#include <vector>

using namespace std;

vector<string> seats;
int lineLen;

bool occ(const vector<string> &seats, int row, int col){
    return seats[row][col] == '#';
}

int adjOccSeats(const vector<string> &s, int r, int c){
    return  occ(s,r-1,c-1) + occ(s,r-1,c) + occ(s,r-1,c+1)+
            occ(s,r,  c-1) +/*occ(s,r,c)+*/ occ(s,r,c+1)+
            occ(s,r+1,c-1) + occ(s,r+1,c) + occ(s,r+1,c+1);
}

vector<string> iterate(const vector<string> &seats){
    vector<string> newSeats(seats);
    for(int r = 1; r <= lineLen; r++){
        for(int c = 1; c <= seats.size(); c++){
            if(seats[r][c] == 'L' && adjOccSeats(seats, r,c) == 0){
                newSeats[r][c] = '#';
            } else if (seats[r][c] == '#' && adjOccSeats(seats, r,c) >= 4){
                newSeats[r][c] = 'L';
            }
        }
    }
    return newSeats;
}

void printField(){
    for(auto s : seats){
        cout << s << endl;
    }
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
            seats.push_back(string(lineLen+2, 'x'));
            firstLine = false;
        }
        if(line == ""){
            break;
        }
        seats.push_back(string("x")+line+string("x"));
    }
    seats.push_back(string(lineLen+2, 'x'));
    printField();
    cout << endl;
    for(vector<string> newSeats = iterate(seats); newSeats != seats; newSeats = iterate(seats)){
        printField();
        cout << endl;
        seats = newSeats;
    }
    printField();
    cout << endl;
    cout << countOccupied(seats) << endl;
    return 0;
}
