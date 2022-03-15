//
//  PersonProfile.cpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#include "PersonProfile.h"

//This constructs a PersonProfile object, specifying the member’s name and email address.
PersonProfile::PersonProfile(std::string name, std::string email) : name(name), email(email), numAVPairs(0){}

//You may define a destructor for PersonProfile if you need one.
PersonProfile::~PersonProfile(){}

//std::string GetName() const
std::string PersonProfile::GetName() const{
    return name;
}

//The getName method returns the member’s email address.
std::string PersonProfile::GetEmail() const{
    return email;
}

//The AddAttValPair method is used to add a new attribute-value pair to the member’s profile. If
//the person’s profile already has an attribute-value pair with the same attribute and value as the
//attval parameter, then this method should do nothing. More than one attribute-value pair in the
//map can have the same attribute, as long as their corresponding values are different. We place
//no requirements on the order that you must store your attribute-value pairs.
void PersonProfile::AddAttValPair(const AttValPair& attval){
    //if the pair is found/already exists, return
    std::unordered_set<std::string>* values = aVPairs.search(attval.attribute);
    
    //the unordered_set of values for the parameter attribute exists
    if(values != nullptr){
        if(std::find(values->begin(), values->end(), attval.value) != values->end()){
            numAVPairs++;
            aVPairsVector.push_back(AttValPair(attval.attribute, attval.value));
        }
    }
    
    //otherwise, insert a new unordered_set
    else{
        std::unordered_set<std::string> newValues = {attval.value};
        aVPairs.insert(attval.attribute, newValues);
        numAVPairs++;
        aVPairsVector.push_back(AttValPair(attval.attribute, attval.value));
    }
}

//This method returns the total number of distinct attribute-value pairs associated with this
//member
int PersonProfile::GetNumAttValPairs() const{
    return numAVPairs;
}

//This method gets the attribute-value pair specified by attribute_num (where 0 <= attribute_num
// < GetNumAttValPairs()) and places it in the attval parameter. The method returns true if it
//successfully retrieves an attribute; otherwise, it returns false and leaves attval unchanged.
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{    
    if(attribute_num < 0 || attribute_num >= numAVPairs)
        return false;
    
    attval = aVPairsVector[attribute_num];
    return true;
}
