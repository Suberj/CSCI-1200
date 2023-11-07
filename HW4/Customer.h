//
// Created by suber on 2/12/2023.
//

#ifndef CODE_CUSTOMER_H
#define CODE_CUSTOMER_H
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <algorithm>

class Customer {
public:
    //CONSTRUCTOR
    Customer(std::string aFile);

    //ACCESSORS
    const std::list<std::string> return_data() const {return data;}
    const std::list<std::string> return_id() const {return id;}
    const std::list<std::string> return_times() const {return times;}
    const std::list<std::string> return_rent() const {return rent_list;}
    const std::list<std::string> return_wait() const {return wait_list;}
    std::string get_quantity(std::string time_num);
    std::string get_item(std::string time_num);
    std::string get_name(std::string time_num);
    std::string rent_return(std::string time_num);
    std::string get_customer_id(std::string time_num);
    std::string rented_quantity(std::string customer_id, std::string item_id);
    std::string id_to_name(std::string customer_id);
    bool did_rent(std::string customer_id, std::string item_id);

    //SETTERS
    void add_rent(std::string time_num);
    bool erase_rent(std::string customer_id, std::string item_id);
    void add_wait(std::string time_num);
    void erase_wait(std::string customer_id, std::string item_id);
    void subtract_rented(std::string customer_id, std::string item_id, int quantity);

    //SORT
    void sort_id();

private:
    std::string file_name;
    std::list<std::string> data;
    std::list<std::string> id;
    std::list<std::string> times;
    std::list<std::string> wait_list;
    std::list<std::string> rent_list;
};


#endif //CODE_CUSTOMER_H
