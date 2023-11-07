#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include "fighters.h"

//You may add additional typedefs, includes, etc. up here

//This is the only array you are allowed to have in your program.
const std::string move_names[7] = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};
const std::set<std::string> move_set = {"jab", "forward-tilt", "up-tilt", "down-tilt", "forward-smash", "up-smash", "down-smash"};
//Feel free to put forward declarations her
//============================================================================================================//
//These functions will make maps for each of the seven attacks
//These maps will store the names as keys and then the frames as the values
std::set<std::pair<int, std::string>> make_jab (const std::set<fighters>& data) {
    std::set<std::pair<int, std::string>> tmp;
    std::set<fighters>::const_iterator citr;
    for(citr = data.begin(); citr != data.end(); citr++) {
        fighters f = *citr;
        std::pair<int, std::string> p;
        p.first = f.get_jab();
        p.second = f.get_name();
        tmp.insert(p);
    }
    return tmp;
}
std::set<std::pair<int, std::string>> make_fwdT (const std::set<fighters>& data) {
    std::set<std::pair<int, std::string>> tmp;
    std::set<fighters>::const_iterator citr;
    for(citr = data.begin(); citr != data.end(); citr++) {
        fighters f = *citr;
        std::pair<int, std::string> p;
        p.first = f.get_fwdT();
        p.second = f.get_name();
        tmp.insert(p);
    }
    return tmp;
}
std::set<std::pair<int, std::string>> make_downT (const std::set<fighters>& data) {
    std::set<std::pair<int, std::string>> tmp;
    std::set<fighters>::const_iterator citr;
    for(citr = data.begin(); citr != data.end(); citr++) {
        fighters f = *citr;
        std::pair<int, std::string> p;
        p.first = f.get_downT();
        p.second = f.get_name();
        tmp.insert(p);
    }
    return tmp;
}
std::set<std::pair<int, std::string>> make_upT (const std::set<fighters>& data) {
    std::set<std::pair<int, std::string>> tmp;
    std::set<fighters>::const_iterator citr;
    for(citr = data.begin(); citr != data.end(); citr++) {
        fighters f = *citr;
        std::pair<int, std::string> p;
        p.first = f.get_upT();
        p.second = f.get_name();
        tmp.insert(p);
    }
    return tmp;
}
std::set<std::pair<int, std::string>> make_fwdS (const std::set<fighters>& data) {
    std::set<std::pair<int, std::string>> tmp;
    std::set<fighters>::const_iterator citr;
    for(citr = data.begin(); citr != data.end(); citr++) {
        fighters f = *citr;
        std::pair<int, std::string> p;
        p.first = f.get_fwdS();
        p.second = f.get_name();
        tmp.insert(p);
    }
    return tmp;
}
std::set<std::pair<int, std::string>> make_upS (const std::set<fighters>& data) {
    std::set<std::pair<int, std::string>> tmp;
    std::set<fighters>::const_iterator citr;
    for(citr = data.begin(); citr != data.end(); citr++) {
        fighters f = *citr;
        std::pair<int, std::string> p;
        p.first = f.get_upS();
        p.second = f.get_name();
        tmp.insert(p);
    }
    return tmp;
}
std::set<std::pair<int, std::string>> make_downS (const std::set<fighters>& data) {
    std::set<std::pair<int, std::string>> tmp;
    std::set<fighters>::const_iterator citr;
    for(citr = data.begin(); citr != data.end(); citr++) {
        fighters f = *citr;
        std::pair<int, std::string> p;
        p.first = f.get_downS();
        p.second = f.get_name();
        tmp.insert(p);
    }
    return tmp;
}
//============================================================================================================//
//this will create the set of fighters
std::set<fighters> parsing (const std::string& file) {
    std::ifstream input;
    input.open(file);
    //this holds all of the fighters
    std::set<fighters> tmp;
    std::string word;
    //skips the headers
    for(int i = 0; i < 8; i++) {
        input >> word;
    }
    //hold the values for fighters class
    std::string name;
    int jab;
    int FT;
    int UT;
    int DT;
    int FS;
    int US;
    int DS;
    while(input.good()) {
        input >> name;
        input >> jab;
        input >> FT;
        input >> UT;
        input >> DT;
        input >> FS;
        input >> US;
        input >> DS;
        fighters f(name, jab, FT, UT,
                   DT, FS, US, DS);
        tmp.insert(f);
    }
    return tmp;
}
//============================================================================================================//
//These next set of functions allow me to output the different stats to the output file
//used if -q is called
void prints_q(std::ofstream& MyFile, std::string name, std::string move, std::set<fighters> f_set) {
    //finding fighter
    fighters f;
    //searches for name and if found stores it in f
    for(std::set<fighters>::iterator itr = f_set.begin(); itr != f_set.end(); itr++) {
        fighters tmp = *itr;
        if(tmp.get_name() == name) {
            f = tmp;
            break;
        }
    }
    //if it wants all stats
    if(move == "all") {
        MyFile << name << " down-smash: " << f.get_downS() << std::endl;
        MyFile << name << " down-tilt: " << f.get_downT() << std::endl;
        MyFile << name << " forward-smash: " << f.get_fwdS() << std::endl;
        MyFile << name << " forward-tilt: " << f.get_fwdT() << std::endl;
        MyFile << name << " jab: " << f.get_jab() << std::endl;
        MyFile << name << " up-smash: " << f.get_upS() << std::endl;
        MyFile << name << " up-tilt: " << f.get_upT() << std::endl;
    }
    //if they just want one stat
    else {
        if(move == "down-smash") {
            MyFile << name << " down-smash: " << f.get_downS() << std::endl;
        }
        else if(move == "down-tilt") {
            MyFile << name << " down-tilt: " << f.get_downT() << std::endl;
        }
        else if(move == "forward-smash") {
            MyFile << name << " forward-smash: " << f.get_fwdS() << std::endl;
        }
        else if(move == "forward-tilt") {
            MyFile << name << " forward-tilt: " << f.get_fwdT() << std::endl;
        }
        else if(move == "jab") {
            MyFile << name << " jab: " << f.get_jab() << std::endl;
        }
        else if(move == "up-smash") {
            MyFile << name << " up-smash: " << f.get_upS() << std::endl;
        }
        else if(move == "up-tilt") {
            MyFile << name << " up-tilt: " << f.get_upT() << std::endl;
        }
    }
}
//used if -f is called
void prints_f(std::ofstream& MyFile, std::string move, int limit, std::set<fighters> f_set) {
    //will store the info for the given move
    std::set<std::pair<int, std::string>> data;
    //this will change what data holds based on inputs
    if(move == "down-smash") {
        data = make_downS(f_set);
    }
    else if(move == "down-tilt") {
        data = make_downT(f_set);
    }
    else if(move == "forward-smash") {
        data = make_fwdS(f_set);
    }
    else if(move == "forward-tilt") {
        data = make_fwdT(f_set);
    }
    else if(move == "jab") {
        data = make_jab(f_set);
    }
    else if(move == "up-smash") {
        data = make_upS(f_set);
    }
    else if(move == "up-tilt") {
        data = make_upT(f_set);
    }
    //printing desired number of fighters with the fastest move
    MyFile << "-f " << move << " " << limit << std::endl; //heading
    std::set<std::pair<int, std::string>>::iterator itr = data.begin();
    for(int i = 0; i < limit; i++) {
        std::pair<int,std::string> p = *itr;
        MyFile << p.second << " " << p.first << std::endl;
        itr++;
    }
}
//used if -s is called
void prints_s(std::ofstream& MyFile, std::string move, int limit, std::set<fighters> f_set) {
    //will store the info for the given move
    std::set<std::pair<int, std::string>> data;
    //this will change what data holds based on inputs
    if(move == "down-smash") {
        data = make_downS(f_set);
    }
    else if(move == "down-tilt") {
        data = make_downT(f_set);
    }
    else if(move == "forward-smash") {
        data = make_fwdS(f_set);
    }
    else if(move == "forward-tilt") {
        data = make_fwdT(f_set);
    }
    else if(move == "jab") {
        data = make_jab(f_set);
    }
    else if(move == "up-smash") {
        data = make_upS(f_set);
    }
    else if(move == "up-tilt") {
        data = make_upT(f_set);
    }
    //printing desired number of fighters with the slowest move
    MyFile << "-s " << move << " " << limit << std::endl; //heading
    //making map that stores frames as the key and a set of names as the values
    std::map<int, std::set<std::string>> f_map;
    std::set<int> keys; //getting keys for the map
    //looping through data and inserting the data to
    std::set<std::pair<int, std::string>>::iterator itr;
    for(itr = data.begin(); itr != data.end(); itr++) {
        std::pair<int,std::string> p = *itr;
        int frame = p.first;
        std::string name = p.second;
        //if in map already
        if(f_map.find(frame) != f_map.end()) {
            f_map[frame].insert(name);
        }
            //if not already in map
        else {
            std::set<std::string> tmp;
            tmp.insert(name);
            f_map[frame] = tmp;
            keys.insert(frame);
        }
    }
    //keep track of where we are in map
    std::set<int>::reverse_iterator ritr;
    int count = 0;
    //stops when limit is reached
    //this is what prints the names
    //prints them first by slowest frames
    //and second alphabetically by name
    while (count < limit) {
        for(ritr = keys.rbegin(); ritr != keys.rend(); ritr++) {
            std::set<std::string> names = f_map[*ritr];
            std::set<std::string>::iterator itr1 = names.begin();
            for(; itr1 != names.end(); itr1++) {
                std::string n = *itr1;
                MyFile << n << " " << *ritr << std::endl;
                count++;
                if(count > limit-1) {
                    break;
                }
            }
            if(count > limit-1) {
                break;
            }
        }
    }
}
//used if -d is called
void prints_d(std::ofstream& MyFile, std::string move, int start, std::set<fighters> f_set) {
    //will store the info for the given move
    std::set<std::pair<int, std::string>> data;
    //this will change what data holds based on inputs
    if(move == "down-smash") {
        data = make_downS(f_set);
    }
    else if(move == "down-tilt") {
        data = make_downT(f_set);
    }
    else if(move == "forward-smash") {
        data = make_fwdS(f_set);
    }
    else if(move == "forward-tilt") {
        data = make_fwdT(f_set);
    }
    else if(move == "jab") {
        data = make_jab(f_set);
    }
    else if(move == "up-smash") {
        data = make_upS(f_set);
    }
    else if(move == "up-tilt") {
        data = make_upT(f_set);
    }
    //printing to file
    MyFile << "-d " << move << " " << start << std::endl; //heading
    std::set<std::pair<int, std::string>>::iterator itr;
    for(itr = data.begin(); itr != data.end(); itr++) {
        std::pair<int,std::string> p = *itr;
        if(p.first == start) {
            MyFile << p.second << std::endl;
        }
    }
}
//============================================================================================================//
//============================================================================================================//
int main(int argc, char** argv){
	// Argument parsing
	if(argc != 4){
		std::cerr << "Proper usage is " << argv[0] << " [database file] [input file] [output file]" << std::endl;
		return -1;
	}

	std::ifstream dbfile(argv[1]);
	if(!dbfile){
		std::cerr << "Failed to open database " << argv[1] << " for reading." << std::endl;
	}

	std::ifstream infile(argv[2]);
	if(!infile){
		std::cerr << "Failed to open input " << argv[2] << " for reading." << std::endl;
	}

	std::ofstream outfile(argv[3]);
	if(!outfile){
		std::cerr << "Failed to open output " << argv[3] << " for writing." << std::endl;
	}

	///////Fill in the rest of main below:
    std::set<fighters> f_set; //contains all fighters data
    //making the data
    f_set = parsing(argv[1]);
    //creating a map that holds names of fighters and available moves
    //this will be used to check the validity of the inputs
    std::set<std::string> valid;
    std::set<fighters>::const_iterator citr;
    for(citr = f_set.begin(); citr != f_set.end(); citr++) {
        fighters tmp = *citr;
        valid.insert(tmp.get_name());
    }
    //This is where the functions get called
    //This is where all of the info is written on the output file
    while(infile.good()) {
        std::string call;
        std::string first;
        infile >> call;
        infile >> first;
        if(call == "-q") {
            std::string move;
            infile >> move;
            //checking if move is valid
            //the .find() function for sets is O(logN)
            if((valid.find(first) != valid.end())) {
                //if name and move is valid then it calls the function to write data to outfile
                if(move_set.find(move) != move_set.end()) {
                    prints_q(outfile, first, move, f_set);
                }
                else if(move == "all") {
                    prints_q(outfile, first, move, f_set);
                }
                //if move not found then it writes error in outfile
                else {
                    outfile << "Invalid move name: " << move << std::endl;
                }
            }
            //checking to see if name is valid
            //the time complexity is O(logN)
            else {
                outfile << "Invalid character name: " << first << std::endl;
            }
        }
        else if(call == "") {
            continue;
        }
        else {
            int num;
            infile >> num;
            //checking if move is valid
            //if move is valid then the data is written to outfile
            //the .find() function for sets is O(logN)
            if(move_set.find(first) != move_set.end()) {
                if (call == "-d") {
                    prints_d(outfile, first, num, f_set);
                }
                if (call == "-f") {
                    prints_f(outfile, first, num, f_set);
                }
                if (call == "-s") {
                    prints_s(outfile, first, num, f_set);
                }
            }
            //if move not found then it writes error in outfile
            else {
                outfile << "Invalid move name: " << first << std::endl;
            }
        }
        outfile << std::endl;
    }
	return 0;
}
