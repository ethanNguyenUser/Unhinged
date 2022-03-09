//
//  AttributeTranslator.cpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#include "AttributeTranslator.h"

//This is the AttributeTranslator constructor. It must take no arguments.
AttributeTranslator::AttributeTranslator(){
    //TODO: Stub
    
}

//You may define a destructor for AttributeTranslator if you need one to free any dynamically
//allocated memory used by your object.
AttributeTranslator::~AttributeTranslator(){
    //TODO: Stub

}

//This method loads the attribute-value translation data from the data file specified by the
//filename parameter. The method must load the data into a data structure that enables efficient
//translation of attribute-value pairs (meeting the big-O requirements at the top of this section).
//The method must return true if the file was successfully loaded and false otherwise.
bool AttributeTranslator::Load(std::string filename){
    //TODO: Stub
    return false;
}

//This method must identify all compatible attribute-value pairs for the specified source attribute-
//value pair in an efficient manner (meeting the requirements at the top of this section) and return
//a vector containing them. If there are no compatible pairs, the vector returned must be empty.
//There is no particular order required for the AttValPairs in the vector returned. The vector
//returned must not contain two attribute-value pairs with the same attributes and values (i.e., no
//duplicates).
std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const{
    //TODO: Stub
    std::vector<AttValPair> v;
    return v;
}
