//
//  RadixTree.hpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/8/22.
//

#ifndef RadixTree_h
#define RadixTree_h

//● MUST be a class template, implemented fully in RadixTree.h.
//● MUST hold a number of nodes that is proportional to the number of unique key-value
//pairs inserted in the Radix Tree, NOT a number of nodes that is proportional to the
//number of keys times the average key length.
//● MUST have a big-O for insertion of O(K) where K is the maximum key length of a new
//item being inserted into the Radix Tree, and for searches, O(K) where K is the maximum
//key length of the items in the Radix Tree.
//● MUST be case-sensitive for all searches
//● MUST be able to accommodate any number of key-value pairs
//● MUST NOT use the STL map, unordered_map, multimap, or unordered_multimap types
//(in your final submission)
//● MUST NOT add any new public member functions or variables
//● MAY avoid dealing with an empty key string
//● MAY use the STL set, list and vector classes
//● MAY have any private member functions or variables you choose to add

template <typename ValueType>
class RadixTree{
public:
 RadixTree();
 ~RadixTree();
 void insert(std::string key, const ValueType& value);
 ValueType* search(std::string key) const;
    
private:
    struct Node{
//        Node(std::string subKey, ValueType val, ){
//
//        }
        std::string subKey;
        ValueType val;
        bool isEnd;
        Node* next[];

    };
};

//The RadixTree constructor.

RadixTree::RadixTree(){
    
}

//You may define a destructor for RadixTree if you need one to free any dynamically allocated
//memory used by your object.
RadixTree::~RadixTree(){
    
}

//The insert method must update the Radix Tree to associate the specified key string with a copy
//of the passed-in value. Inserting the same item twice should simply replace the original value
//with the new value. The insert method needs to consider a number of special cases and edge
//conditions; here are a few to consider (this is not an exhaustive list of edge conditions).
void RadixTree::insert(std::string key, const ValueType& value){
    
}

//The search method is responsible for searching your Radix Tree for the specified key. If the key
//is found, then the search method must return a pointer to the value associated with the key. If
//the specified key was not found, the method must return nullptr. If this method returns a non-null
//pointer, the caller is free to modify the value held within the Radix Tree, e.g
ValueType* RadixTree::search(std::string key) const{
    return new ValueType();
}


#endif /* RadixTree_h */
