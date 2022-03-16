//
//  MatchMaker.cpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#include "MatchMaker.h"

//This constructs a MatchMaker object with the indicated parameters.
MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at) : mdb(mdb), at(at){}

//You may define a destructor for MemberDatabase if you need one to free any dynamically
//allocated memory used by your object.
MatchMaker::~MatchMaker(){}

//● Taking as input an email address for a member, and a matching threshold (indicating
//how many compatible attribute-value pairs another member must have to be considered
//a good match)
//● Using the provided email address to obtain the member’s attribute-value pairs (e.g.,
//“hobby”,”eating”, etc.)
//● Converting this collection of attribute-value pairs into a collection of unique compatible
//attribute-value pairs that we want to find in other members (e.g., for “hobby”,”eating”
//might translate to “hobby”,”cooking” as well as “occupation”,”chef”)
//● Discovering the collection of members that have each such compatible attribute-value
//pair (Joe and Mary have “hobby”,”cooking”; Mary and Sue have “occupation”,”chef”)
//● Identifying the collection of members that have at least the threshold number of
//compatible attribute-value pairs in common with the member we’re trying to match for
//● Returning a vector of EmailCount objects (a struct we provide in provided.h), each
//holding the email address of a matching member that has at least the threshold number
//of compatible attribute-value pairs, along with the number of such compatible pairs. The
//EmailCount objects in the returned vector are ordered primarily in descending order of
//the number of compatible attribute-value pairs, with ties broken by a secondary ordering
//in ascending alphabetical order by email address (so if two members both have the
//same number of matching attribute-value pairs, then we’d order their email addresses
//alphabetically in the output)
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const{
    //Using the provided email address to obtain the member’s attribute-value pairs (e.g., “hobby”,”eating”, etc.)
    const PersonProfile* person = mdb.GetMemberByEmail(email);
    std::unordered_set<std::string> compAVPairs;
    
    //store all of this person's compatible att-val pairs a hash set
    for(int i = 0; i < person->GetNumAttValPairs(); i++){
        AttValPair temp;
        person->GetAttVal(i, temp);
        std::vector<AttValPair> compAVPairsVector = at.FindCompatibleAttValPairs(temp);
        for(int j = 0; j < compAVPairsVector.size(); j++){
            compAVPairs.insert(compAVPairsVector[j].attribute + "," + compAVPairsVector[j].value);
        }
    }
        
    //find all members who have the matching attributes
    std::unordered_map<std::string, int> emailCounts;
    std::unordered_set<std::string> emails;
    for(std::unordered_set<std::string>::iterator it = compAVPairs.begin(); it != compAVPairs.end(); it++){
        size_t commaIndex = it->find(',');
        std::vector<std::string> emailsVector = mdb.FindMatchingMembers(AttValPair(it->substr(0, commaIndex), it->substr(commaIndex + 1)));
            
        //loop through vector of emails that have this particular compatible att-val pair, converting to unordered_set
        for(int i = 0; i < emailsVector.size(); i++){
            //skip counting self
            if(email == emailsVector[i])
                continue;
            
            //if the email isn't in the map yet, so insert a new map
            if(emails.insert(emailsVector[i]).second){
                emailCounts.insert({emailsVector[i], 1});
            }
            
            //otherwise, the email is already in the map, so increment the count of the map
            else{
                (emailCounts.find(emailsVector[i])->second)++;
            }
        }
    }
        
    std::vector<EmailCount> emailCountsVector;
    
    //convert unordered_map emailCounts into vector of EmailCount's
    for(std::unordered_map<std::string, int>::iterator it = emailCounts.begin(); it != emailCounts.end(); it++){
        if(it->second >= threshold)
            emailCountsVector.push_back(EmailCount(it->first, it->second));
    }
    
    //sort emailCountsVector
    std::sort(emailCountsVector.begin(), emailCountsVector.end(), compareEmailCounts);
    
    return emailCountsVector;
}

bool MatchMaker::compareEmailCounts(EmailCount e1, EmailCount e2){
    if(e1.count == e2.count){
        return e1.email < e2.email;
    }
    return e2.count < e1.count;
}

