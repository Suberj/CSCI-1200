//
// Created by suber on 2/12/2023.
//

#include "Customer.h"

//CONSTRUCTOR
Customer::Customer(std::string aFile) {
    file_name = aFile;

    //opening file
    std::ifstream text;
    text.open(file_name);
    std::string word;
    text >> word;

    while(text.good()) {
        if(word.find('C') != std::string::npos) {
            data.push_back(word);
            text >> word;
            data.push_back(word);
            text >> word;
            data.push_back(word);
            text >> word;
            data.push_back(word);
            text >> word;
            data.push_back(word);
            text >> word;
            data.push_back(word);
        }
        else {
            std::cerr << "Invalid customer information found for ID " << word << " in the customer file." << std::endl;
            text >> word;
            text >> word;
            text >> word;
            text >> word;
            text >> word;
        }

        text >> word;
    }
}

//ACCESSORS
std::string Customer::get_quantity(std::string time_num) {
    std::list<std::string>::iterator itr;
    for (itr = data.begin(); itr != data.end(); itr++) {
        if (*itr == time_num) {
            itr++;
            return *itr;
        }
    }
}

std::string Customer::get_item(std::string time_num) {
    std::list<std::string>::iterator itr;
    for (itr = data.begin(); itr != data.end(); itr++) {
        if (*itr == time_num) {
            itr++;
            itr++;
            return *itr;
        }
    }
}

std::string Customer::get_name(std::string time_num) {
    std::list<std::string>::iterator itr;
    for (itr = data.begin(); itr != data.end(); itr++) {
        if (*itr == time_num) {
            itr++;
            itr++;
            itr++;
            return *itr;
        }
    }
}

std::string Customer::rent_return(std::string time_num) {
    std::list<std::string>::iterator itr;
    for (itr = data.begin(); itr != data.end(); itr++) {
        if (*itr == time_num) {
            itr--;
            return *itr;
        }
    }
}

std::string Customer::get_customer_id(std::string time_num) {
    std::list<std::string>::iterator itr;
    for (itr = data.begin(); itr != data.end(); itr++) {
        if (*itr == time_num) {
            itr--;
            itr--;
            return *itr;
        }
    }
}

bool Customer::did_rent(std::string customer_id, std::string item_id) {
    std::list<std::string>::iterator itr;
    for (itr = rent_list.begin(); itr != rent_list.end(); itr++) {
        if(*itr == customer_id) {
            itr++;
            if(*itr == item_id) {
                return true;
            }
        }
    }
    return false;
}

std::string Customer::rented_quantity(std::string customer_id, std::string item_id) {
    std::list<std::string>::iterator itr;
    for (itr = rent_list.begin(); itr != rent_list.end(); itr++) {
        if(*itr == customer_id) {
            itr++;
            if(*itr == item_id) {
                itr++;
                std::string time = *itr;
                return time;
            }
        }
    }
}

std::string Customer::id_to_name(std::string customer_id) {
    std::list<std::string>::iterator it;
    for(it = data.begin(); it != data.end(); it++) {
        if(*it == customer_id) {
            it++;
            it++;
            it++;
            it++;
            it++;
            return *it;
        }
    }
}

//SORT
void Customer::sort_id() {
    //while loop that ads all IDs as string ordered in a list
    //This will be used to order everything in the list
    int count = 0;
    std::list<std::string>::iterator it;
    for(it = data.begin(); it != data.end(); it++) {
        std::string word = *it;
        if(id.size() == 0) {
            id.push_back(word);
        }
        else if(count%6 == 0 && (std::find(id.begin(), id.end(), word) == id.end())) {
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

    //creating times list
    std::list<std::string>::iterator it1;
    for(it1 = data.begin(); it1 != data.end(); it1++) {
        if(*it1 == "rent" || *it1 == "return") {
            it1++;
            times.push_back(*it1);
        }
    }
}

//SETTERS
void Customer::add_rent(std::string time_num) {
    rent_list.push_back(time_num);
}

bool Customer::erase_rent(std::string customer_id, std::string item_id) {
    std::list<std::string>::iterator itr;
    for (itr = rent_list.begin(); itr != rent_list.end(); itr++) {
        if(*itr == customer_id) {
            itr++;
            if(*itr == item_id) {
                itr--;
                itr = rent_list.erase(itr);
                itr = rent_list.erase(itr);
                itr = rent_list.erase(itr);
                return true;
            }
        }
    }
    return false;
}

void Customer::add_wait(std::string time_num) {
    wait_list.push_back(time_num);
}

void Customer::erase_wait(std::string customer_id, std::string item_id) {
    std::list<std::string>::iterator itr;
    for (itr = wait_list.begin(); itr != wait_list.end(); itr++) {
        if(*itr == customer_id) {
            itr++;
            if(*itr == item_id) {
                itr--;
                itr = wait_list.erase(itr);
                itr = wait_list.erase(itr);
                itr = wait_list.erase(itr);
                break;
            }
        }
    }
}

void Customer::subtract_rented(std::string customer_id, std::string item_id, int quantity) {
    std::list<std::string>::iterator itr;
    for (itr = rent_list.begin(); itr != rent_list.end(); itr++) {
        if(*itr == customer_id) {
            itr++;
            if(*itr == item_id) {
                itr++;
                //subtracting one to quantity rented
                int num = stoi(*itr);
                num -= quantity;
                std::string str_num = std::to_string(num);
                *itr = str_num;
                break;
            }
        }
    }
}
