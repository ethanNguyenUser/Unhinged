//
//  AttributeTranslator.cpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#include "AttributeTranslator.h"
#include <fstream>

//This is the AttributeTranslator constructor. It must take no arguments.
AttributeTranslator::AttributeTranslator(){
    
}

//You may define a destructor for AttributeTranslator if you need one to free any dynamically
//allocated memory used by your object.
AttributeTranslator::~AttributeTranslator(){
    
}

//This method loads the attribute-value translation data from the data file specified by the
//filename parameter. The method must load the data into a data structure that enables efficient
//translation of attribute-value pairs (meeting the big-O requirements at the top of this section).
//The method must return true if the file was successfully loaded and false otherwise.
bool AttributeTranslator::Load(std::string filename){
    std::ifstream inFile;
    inFile.open(filename);
    
    //check file opened
    if (!inFile)
        return false;

    std::string line;
    while (getline(inFile, line)){
        if(line == "")
            continue;
        int i = 0;
        std::string sourceA = "";
        std::string sourceV = "";
        std::string compA = "";
        std::string compV = "";

        for(; line[i] != ','; i++)
            sourceA += line[i];
        i++;
        for(; line[i] != ','; i++)
            sourceV += line[i];
        i++;
        for(; line[i] != ','; i++)
            compA += line[i];
        i++;
        for(; i != line.size(); i++)
            compV += line[i];
        
//        if()
//        sourceAVPairs.insert(sourceA, sourceV);
//        sourceKeys.push_back(sourceA);
//        
//        compAVPairs.insert(compA, compV);
//        compKeys.push_back(compA);
    }
    inFile.close();
    
    return true;
}

//This method must identify all compatible attribute-value pairs for the specified source attribute-
//value pair in an efficient manner (meeting the requirements at the top of this section) and return
//a vector containing them. If there are no compatible pairs, the vector returned must be empty.
//There is no particular order required for the AttValPairs in the vector returned. The vector
//returned must not contain two attribute-value pairs with the same attributes and values (i.e., no
//duplicates).
std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const{
    std::vector<AttValPair> v;
    return v;
}
