//
// Created by suber on 4/10/2023.
//

#include <fstream>
#include <cassert>
#include <cstdlib>
#include "ds_hashset.h"

//hash function from lab 11
class hash_string_obj {
public:
    unsigned int operator() ( const std::string& key ) const {
        //  This implementation comes from
        //  http://www.partow.net/programming/hashfunctions/
        //
        //  This is a general-purpose, very good hash function for strings.
        unsigned int hash = 1315423911;
        for(unsigned int i = 0; i < key.length(); i++)
            hash ^= ((hash << 5) + key[i] + (hash >> 2));
        return hash;
    }
};
typedef ds_hashset<hash_string_obj> ds_hashset_type;
//===========================================================================================================
//function that will proccess the queries
//this will return a vector that holds all the matches
//the matches are held in groups of 3
//the first is the position, the second is the error, and the third is the match itself
//this is the easiest way to print them all out
std::vector<std::string> query(const std::string& genome, int kmer, const ds_hashset_type& hash_table,
                               const std::string& data, int tolerance) {
    std::vector<std::string> results; //will hold the matching results
    //finding position of possible matches to genome
    std::list<int> positions = hash_table.getPosition(genome, kmer);
    std::list<int>::iterator itr;
    //looping through positions to see if they word
    for(itr = positions.begin(); itr != positions.end() && *itr <= data.size() - genome.size(); itr++) {
        std::string key = std::string(data.begin() + *itr, data.begin() + *itr + genome.size());
        //comparing the geneome user inputs to possible matches in the hashtable
        int count = 0;
        for (unsigned int i = 0; i < genome.size(); ++i) {
            if (key[i] != genome[i]) {
                count++;
                if (count > tolerance) {
                    break;
                }
            }
        }
        //pushing back valid results to list
        if(count <= tolerance) {
            std::string position = std::to_string(*itr);
            std::string error = std::to_string(count);
            results.push_back(position);
            results.push_back(error);
            results.push_back(key);
        }
    }
    return results;
}
//===========================================================================================================
int main() {
    //initializing hashtable
    ds_hashset_type hash_table;
    //initalizing other variables that will be needed
    int kmer;
    int tolerance;
    float occ;
    unsigned int size;
    std::string word; //hold the words from cin
    std::ifstream input; //will be used as our input file
    std::string data; //will hold a long string that contains all of the data for genomes
    //does not stop until user inputs quit
    //there is a condition later that will stop it when quit it inputted
    while(std::cin >> word) {
        //if the user inputs genome that indicates the input file is next word
        if(word == "genome") {
            std::cin >> word;
            input.open(word);
            std::string tmp; //words in the input file
            //if file is valid then this will add all of the genome data into one string
            //this will allow for it to be put into hashtable easier once we know kmer
            if(input.good()) {
                while(input >> tmp) {
                    data = data + tmp;
                }
            }
            //if file cannot open error will occur
            else {
                std::cerr << "File " << word << " cannot open." << std::endl;
            }

        }
        //after user inputs kmer the next value is an int for the kmer
        else if(word == "kmer") {
            std::cin >> kmer;
            //creating the hashtable since we have all the info we need to create it
            for(unsigned int i = 0; i <= data.size(); i++) {
                //gets a portion of the data and puts it into the hashtable
                std::string key = std::string(data.begin() + i, data.begin() + i + kmer);
                hash_table.insert(key, i);
            }
        }
        //these next two are optional for the user to input
        //these allow the user to set and change the table size and the occupancy
        else if(word == "table_size") {
            std::cin >> size;
            hash_table.setSize(size);
        }
        else if(word == "occupancy") {
            std::cin >> occ;
            hash_table.setOccupancy(occ);
        }
        //this is the biggest one and will be the bulk of this assignment
        else if(word == "query") {
            std::cin >> tolerance;
            std::cin >> word; //holds the genome data that is inputed by user
            std::cout << "Query: " << word << std::endl; //priting heading for query
            //using query function to find matches for the genome inputted
            std::vector<std::string> matches = query(word, kmer, hash_table, data, tolerance);
            if(matches.empty()) {
                std::cout << "No Match" << std::endl;
            }
            //printing matches
            else {
                for(unsigned int i = 0; i < matches.size()-2; i++) {
                    std::cout << matches[i] << " " << matches[i+1] << " " << matches[i+2] << std::endl;
                }
            }
        }
        else if(word == "quit") {
            break;
        }
    }
}
