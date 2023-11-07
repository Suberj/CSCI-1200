//
// Created by suber on 2/12/2023.
//

#include "Inventory.h"
#include <iostream>

//CONSTRUCTOR
Inventory::Inventory(std::string aFile) {
    file_name = aFile;

    //opening file
    std::ifstream text;
    text.open(file_name);
    std::string word;
    text >> word;

    while(text.good()) {
        if(word.find('T') != std::string::npos) {
            data.push_back(word);
            text >> word;
            data.push_back(word);
            text >> word;
            data.push_back(word);
        }
        else {
            std::cerr << "Invalid inventory ID " << word << " found in the inventory file." << std::endl;
            text >> word;
            text >> word;
        }
        text >> word;
    }

}

//GET FUNCTIONS
std::string Inventory::get_name(std::string id_num) {
    std::list<std::string>::iterator itr;
    for(itr = data.begin(); itr != data.end() ; itr++) {
        if(*itr == id_num) {
            itr++;
            itr++;
            return *itr;
        }
    }
    return NULL;
}

std::string Inventory::get_quantity(std::string id_num) {
    std::list<std::string>::iterator itr;
    for(itr = data.begin(); itr != data.end() ; itr++) {
        if(*itr == id_num) {
            itr++;
            return *itr;
        }
    }
    return NULL;
}

//SORT
void Inventory::sort_id() {
    //while loop that ads all IDs as string ordered in a list
    //This will be used to order everything in the list
    int count = 0;
    std::list<std::string>::iterator it;
    for(it = data.begin(); it != data.end(); it++) {
        std::string word = *it;
        if(id.size() == 0) {
            id.push_back(word);
        }
        else if(count%3 == 0 && (std::find(id.begin(), id.end(), word) == id.end())) {
            std::string last_word = id.back();
            if(word < last_word) {
                id.push_back(word);
            }
            else {
                std::list<std::string>::iterator itr;
                for (itr = id.begin(); itr != id.end(); itr++) {
                    if (*itr < word) {
                        id.insert(itr, word);
                        break;
                    }
                }
            }
        }
        count++;
    }
    //flipping list because they are in descending order currently
    id.reverse();
}

//OTHER FUNCTIONS
void Inventory::add(std::string id_num) {
    std::list<std::string>::iterator itr;
    for(itr = data.begin(); itr != data.end() ; itr++) {
        if(*itr == id_num) {
            itr++;
            int num = stoi(*itr);
            num++;
            std::string str_num = std::to_string(num);
            *itr = str_num;
        }
    }
}

void Inventory::subtract(std::string id_num) {
    std::list<std::string>::iterator itr;
    for(itr = data.begin(); itr != data.end() ; itr++) {
        if(*itr == id_num) {
            itr++;
            int num = stoi(*itr);
            num--;
            std::string str_num = std::to_string(num);
            *itr = str_num;
        }
    }
}


