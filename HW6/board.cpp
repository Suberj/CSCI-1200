//
// Created by suber on 3/8/2023.
//

#include "board.h"

//CONSTRUCTORS
//Default
Board::Board() {
    rows = 0;
    cols = 0;
}
//Normal constructor that takes in size of grids
Board::Board(int arows, int acols) {
    if (arows == 0 || acols == 0) {
        rows = 0;
        cols = 0;
    } else {
        rows = arows;
        cols = acols;
    }
    //this creates the grid for word search
    //defaults to a "0"
    for (int i = 0; i < rows; i++) {
        letters.push_back(std::vector<char>());
        for (int j = 0; j < cols; j++) {
            letters[i].push_back('z');
        }
    }
}
//this will copy the board that is taken in
Board::Board(const Board& board) {
    //gets rows and columns using accessors
    rows = board.get_rows();
    cols = board.get_cols();
    //making grid
    for (int i = 0; i < rows; i++) {
        letters.push_back(std::vector<char>());
        for (int j = 0; j < cols; j++) {
            letters[i].push_back(board[i][j]);
        }
    }
}

//ACCESSORS
//counts how many spaces have letters
//this will be used to make sure no zeros are still in grid
int Board::filled() const {
    int count = 0;
    //this nested loop goes through every letter in grid
    //adds to count if grid position is not zero
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (letters[i][j] != 'z') {
                count++;
            }
        }
    }
    return count;
}

//MODIFIERS
//inserts the word into the board
void Board::insert(const std::string& word, int r, int c, int y, int x) {
    //loops through grid changing every letter to the certain letter in the word
    for (unsigned int i = r, j = c, k = 0; k < word.size(); i += y, j += x, k++) {
        letters[i][j] = word[k];
    }
}

//operators
//allows bracket notation to access certain char of board
const std::vector<char>& Board::operator[] (int i) const {
    return letters[i];
}
//non const version of the bracket notation
//needed this after running into issues in main file
std::vector<char>& Board::operator[] (int i) {
    return letters[i];
}
//allows the printing of boards
/*
 * EXAMPLE OF PRINTED BOARD
 * Board:
 *   cat
 *   one
 */
std::ostream& operator<< (std::ostream& file, const Board& board) {
    file << "Board:";
    //loops through whole grid printing each letter one at a time
    for (int i = 0; i < board.get_rows(); i++) {
        //prints new line at start of line
        file << std::endl;
        file << "  ";
        for (int j = 0; j < board.get_cols(); j++) {
            file << board[i][j];
        }
    }
    file << std::endl;
    return file;
}
//equal operator to compare two boards
bool operator== (const Board& b1, const Board& b2) {
    //seeing if rows and columns are the same
    //this will be a quick check for the board
    //also will help with the looping and segmentation fault
    if (b1.get_rows() != b2.get_rows()) {
        return false;
    }
    else if (b1.get_cols() != b2.get_cols()) {
        return false;
    }
    //if grids are same size this will loop through both grids
    //if the letters do not line up it returns false
    for (int i = 0; i < b1.get_rows(); i++) {
        for (int j = 0; j < b1.get_cols(); j++) {
            if (b1[i][j] != b2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Board::SpaceForWord(const std::string& word,
                              int r, int c, int y, int x) {
    //ends function if the word is size zero
    //this is because that means there is no word
    if (word.size() == 0) {
        return false;
    }
    int size = word.size();
    int fr = r + (y * size);
    int fc = c + (x * size);
    //checking for segmentation faults
    if ((y == 1 && fr > rows) || (y == -1 && fr < -1)) {
        return false;
    }
    else if ((x == 1 && fc > cols) || (x == -1 && fc < -1)) {
        return false;
    }
    //loops through the grid
    for (unsigned int i = r, j = c, k = 0; k < word.size(); i += y, j += x, k++) {
        //makes sure there are no zeros still in grid
        if (letters[i][j] != word[k] && letters[i][j] != 'z') {
            return false;
        }
    }
    return true;
}

//these functions find a word in the board
//will be used to search for bad words
bool Board::search (int i, int j, std::string word, int k) {
    //found whole word
    if(k == word.size()) {
        return true;
    }
    //seeing if letters match up and checking bounds
    else if(i >= rows || i < 0 || j >= cols || j < 0 || letters[i][j] != word[k] ) {
        return false;
    }
    //checking each dirrection
    else {
        bool opt1 = search(i + 1, j, word, k + 1); //down direction
        bool opt2 = search(i, j + 1, word, k + 1); //left direction
        bool opt3 = search(i - 1, j, word, k + 1); //up direction
        bool opt4 = search(i, j - 1, word, k + 1); //right direction
        //seeing if any are true we have word in board
        return (opt1 || opt2 || opt3 || opt4);
    }
}
bool Board::present(std::string word) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if (letters[i][j] == word[0]) {
                if(search(i,j,word,0)) {
                    return true;
                }
            }
        }
    }
    return false;
}
