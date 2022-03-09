//
//  RadixTree.hpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/8/22.
//

#ifndef RadixTree_h
#define RadixTree_h

#include <iostream>

const int NODE_ARRAY_SIZE = 127;

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
    void print(){
        std::cerr << "print()" << std::endl;
        printNodes(root, 0);
    }
    
private:
    struct Node{
        Node(std::string subKey, ValueType val) : subKey(subKey), val(val), isEnd(true){
        }
        ~Node(){
            for(int i = 0; i < NODE_ARRAY_SIZE; i++){
                if(next[i] != nullptr)
                    delete next[i];
            }
        }
        std::string subKey;
        ValueType val;
        bool isEnd;
        Node* next[NODE_ARRAY_SIZE] = {nullptr};
    };
    
    void printNodes(Node* p, int depth){
        if(p == nullptr)
            return;
        if(p->subKey != ""){
            std::cerr << std::string(depth, '\t') << p->subKey << ",";
            if(p->isEnd)
                std::cerr << p->val;
            std::cerr << std::endl;
        }
        for(int i = 0; i < NODE_ARRAY_SIZE; i++){
            if(p->next[i] != nullptr)
                printNodes(p->next[i], depth + 1);
        }
    }
    
    bool keyMatchesSubKey(std::string key, std::string sub);
    Node* root;
};

//returns whether sub matches with first part of key
template <typename ValueType>
bool RadixTree<ValueType>::keyMatchesSubKey(std::string key, std::string sub){
    if(sub.length() < key.length())
        return false;
    return key.substr(sub.length()) == sub;
}


//The RadixTree constructor.
template <typename ValueType>
RadixTree<ValueType>::RadixTree(){
    root = new Node("", 0);
    root->isEnd = false;
}

//You may define a destructor for RadixTree if you need one to free any dynamically allocated
//memory used by your object.
template <typename ValueType>
RadixTree<ValueType>::~RadixTree(){
    delete root;
}

//The insert method must update the Radix Tree to associate the specified key string with a copy
//of the passed-in value. Inserting the same item twice should simply replace the original value
//with the new value.
template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value){
    //no elements initially
//    if(root == nullptr){
//        root = new Node(key, value);
//        return;
//    }
    
    //loop through each character in the key
    Node* p = root;
    int i = 0;
    int subKeyIndex = 0;
    for(; i < key.size(); i++){
        char c = key[i];
        
        //if the subKeyIndex is greater than or equal to the length of the subKey for the Node p, that means the key goes past this current Node
        if(p->subKey.size() <= subKeyIndex){
            //if the key's next character doesn't exist in the p's next array, create a new Node
            if(p->next[c] == nullptr){
                p->next[c] = new Node(key.substr(i), value);
                return;
            }
            //otherwise, the RadixTree still has more Nodes that may match part of or all of the key, so set it to it's next Node that correspond to what is in the key
            else{
                p = p->next[c];
            }
            subKeyIndex = 0;
        }
        
        //if the subKey character matches the key character, increment the subKeyIndex
        if(c == p->subKey[subKeyIndex]){
            subKeyIndex++;
        }
        //the key's character doesn't match what we have in the Node, so we need to create two new Nodes by splitting up the current Node
        else{
            p->isEnd = false;
            //from original
            std::string nextSubKey = p->subKey.substr(subKeyIndex);
            p->subKey = p->subKey.substr(0, subKeyIndex);
            
            //from new key
            p->next[c] = new Node(key.substr(i), value);
            
            //from original
            p->next[nextSubKey[0]] = new Node(nextSubKey, p->val);
//            Node* temp = p->next[nextSubKey[0]];
//            temp->next = nullptr;
            
            return;
        }
        
    }
    //need to check when key is already contained as a subset of some element in the radix tree (e.g. car in card)
    if(subKeyIndex >= p->subKey.size())
        p->isEnd = true;

    //if we looped through the entire key's characters without returning, we have a duplicate key, so set the value
    p->val = value;
    
}

//The search method is responsible for searching your Radix Tree for the specified key. If the key
//is found, then the search method must return a pointer to the value associated with the key. If
//the specified key was not found, the method must return nullptr. If this method returns a non-null
//pointer, the caller is free to modify the value held within the Radix Tree, e.g
template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const{
    Node* p = root;
    while(true){
        if(p->isEnd && p->val == key){
            break;
        }
    }
    return new ValueType();
}

#endif /* RadixTree_h */
