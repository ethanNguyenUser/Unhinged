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
        std::string source = "";
        std::string comp = "";
        
        //build source att-val pair
        int commaCounter = 0;
        for(; commaCounter < 2; i++){
            if(line[i] == ',')
                commaCounter++;
            source += line[i];
        }
        i++;

        //build compatible att-val pair
        commaCounter = 0;
        for(; i != line.size(); i++){
            if(line[i] == ',')
                commaCounter++;
            comp += line[i];
        }
        
        //insert mappng of source to comp
        
        //the vector of values for the parameter attribute exists
        std::vector<std::string>* comps = sourceToComp.search(source);
        if(comps != nullptr){
            //if the value doesn't already exist in the values vector, push back the new value into the values vector
            if(std::find(comps->begin(), comps->end(), comp) == comps->end())
                comps->push_back(comp);
        }
        //otherwise, insert a new vector
        else{
            std::vector<std::string> newComps = {comp};
            sourceToComp.insert(source, newComps);
        }
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
    std::vector<AttValPair> compPairs(0);

    //if no match, return an empty vector, comps is a pointer to a vector of strings of form "compatible_attribute,compatible_value"
    std::vector<std::string>* comps = sourceToComp.search(source.attribute);
    if(comps == nullptr)
        return compPairs;
    
    for(int i = 0; i < comps->size(); i++){
        std::string comp = (*comps)[i];
        size_t commaIndex = comp.find(',');
        compPairs.push_back(AttValPair(comp.substr(0, commaIndex), comp.substr(commaIndex + 1, comp.size())));
    }
    
    return compPairs;
}
