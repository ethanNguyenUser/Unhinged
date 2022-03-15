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
    void print() const{
        std::cerr << "print()" << std::endl;
        for(int i = 0; i < NODE_ARRAY_SIZE; i++){
            printNodes(root.next[i], 0);
        }
    }
    
private:
    struct Node{
        Node(std::string subKey, ValueType val, Node* parent = nullptr, bool isEnd = true);
        ~Node();
        std::string subKey;
        ValueType val;
        bool isEnd;
        Node* parent;
        Node* next[NODE_ARRAY_SIZE] = {nullptr};
    };
    
    struct RootNode{
        Node* next[NODE_ARRAY_SIZE] = {nullptr};
    };
    
    void printNodes(Node* p, int depth) const{
        if(p == nullptr)
            return;
        if(p->subKey != ""){
            std::cerr << std::string(depth, '\t') << p->subKey << "||";
            if(p->isEnd){
//                std::cerr << p->val;
                
                //for vector
//                for(int i = 0; i < p->val.size(); i++){
//                    std::cerr << p->val[i] << "|";
//                }
                
                //for unordered_set
                for(auto it = p->val.begin(); it != p->val.end(); it++){
                    std::cerr << *it << "|";
                }
                
//                std::cerr << p->val.GetName();
            }
            else
                std::cerr << "*";
            std::cerr << std::endl;
        }
        for(int i = 0; i < NODE_ARRAY_SIZE; i++){
            if(p->next[i] != nullptr)
                printNodes(p->next[i], depth + 1);
        }
    }
    
    void splitNode(Node* p, const std::string& key, const std::string& subKey, const int& subKeyIndex, const ValueType& value, const int& i, bool isEnd);
    
    RootNode root;
};

//The RadixTree constructor.
template <typename ValueType>
RadixTree<ValueType>::RadixTree(){
    //create a dummy head node
}

//You may define a destructor for RadixTree if you need one to free any dynamically allocated
//memory used by your object.
template <typename ValueType>
RadixTree<ValueType>::~RadixTree(){
    for(int i = 0; i < NODE_ARRAY_SIZE; i++){
        if(root.next[i] != nullptr)
            delete root.next[i];
    }
}

//The insert method must update the Radix Tree to associate the specified key string with a copy
//of the passed-in value. Inserting the same item twice should simply replace the original value
//with the new value.
template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value){
    if(key == "")
        return;
    
    //loop through each character in the key
    Node* p = root.next[key[0]];
    if(p == nullptr){
        root.next[key[0]] = new Node(key, value);
        return;
    }
    
    int i = 0;
    int subKeyIndex = 0;
    for(; i < key.size(); i++){
        char c = key[i];

        //if the subKeyIndex is greater than or equal to the length of the subKey for the Node p, that means the key goes past this current Node
        if(p->subKey.size() <= subKeyIndex){
            //if the key's next character doesn't exist in the p's next array, create a new Node
            if(p->next[c] == nullptr){
                p->next[c] = new Node(key.substr(i), value, p);
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
        
        //the key's character doesn't match what we have in the Node, so we need to create two new Nodes by splitting up the current Node, key could be shorter or longer than subkey
        else{
            splitNode(p, key, p->subKey, subKeyIndex, value, i, false);
            return;
        }
    }
    
    //need to check when key is already contained as a subset of some element in the radix tree (e.g. insert("car") when "card" already exists)
    if(subKeyIndex < p->subKey.size()){
        splitNode(p, key, p->subKey, subKeyIndex, value, i, true);
        return;
    }

    //if we looped through the entire key's characters without returning, we have a duplicate key, so set the value
    p->val = value;
    p->isEnd = true;
}

//The search method is responsible for searching your Radix Tree for the specified key. If the key
//is found, then the search method must return a pointer to the value associated with the key. If
//the specified key was not found, the method must return nullptr. If this method returns a non-null
//pointer, the caller is free to modify the value held within the Radix Tree, e.g
template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const{
    if(key == "")
        return nullptr;
    
//    std::cerr << key << std::endl;
    if(root.next[key[0]] == nullptr)
        return nullptr;
    
    Node* p = root.next[key[0]];
    std::string subKey = "";
    while(true){
        if(p == nullptr)
            break;
        
        subKey += p->subKey;
        if(p->isEnd && subKey == key)
            return &p->val;
        
        //key goes past subKey, so keep searching
        if(key.size() > subKey.size())
            p = p->next[key[subKey.size()]];
        else
            break;
    }
    
    //reached end of search, return nullptr
    return nullptr;
}

template <typename ValueType>
RadixTree<ValueType>::Node::Node(std::string subKey, ValueType val, Node* parent, bool isEnd) : subKey(subKey), val(val), isEnd(isEnd), parent(parent){}

template <typename ValueType>
RadixTree<ValueType>::Node::~Node(){
    for(int i = 0; i < NODE_ARRAY_SIZE; i++){
        if(next[i] != nullptr)
            delete next[i];
    }
}

template <typename ValueType>
void RadixTree<ValueType>::splitNode(Node *p, const std::string& key, const std::string& subKey, const int& subKeyIndex, const ValueType& value, const int& i, bool isEnd){
    
    Node* newNode = nullptr;
    
    //if no parents
    if(p->parent == nullptr){
        //create new Node that will be the parent of the Nodes for our parameter key and the original Nodes already in the tree
        root.next[subKey[0]] = new Node(subKey.substr(0, subKeyIndex), value, p->parent, isEnd);
        newNode = root.next[subKey[0]];
    }
    
    //otherwise, there are parents
    else{
        //create new Node that will be the parent of the Nodes for our parameter key and the original Nodes already in the tree
        p->parent->next[subKey[0]] = new Node(subKey.substr(0, subKeyIndex), value, p->parent, isEnd);
        newNode = p->parent->next[subKey[0]];
    }
    
    //update p, which is the parent of all the original Nodes that collide with the parameter key
    p->parent = newNode;
    p->subKey = subKey.substr(subKeyIndex);

    //add to the new Node the Node for our parameter key
    std::string newSubkey = key.substr(i);
    newNode->next[newSubkey[0]] = new Node(newSubkey, value, newNode);

    //have newNode point to p, which was from the original tree
    newNode->next[p->subKey[0]] = p;
}

#endif /* RadixTree_h */
