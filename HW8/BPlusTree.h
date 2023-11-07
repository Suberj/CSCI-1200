/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>


#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree;

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; }

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>;
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////
template <class T>
class BPlusTree{
public:
    // Constructors & Destructor
    BPlusTree(int s);
    BPlusTree(const BPlusTree<T>& old);
    ~BPlusTree();
    //main two functions for this HW
    BPlusTreeNode<T>* find(const T& key) const {return find(key, root);}
    void insert(const T& key) {insert(key, root, NULL);}
    // Print
    void print_sideways(std::ostream& out) const;
    void print_BFS(std::ostream& out) const;
    //Operators
    BPlusTree<T>& operator=(const BPlusTree<T>& old);
private:
    // Representation
    BPlusTreeNode<T>* root;
    int size_;
    //used for the constructor/deconstructors
    BPlusTreeNode<T>* copy(BPlusTreeNode<T>* old_root, BPlusTreeNode<T>* parent);
    void destroy(BPlusTreeNode<T>* p);
    //these are the recursion functions for the public driver functions
    BPlusTreeNode<T>* find(const T& key, BPlusTreeNode<T>* p) const;
    void insert(const T& key, BPlusTreeNode<T>*& node, BPlusTreeNode<T>* parent);
    //helper function for the prints
    void print_sideways(std::ostream& outfile, BPlusTreeNode<T>* node, int depth) const;
    //helper function for insert
    void split(const T& key, BPlusTreeNode<T>*& node, BPlusTreeNode<T>* parent, unsigned int i);
};
///////////////////////////////////////////////////////////////////////////////////////
//Implementation of functions
///////////////////////////////////////////////////////////////////////////////////////
//Constructor
//Default
template <class T>
BPlusTree<T>::BPlusTree(int s) {
    root = NULL;
    size_ = s;
}
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& old){
    size_ = old.size_;
    root = this->copy(old.root, NULL);
}
//Deconstructor
//this will help with memory leaks
template <class T>
BPlusTree<T>::~BPlusTree() {
    this->destroy(root);
    root = NULL;
}
///////////////////////////////////////////////////////////////////////////////////////
//Operators
//used to set trees equal
template <class T>
BPlusTree<T>& BPlusTree<T>::operator=(const BPlusTree<T>& old) {
    if (&old != this) {
        this->destroy(root);
        root = this->copy(old.root, NULL);
        size_ = old.size_;
    }
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////
//find
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key, BPlusTreeNode<T>* p) const {
    //checking if tree is empty
    //if tree is empty should return NULL
    if (this->root == NULL) {
        return NULL;
    }
    //this is the bulk of the function
    //this will recursively look for the element where it goes down a level each time
    unsigned int i = 0;
    for (; i < p->keys.size(); i++) {
        if (key < p->keys[i]) {
            if (p->is_leaf()) {
                return p;
            }
            else{
                return find(key, p->children[i]);
            }
        }
    }
    //this will check right most branch of the tree
    //had to add this in because it was not going far enough
    if (p->is_leaf()) {
        return p;
    }
    else {
        return find(key, p->children[i]);
    }
}
///////////////////////////////////////////////////////////////////////////////////////
//insert function
//this is where the majority of the time and thinking went into in this HW
///////////////////////////////////////////////////////////////////////////////////////
//to insert you have to first find where to insert then if there is no space you have to
//take the middle term, clear the leaf, put the middle element in the leaf, and then
//put the two lower values in the branch to the left and the bigger two values in the branch
//to the right
///////////////////////////////////////////////////////////////////////////////////////
//helper function for insert to split function
//this is just to neaten up the code and easier to understand while writing
//split function does most of the heavy lifting for the insert function
template <class T>
void BPlusTree<T>::split(const T& key, BPlusTreeNode<T>*& node, BPlusTreeNode<T>* parent, unsigned int i) {
    if (!node->is_leaf()) {
        //insert the key recursively into the child node
        insert(key, node->children[i], node);

        //check if the child node is full
        if (node->children[i]->keys.size() >= this->size_) {
            //split the child node in half
            unsigned int left = node->children[i]->keys.size() / 2;
            unsigned int right = node->children[i]->keys.size() - left;

            BPlusTreeNode<T>* new_child = new BPlusTreeNode<T>();
            new_child->parent = node;

            //move the second half
            while (new_child->keys.size() != right) {
                new_child->keys.insert(new_child->keys.begin(), node->children[i]->keys.back());
                node->children[i]->keys.pop_back();
            }

            //move the second half
            if (!node->children[i]->is_leaf()) {
                while (new_child->children.size() != new_child->keys.size() + 1) {
                    new_child->children.insert(new_child->children.begin(), node->children[i]->children.back());
                    new_child->children.front()->parent = new_child;
                    node->children[i]->children.pop_back();
                }
            }

            //determine the parent key
            T parent_key = node->children[i]->keys.back();
            if (node->children[i]->is_leaf()) {
                parent_key = new_child->keys.front();
            }
            else {
                node->children[i]->keys.pop_back();
            }

            //insert the parent key and new child into the node's parent
            typename std::vector<T>::iterator keys_itr = node->keys.begin();
            typename std::vector<BPlusTreeNode<T>*>::iterator children_itr = node->children.begin();
            node->keys.insert(keys_itr + i, parent_key);
            node->children.insert(children_itr + i + 1, new_child);
        }

        //check if the node root needs to be split
        if (parent == nullptr && node->keys.size() >= this->size_) {
            //finding two starting nodes
            unsigned int left;
            unsigned int right;
            left = node->keys.size()/2;
            //finding right side node
            if (node->is_leaf()) {
                right = node->keys.size() - left;
            }
            else{
                right = node->keys.size() - left - 1;
            }
            //creating child
            BPlusTreeNode<T>* child = new BPlusTreeNode<T>();
            //this will add keys to left
            while (child->keys.size() != right) {
                child->keys.insert(child->keys.begin(), node->keys.back());
                node->keys.pop_back();
            }
            //this will add keys to right
            if (!node->is_leaf()) {
                while (child->children.size() != right + 1) {
                    child->children.insert(child->children.begin(), node->children.back());
                    child->children.front()->parent = child;
                    node->children.pop_back();
                }
            }
            //creating parent
            BPlusTreeNode<T>* parent = new BPlusTreeNode<T>();
            node->parent = parent;
            child->parent = parent;
            if (node->is_leaf()) {
                parent->keys.push_back(child->keys.front());
            }
            else {
                parent->keys.push_back(node->keys.back());
                node->keys.pop_back();
            }
            parent->children.push_back(node);
            parent->children.push_back(child);
            this->root = parent;
        }
    }
    else {
        // Insert the key into the leaf node
        typename std::vector<T>::iterator itr = node->keys.begin();
        node->keys.insert(itr + i, key);

        // Check if the leaf node's parent needs to be split
        if (parent == nullptr && node->keys.size() >= this->size_) {
            //finding two starting nodes
            unsigned int left;
            unsigned int right;
            left = node->keys.size()/2;
            //finding right side node
            if (node->is_leaf()) {
                right = node->keys.size() - left;
            }
            else{
                right = node->keys.size() - left - 1;
            }
            //creating child
            BPlusTreeNode<T>* child = new BPlusTreeNode<T>();
            //this will add keys to left
            while (child->keys.size() != right) {
                child->keys.insert(child->keys.begin(), node->keys.back());
                node->keys.pop_back();
            }
            //this will add keys to right
            if (!node->is_leaf()) {
                while (child->children.size() != right + 1) {
                    child->children.insert(child->children.begin(), node->children.back());
                    child->children.front()->parent = child;
                    node->children.pop_back();
                }
            }
            //creating parent
            BPlusTreeNode<T>* parent = new BPlusTreeNode<T>();
            node->parent = parent;
            child->parent = parent;
            if (node->is_leaf()) {
                parent->keys.push_back(child->keys.front());
            }
            else {
                parent->keys.push_back(node->keys.back());
                node->keys.pop_back();
            }
            parent->children.push_back(node);
            parent->children.push_back(child);
            this->root = parent;
        }
    }
}
//actual insert
template <class T>
void BPlusTree<T>::insert(const T& key, BPlusTreeNode<T>*& node, BPlusTreeNode<T>* parent) {
    //if empty need to make new tree
    if (this->root == NULL) {
        this->root = new BPlusTreeNode<T>();
        this->root->keys.push_back(key);
        return;
    }
    //checking keys
    //finding position to insert properly
    unsigned int i = 0;
    for (; i < node->keys.size(); ++i) {
        if (key < node->keys[i]) {
            split(key, node, parent, i);
            return;
        }
    }
    split(key, node, parent, i);
}
///////////////////////////////////////////////////////////////////////////////////////
//print functions
//helper for print function
template <class T>
void BPlusTree<T>::print_sideways(std::ostream& out, BPlusTreeNode<T>* p, int level) const {
    if (this->root == nullptr) {
        out << "Tree is empty." << std::endl;
        return;
    }
    const unsigned int left = p->children.size() / 2;
    const unsigned int right = p->children.size() - left;
    //printing left side
    for (unsigned int i = 0; i < left; ++i) {
        print_sideways(out, p->children[i], level + 1);
    }
    for (int i = 0; i < level; ++i) {
        out << '\t';
    }
    out << p->keys[0];
    for (unsigned int i = 1; i < p->keys.size(); ++i) {
        out << ',' << p->keys[i];
    }
    out << std::endl;
    //printing right side
    for (unsigned int i = left; i < left + right; ++i) {
        print_sideways(out, p->children[i], level + 1);
    }
}
//driver function
template <class T>
void BPlusTree<T>::print_sideways(std::ostream& out) const {
    if (root) {
        print_sideways(out, root, 0);
    }
    else {
        out << "Tree is empty." << std::endl;
    }
}
//this is the second print function that the assignment calls for
//this one prints vertical and justified left
template <class T>
void BPlusTree<T>::print_BFS(std::ostream& out) const {
    if(root) {
        //holds the data that needs to be printed
        std::vector<std::vector<BPlusTreeNode<T>*>> levels;
        std::vector<BPlusTreeNode<T>*> level;
        level.push_back(root);
        levels.push_back(level);
        //going through one level at a time
        for (unsigned int i = 0; i < levels.size(); i++) {
            //printing node keys and adding children to next level
            for (unsigned int j = 0; j < levels[i].size(); j++) {
                BPlusTreeNode<T>* node = levels[i][j];
                for (unsigned int k = 0; k < node->keys.size(); k++) {
                    out << node->keys[k];
                    if (k < node->keys.size() - 1) {
                        out << ",";
                    }
                }
                out << "\t";
                if (!node->is_leaf()) {
                    std::vector<BPlusTreeNode<T>*> children = node->children;
                    levels.push_back(children);
                }
            }
            out << std::endl;
        }
    }
    //if nothing in tree tells the user the tree is empty
    else {
        out << "Tree is empty." << std::endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//Private function implementations
///////////////////////////////////////////////////////////////////////////////////////
//this is used in the copy constructor
template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy(BPlusTreeNode<T>* old, BPlusTreeNode<T>* parent) {
    // Base case
    if (old == NULL) {
        return NULL;
    }
    //Creating new node
    BPlusTreeNode<T>* tmp = new BPlusTreeNode<T>();
    //This will copy the children of the nodes
    for (unsigned int i = 0; i < old->children.size(); ++i) {
        tmp->children.push_back(copy(old->children[i], tmp));
    }
    //making tmp values when at end
    tmp->keys = old->keys;
    tmp->parent = parent;
    //returns tmp values
    return tmp;
}
//used for deconstructor and to stop memory leaks
template <class T>
void BPlusTree<T>::destroy(BPlusTreeNode<T>* p) {
    //Base case
    if (p == NULL) {
        return;
    }
    //Deleting
    for (unsigned int i = 0; i < p->children.size(); ++i) {
        destroy(p->children[i]);
    }
    delete p;
}
///////////////////////////////////////////////////////////////////////////////////////
#endif
