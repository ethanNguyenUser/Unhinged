//
//  MemberDatabase.cpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#include "MemberDatabase.h"

//Person 1’s name
//Person 1’s email address
//Count of number of attribute-value pairs for person 1
//attr1,value1
//attr2,value2
//…
//attrN,valueN

//The member database constructor.
MemberDatabase::MemberDatabase(){
    //TODO: Stub
}

//You may define a destructor for MemberDatabase if you need one to free any dynamically
//allocated memory used by your object.
MemberDatabase::~MemberDatabase(){
    //TODO: Stub
}

//This method loads the member database from the data file specified by the filename parameter,
//e.g., members.txt. The method must load the data into data structures that enable efficient
//retrieval of email addresses (meeting the big-O requirements at the top of this section). The
//method must return true if the file was successfully loaded and false otherwise. If two members
//in the data file have the same email address, this method returns false.
bool MemberDatabase::LoadDatabase(std::string filename){
    //TODO: Stub
    return false;
}

//This method must identify all members that have the specified input attribute-value pair in an
//efficient manner (meeting the requirements at the top of this section) and return a vector
//containing their email addresses. If there are no such members, the vector returned must be
//empty. There is no particular order required for the email addresses in the vector returned. The
//vector returned must not contain duplicate email addresses.
std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const{
    //TODO: Stub
    std::vector<std::string> v;
    return v;
}

//Given an email address, this method must determine if a member exists in the database with
//that email address, and if so, a pointer to that member’s PersonProfile that is held in your
//MemberDatabase object; if there is no such member, this method returns nullptr.
const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const{
    //TODO: Stub
    return new PersonProfile("", "");
}
