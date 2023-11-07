//
// Created by suber on 4/10/2023.
//

#ifndef ds_hashset_h_
#define ds_hashset_h_

//Most of this is reused from lab 11 implementation
#include <list>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>
#include <string>
// The ds_hashset is templated over both the type of key and the type
// of the hash function, a function object.
template <class HashFunc>
class ds_hashset {
private:
    std::vector<std::pair<std::string, std::list<int>>> m_table;
    HashFunc m_hash;
    unsigned int m_size;
    float m_occupancy;
public:
    //==========================
    //Constructors
    //==========================
    //Default constructor
    ds_hashset(unsigned int init_size = 100, float init_occupancy = 0.5)
            : m_table(init_size), m_size(0), m_occupancy(init_occupancy) {}
    //copy constructor
    ds_hashset(const ds_hashset<HashFunc>& old)
            : m_table(old.m_table), m_size(old.m_size), m_occupancy(old.m_occupancy) {}
    //descontructor
    ~ds_hashset() {}
    //==========================
    //Operators
    //==========================
    //equal operator used when checking copy constructor
    ds_hashset& operator=(const ds_hashset<HashFunc>& old) {
        if (&old != this) {
            this->m_table = old.m_table;
            this->m_size = old.m_size;
            this->m_hash = old.m_hash;
            this->m_occupancy = old.m_occupancy;
        }
        return *this;
    }
    //====================================
    //other functions
    //====================================
    //Insert the key if it is not already there.
    //Adds the given key and its position to the hash table.
    void insert(const std::string& key, const int pos) {
        const unsigned int resize = static_cast<unsigned int>(m_occupancy * m_table.size());
        //sees if table needs to be resized
        if (m_size >= resize) {
            resize_table(2 * m_table.size());
        }
        //getting hashvalue to figure out where it needs to be inserted
        //if slot is empty puts it there
        //if not does a sort of linear probing to find where it needs to be inserted
        unsigned int hash_value = m_hash(key) % m_table.size();
        while (!m_table[hash_value].first.empty() && m_table[hash_value].first != key) {
            hash_value = (hash_value + 1) % m_table.size();
        }
        if (m_table[hash_value].first.empty()) {
            m_size++;
        }
        m_table[hash_value].first = key;
        m_table[hash_value].second.push_back(pos);
    }
    //find the key in list and return position
    const std::list<int> getPosition(const std::string& key, const int& kmer) const {
        //extract the prefix of length kmer from the key
        const std::string prefix = std::string(key.begin() + 0, key.begin() + 0 + kmer);
        //compute the hash value for the prefix
        unsigned int hash_value = m_hash(prefix);
        //search for the prefix in the hash table using open addressing
        unsigned int index = hash_value % m_table.size();
        unsigned int start_index = index;
        while (!m_table[index].first.empty() && m_table[index].first != prefix) {
            index = (index + 1) % m_table.size();
            if (index == start_index) {
                //went through the whole table without finding the prefix
                return std::list<int>();
            }
        }
        //return the list of positions associated with the prefix, if found
        if (m_table[index].first == prefix) {
            return m_table[index].second;
        }
        else {
            return std::list<int>();
        }
    }
    //====================================
    //Modifiers
    //====================================
    //this is a way to access the resize table function
    void setSize(unsigned int i) {m_size = i;
        resize_table(i);};
    void setOccupancy(float i) {m_occupancy = i;};
//======================================================================================================
//private functions
private:
    //resize the table with the same values but twice as many buckets
    void resize_table(unsigned int new_size) {
        //making new table
        std::vector<std::pair<std::string, std::list<int>>> new_table(new_size);
        //going through every entry in old table
        for(unsigned int i = 0; i < m_table.size(); i++) {
            const std::string& key = m_table[i].first;
            if (!key.empty()) {
                //find new value and index
                unsigned int hash_value = m_hash(key);
                unsigned int index = hash_value % new_size;
                //insert values into new table
                while (!new_table[index].first.empty()) {
                    index = (index + 1) % new_size;
                }
                new_table[index] = m_table[i];
            }
        }
        //update m_table to new_table
        m_table = std::move(new_table);
    }
};

#endif
