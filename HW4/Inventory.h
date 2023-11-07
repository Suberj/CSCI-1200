//
// Created by suber on 2/12/2023.
//

#ifndef CODE_INVENTORY_H
#define CODE_INVENTORY_H
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

class Inventory {
public:
    //CONSTRUCTOR
    Inventory(std::string aFile);

    //ACCESSORS
    const std::list<std::string> return_data() const {return data;}
    const std::list<std::string> return_id() const {return id;}

    //GET FUNCTIONS
    std::string get_quantity(std::string id_num);
    std::string get_name(std::string id_num);

    //SORT
    void sort_id();

    //OTHER FUNCTIONS
    void add(std::string id_num);
    void subtract(std::string id_num);

private:
    std::string file_name;
    std::list<std::string> data;
    std::list<std::string> id;
};

#endif //CODE_INVENTORY_H
