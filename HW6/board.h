//
// Created by suber on 3/8/2023.
//

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class Board {
public:
    //constructors
    Board();
    Board(int arows, int acols);
    Board(const Board& board);
    //accessors
    int size() const {return cols*rows;};
    int filled() const;
    int get_rows() const {return rows;};
    int get_cols() const {return cols;};
    //modifiers
    void insert(const std::string& word, int r, int c, int y, int x); //inserts the words in the board
    //others
    bool SpaceForWord(const std::string& word,
                      int r, int c, int y, int x); //check if word can go in board
    bool present(std::string word); //this will start the present function
    //operators
    const std::vector<char>& operator[] (int i) const; //allows for [] notation with board
    std::vector<char>& operator[] (int i); //allows for [] notation with board
private:
    int rows;
    int cols;
    std::vector <std::vector<char>> letters; //this is the actual board
    bool search(int i, int j, std::string word, int k); //this will search for words in the board
};
//used for printing
std::ostream& operator<< (std::ostream& out, const Board& board);
//equal operator
bool operator== (const Board& board1, const Board& board2);

#endif
