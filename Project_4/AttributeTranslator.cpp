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
AttributeTranslator::~AttributeTranslator(){}

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
        for(;; i++){
            if(line[i] == ',')
                commaCounter++;
            if(commaCounter == 2)
                break;
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
        
        //for testing
//        std::cerr << source << "|" << comp << std::endl;
        
        //insert mappng of source to comp
        std::unordered_set<std::string>* comps = sourceToComp.search(source);
        
        //if the vector of comps exists already for a particular source, insert into the unordered_set the comp
        if(comps != nullptr)
            comps->insert(comp);
    
        //otherwise, insert a new vector
        else{
            std::unordered_set<std::string> newComps = {comp};
            sourceToComp.insert(source, newComps);
        }
    }
    inFile.close();
    
    //for testing
//    sourceToComp.print();

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
    std::unordered_set<std::string>* comps = sourceToComp.search(source.attribute + "," + source.value);

    if(comps == nullptr)
        return compPairs;
    
    for(std::unordered_set<std::string>::iterator it = comps->begin(); it != comps->end(); it++){
        std::string comp = *it;
        size_t commaIndex = comp.find(',');
        compPairs.push_back(AttValPair(comp.substr(0, commaIndex), comp.substr(commaIndex + 1)));
    }
    
    return compPairs;
}
