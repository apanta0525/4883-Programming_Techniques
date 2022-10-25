
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<int> string_split(string str) {
    vector<int> result;
    istringstream iss(str);
    for (int s; iss >> s;)
        result.push_back(s);
    return result;
}

int process(vector<int> nums, int cases) {

    int chessBoard[8][8] = {};

    int row = 0, col = 0;
    int moves = 0;
    int minMoves = 1000;
    int count = 0;



    for (int x = 0; x < nums.size(); x++) {
        col = row = nums[x];
        chessBoard[row - 1][col - 1] = 1; //place queens
        count++;

        if (count == 8) {
            break;
        }
    }

    //we will start at row = 0, col = 0
    row = 0, col = 0;
    cout << endl;




navigateColumn:
    // Move to the next column
    col++;
    if (col == 8) goto updateMinMoves;
    row = -1;

navigateRow:
    // Move to the next row
    row++;
    moves++;
    if (row == 8) goto tryBackTrack;
    // row test 
    for (int i = 0; i < col; i++) {
        if (chessBoard[row][i] == 1) goto navigateRow;
    }
    // move diagonally 
    for (int i = 1; ((row - i) >= 0 && (col - i) >= 0); i++) {
        if (chessBoard[row - i][col - i] == 1) goto navigateRow;
    }
    // move diagonally 
    for (int i = 1; ((row + i) <= 7 && (col - i) >= 0); i++) {
        if (chessBoard[row + i][col - i] == 1) goto navigateRow;
    }
    chessBoard[row][col] = 1;
    goto navigateColumn;

tryBackTrack:
    // go to previous column
    col--;
    moves--;
    if (col == -1) {
        cout << "Case "<<cases <<":" << minMoves << " ";
        return 0;
    }
    //update visited
    row = 0;
    while (chessBoard[row][col] != 1) {
        row++;
    }
    // remove queen
    chessBoard[row][col] = 0;
    //goto navigateRow;
    goto navigateRow;

updateMinMoves:
    if (moves < minMoves) {
        minMoves = moves;
    }
    moves = 0;
    goto tryBackTrack;
}

int main() {

    fstream newfile;
    newfile.open("input.txt", ios::in);
    int cases = 1;
    if (newfile.is_open()) { //checking whether the file is open
        string tp;
        while (getline(newfile, tp)) { //read data from file object and put it into string.
            vector<int> nums = string_split(tp);
            process(nums,cases);
            
            cases++;
        }
        newfile.close(); //close the file object.
    }


}

