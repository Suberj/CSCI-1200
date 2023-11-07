#include <iostream>
#include <list>
#include "Inventory.h"
#include "Customer.h"

int main(int argc, char*argv[]) {

    if(argc == 5) {

        std::string i_file = argv[1];
        std::string c_file = argv[2];
        std::string i_output = argv[3];
        std::string c_output = argv[4];

        //creating classes
        Inventory inventory(i_file);
        Customer customer(c_file);
        //getting data
        //inventory data
        std::list<std::string> i_data;
        i_data = inventory.return_data();
        inventory.sort_id();
        std::list<std::string> item_id;
        item_id = inventory.return_id();
        //customer data
        std::list<std::string> c_data;
        c_data = customer.return_data();
        customer.sort_id();
        std::list<std::string> customer_sorted_id = customer.return_id();
        std::list<std::string> time_stamps;
        time_stamps = customer.return_times();

        //loop going through all of the timestamps
        std::list<std::string>::iterator itr;
        for (itr = time_stamps.begin(); itr != time_stamps.end(); itr++) {
            std::string time = *itr;
            std::string rr = customer.rent_return(time);
            //getting customer info
            std::string item = customer.get_item(time);
            std::string quantity = customer.get_quantity(time);
            std::string customer_id = customer.get_customer_id(time);
            std::string customer_name = customer.get_name(time);
            //checking if renting or returning
            if (rr == "rent") {
                std::list<std::string>::iterator itr1;
                int check = 0; //checking if item is valid
                for (itr1 = item_id.begin(); itr1 != item_id.end(); itr1++) {
                    if (*itr1 == item) {
                        check++;
                    }
                }
                if (check > 0) {
                    std::string item_name = inventory.get_name(item);
                    std::string item_quantity = inventory.get_quantity(item);
                    //checking if there is enough of the item for the customer to rent
                    int int_quantity = stoi(quantity);
                    if (item_quantity >= quantity) {
                        for (int i = 0; i < int_quantity; i++) {
                            inventory.subtract(item);
                        }
                        customer.add_rent(customer_id);
                        customer.add_rent(item);
                        customer.add_rent(quantity);
                    } else {
                        customer.add_wait(customer_id);
                        customer.add_wait(item);
                        customer.add_wait(quantity);
                    }
                }
                else {
                    std::cerr << "Customer " << customer_id << " requested item " << item
                              << " which is not in the inventory." << std::endl;
                }
            }
            else if (rr == "return") {
                int check = 0;
                std::list<std::string>::iterator it;
                for (it = item_id.begin(); it != item_id.end(); it++) {
                    if (item == *it) {
                        check++;
                        break;
                    }
                }
                if (check > 0) {
                    if (customer.did_rent(customer_id, item)) {
                        //erasing the customers rent transaction from rent list and getting the quantity they returned
                        std::string rent_quantity = customer.rented_quantity(customer_id, item);
                        std::string return_quantity = customer.get_quantity(time);
                        //if they returned less than they rented this will adjust the numbers
                        if (rent_quantity > return_quantity) {
                            int num = stoi(return_quantity);
                            for (int i = 0; i < num; i++) {
                                inventory.add(item);
                            }
                            customer.subtract_rented(customer_id, item, num);

                            //dealing with wait list
                            std::list<std::string> w_list = customer.return_wait();
                            std::string rent_customer; //will hold id of customer who wants to rent returned item
                            std::string rent_quantity1; //will hold quantity of item that person wants to rent
                            std::list<std::string>::iterator itr;
                            for (itr = w_list.begin(); itr != w_list.end(); itr++) {
                                if (*itr == item) {
                                    itr++;
                                    rent_quantity1 = *itr;
                                    //checking if person wants to return less then there is
                                    std::string item_quantity = inventory.get_quantity(item);
                                    if (rent_quantity1 <= item_quantity) {
                                        itr--;
                                        itr--;
                                        rent_customer = *itr;

                                        //adding to rent list
                                        customer.add_rent(rent_customer);
                                        customer.add_rent(item);
                                        customer.add_rent(rent_quantity1);
                                        //erasing from wait list
                                        customer.erase_wait(rent_customer, item);
                                        //adjusting available quantity
                                        int int_quantity = stoi(rent_quantity1);
                                        for (int i = 0; i < int_quantity; i++) {
                                            inventory.subtract(item);
                                        }
                                        break;
                                    }
                                }
                            }

                        }
                            //if customer returned the same amount they rented this will adjust
                        else if (rent_quantity == return_quantity) {
                            int num = stoi(return_quantity);
                            for (int i = 0; i < num; i++) {
                                inventory.add(item);
                            }
                            customer.erase_rent(customer_id, item);

                            //dealing with wait list
                            std::list<std::string> w_list = customer.return_wait();
                            std::string rent_customer; //will hold id of customer who wants to rent returned item
                            std::string rent_quantity1; //will hold quantity of item that person wants to rent
                            std::list<std::string>::iterator itr;
                            for (itr = w_list.begin(); itr != w_list.end(); itr++) {
                                if (*itr == item) {
                                    itr++;
                                    rent_quantity1 = *itr;
                                    //checking if person wants to return less then there is
                                    std::string item_quantity = inventory.get_quantity(item);
                                    if (rent_quantity1 <= item_quantity) {
                                        itr--;
                                        itr--;
                                        rent_customer = *itr;

                                        //adding to rent list
                                        customer.add_rent(rent_customer);
                                        customer.add_rent(item);
                                        customer.add_rent(rent_quantity1);
                                        //erasing from wait list
                                        customer.erase_wait(rent_customer, item);
                                        //adjusting available quantity
                                        int int_quantity = stoi(rent_quantity1);
                                        for (int i = 0; i < int_quantity; i++) {
                                            inventory.subtract(item);
                                        }
                                        break;
                                    }
                                }
                            }

                        }
                            //if they returned item they did not rent
                        else {
                            std::cerr << "Customer " << customer_id << " attempted to return item " << item
                                      << " which she/he did not rent." << std::endl;
                        }
                    }

                        //this will go off if the item is not in inventory
                    else {
                        std::cerr << "Customer " << customer_id << " attempted to return item " << item
                                  << " which is not in the inventory." << std::endl;
                    }
                }
                else {
                    std::cerr << "Customer " << customer_id << " attempted to return item " << item
                              << " which is not in the inventory." << std::endl;
                }
            }
                //gives error if they did not rent or return item
            else {
                std::cerr << "Neither rented or returned" << std::endl;
            }
        }

        //making customer output file
        //getting data that will be needed for customer output
        std::list<std::string> rent_list;
        rent_list = customer.return_rent(); //return list is formated - {customer_id, item_id, quantity_rented ...}
        std::list<std::string> wait_list;
        wait_list = customer.return_wait(); //wait list is formated - {customer_id, item_id, quantity_rented ...}
        //starting customer output
        std::ofstream myfile; //use myfile << to write to customer output file
        myfile.open(c_output); //opening customer output file to write to
        std::list<std::string>::iterator itr3;
        for (itr3 = customer_sorted_id.begin(); itr3 != customer_sorted_id.end(); itr3++) {
            std::string cid = *itr3; //customer id
            std::string cname = customer.id_to_name(cid); //customer name

            //finding if customer is on rent list
            std::list<std::string> crent; //will hold data if customer is on rent list currently
            std::list<std::string>::iterator it;
            for (it = rent_list.begin(); it != rent_list.end(); it++) {
                if (*it == cid) {
                    it++;
                    crent.push_back(*it);
                    it++;
                    crent.push_back(*it);
                }
            }

            //finding if customer is on wait list
            std::list<std::string> cwait; //will hold data if customer is on wait list currently
            for (it = wait_list.begin(); it != wait_list.end(); it++) {
                if (*it == cid) {
                    it++;
                    cwait.push_back(*it);
                    it++;
                    cwait.push_back(*it);
                }
            }

            //outputting to file
            if (crent.size() > 0 || cwait.size() > 0) {
                myfile << cid << " " << cname << std::endl;
                //outputting rentals customer has currently
                if (crent.size() > 0) {
                    myfile << "Rentals: ";
                    for (it = crent.begin(); it != crent.end(); it++) {
                        myfile << *it;
                        it++;
                        myfile << " (" << *it << ") ";
                    }
                    myfile << std::endl;
                }
                //outputting pending rentals customer currently has
                if (cwait.size() > 0) {
                    myfile << "Pending: ";
                    for (it = cwait.begin(); it != cwait.end(); it++) {
                        myfile << *it;
                        it++;
                        myfile << " (" << *it << ") ";
                    }
                    myfile << std::endl;
                }
            }
            myfile << std::endl;
        }
        myfile.close();
        //making inventory outputfile
        std::ofstream myfile1; //use myfile1 << to write to customer output file
        myfile1.open(i_output); //opening customer output file to write to
        std::list<std::string>::iterator itr4;
        for (itr4 = item_id.begin(); itr4 != item_id.end(); itr4++) {
            std::string iid = *itr4;
            std::string iname = inventory.get_name(iid);
            std::string available_q = inventory.get_quantity(iid);
            //finding if item is being rented
            std::list<std::string> irent; //will hold data if item is being rented
            std::list<std::string>::iterator it;
            for (it = rent_list.begin(); it != rent_list.end(); it++) {
                if (*it == iid) {
                    it--;
                    std::string customer_name = customer.id_to_name(*it);
                    irent.push_back(*it);
                    irent.push_back(customer_name);
                    it++;
                    it++;
                    irent.push_back(*it);
                }
            }
            //finding if item is pending
            std::list<std::string> iwait; //will hold data if item is pending
            for (it = wait_list.begin(); it != wait_list.end(); it++) {
                if (*it == iid) {
                    it--;
                    std::string customer_name = customer.id_to_name(*it);
                    iwait.push_back(*it);
                    iwait.push_back(customer_name);
                    it++;
                    it++;
                    iwait.push_back(*it);
                }
            }

            //outputting to file
            myfile1 << iid << " " << available_q << " available " << iname << std::endl;
            //outputting rentals customer has currently
            if (irent.size() > 0) {
                myfile1 << "Rental Customers: ";
                std::list<std::string>::iterator it1;
                for (it1 = customer_sorted_id.begin(); it1 != customer_sorted_id.end(); it1++) {
                    for (it = irent.begin(); it != irent.end(); it++) {
                        if (*it == *it1) {
                            myfile1 << *it;
                            it++;
                            myfile1 << " " << *it;
                            it++;
                            myfile1 << " (" << *it << ") ";
                        }
                    }
                }
                myfile1 << std::endl;
            }
            //outputting pending rentals customer currently has
            if (iwait.size() > 0) {
                myfile1 << "Pending Customers: ";
                std::list<std::string>::iterator it1;
                for (it1 = customer_sorted_id.begin(); it1 != customer_sorted_id.end(); it1++) {
                    for (it = iwait.begin(); it != iwait.end(); it++) {
                        if (*it == *it1) {
                            myfile1 << *it;
                            it++;
                            myfile1 << " " << *it;
                            it++;
                            myfile1 << " (" << *it << ") ";
                        }
                    }
                }
                myfile1 << std::endl;
            }
            myfile1 << std::endl;
        }
        myfile1.close();
    }
    else {
        std::cerr << "Wrong amount of inputs were inputted";
        std::cerr << "(rental.exe inventory_file customer_file inventory_output_file customer_output_file)" << std::endl;
    }
}
