//
//  MemberDatabase.cpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#include "MemberDatabase.h"
#include <fstream>

//The member database constructor.
MemberDatabase::MemberDatabase(){}

//You may define a destructor for MemberDatabase if you need one to free any dynamically
//allocated memory used by your object.
MemberDatabase::~MemberDatabase(){
    for(int i = 0; i < profiles.size(); i++){
        delete profiles[i];
    }
}

//Person 1’s name
//Person 1’s email address
//Count of number of attribute-value pairs for person 1
//attr1,value1
//attr2,value2
//…
//attrN,valueN


//This method loads the member database from the data file specified by the filename parameter,
//e.g., members.txt. The method must load the data into data structures that enable efficient
//retrieval of email addresses (meeting the big-O requirements at the top of this section). The
//method must return true if the file was successfully loaded and false otherwise. If two members
//in the data file have the same email address, this method returns false.
bool MemberDatabase::LoadDatabase(std::string filename){
    std::ifstream inFile;
    inFile.open(filename);
    
    //check file opened
    if (!inFile)
        return false;

    std::string line;
    
    //determine what way to take input
    bool isName = true;
    bool isEmail = false;
    bool isCountAttValPairs = false;
    bool isAttValPair = false;
    
    //store variables
    int countAttValPairs = 0;
    std::string name = "";
    std::string email = "";
    std::vector<std::string> attValPairsString = {};
    
    while (getline(inFile, line)){
        //extract name information
        if(isName){
            name = line;
            isName = false;
            isEmail = true;
            continue;
        }
        
        //extract email information
        if(isEmail){
            email = line;
            isEmail = false;
            isCountAttValPairs = true;
            continue;
        }
        
        //extract att-val pair count information
        if(isCountAttValPairs){
            countAttValPairs = stoi(line);
            isCountAttValPairs = false;
            isAttValPair = true;
            continue;
        }
        
        //extract att-val pair information
        if(countAttValPairs != 0){
            attValPairsString.push_back(line);
            countAttValPairs--;
            continue;
        }
        
        //extract name information
        if(line == ""){
            PersonProfile* person = new PersonProfile(name, email);
            
            //insert emailToProfiles

            PersonProfile** p = emailToProfile.search(email);
            
            //if this person already exists, delete them and return false
            if(p != nullptr){
                delete person;
                return false;
            }
            
            //otherwise, person doesn't exist already, so insert into RadixTree and push into profiles vector
            emailToProfile.insert(email, *p);
            profiles.push_back(person);
                                
            for(int i = 0; i < attValPairsString.size(); i++){
                std::string aVPair = attValPairsString[i];
                person->AddAttValPair(AttValPair(line.substr(0, aVPair.find(',')), aVPair.substr(line.find(',') + 1)));
                
                //insert aVPairToEmails
                
                std::vector<std::string>* emails = aVPairToEmails.search(aVPair);
                //if there are already emails for this particular att-val pair, add email
                if(emails != nullptr)
                    emails->push_back(email);
                
                //otherwise, there aren't any emails for this particular pair, so add a new vector
                else{
                    std::vector newEmails = {email};
                    *emails = {email};
                }
                
            }
    
            isAttValPair = false;
        }
    }
    inFile.close();
    return true;
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
