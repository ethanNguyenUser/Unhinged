//
//  PersonProfile.cpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#include "PersonProfile.h"

//This constructs a PersonProfile object, specifying the member’s name and email address.
PersonProfile::PersonProfile(std::string name, std::string email){
    //TODO: Stub
}

//You may define a destructor for PersonProfile if you need one.
PersonProfile::~PersonProfile(){
    //TODO: Stub
}

//std::string GetName() const
std::string PersonProfile::GetName() const{
    //TODO: Stub
    return "";
}

//The getName method returns the member’s email address.
std::string PersonProfile::GetEmail() const{
    //TODO: Stub
    return "";
}

//The AddAttValPair method is used to add a new attribute-value pair to the member’s profile. If
//the person’s profile already has an attribute-value pair with the same attribute and value as the
//attval parameter, then this method should do nothing. More than one attribute-value pair in the
//map can have the same attribute, as long as their corresponding values are different. We place
//no requirements on the order that you must store your attribute-value pairs.
void PersonProfile::AddAttValPair(const AttValPair& attval){
    //TODO: Stub
}

//This method returns the total number of distinct attribute-value pairs associated with this
//member
int PersonProfile::GetNumAttValPairs() const{
    //TODO: Stub
    return 0;
}

//This method gets the attribute-value pair specified by attribute_num (where 0 <= attribute_num
// < GetNumAttValPairs()) and places it in the attval parameter. The method returns true if it
//successfully retrieves an attribute; otherwise, it returns false and leaves attval unchanged. If you
//write a loop like this
bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const{
    //TODO: Stub
    return false;
}
