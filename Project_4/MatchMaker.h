//
//  MatchMaker.hpp
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#ifndef MatchMaker_h
#define MatchMaker_h

#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

//● MUST run as efficiently as possible - we will not state any exact big-O requirements, but
//try to make your code as efficient as possible - avoid O(N) algorithms where at all
//possible. If you code things correctly, you should be able to find matches in a fraction of
//a second even across hundreds of thousands of member profiles!
//● MUST NOT add any new public member functions or variables
//● MAY use ANY STL containers you like
//● MAY have any private member functions or variables you choose to add
class MatchMaker{
public:
    //This constructs a MatchMaker object with the indicated parameters.
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    
    //You may define a destructor for MemberDatabase if you need one to free any dynamically
    //allocated memory used by your object.
    ~MatchMaker();
    
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
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
    
private:
    MemberDatabase mdb;
    AttributeTranslator at;
    
    static bool compareEmailCounts(EmailCount e1, EmailCount e2);
};

#endif /* MatchMaker_h */
