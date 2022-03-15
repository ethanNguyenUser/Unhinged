//
//  PersonProfile.h
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#ifndef PersonProfile_h
#define PersonProfile_h

#include "provided.h"
#include <vector>
#include <unordered_set>
#include "RadixTree.h"

//●MUST be able to add and retrieve attribute-value pairs in better than O(N) time where N
//is the number of attribute-value pairs stored in the object. So for example, O(log2 N)
//would be acceptable. For big-O analysis purposes, you may assume that there's a
//constant that all attribute lengths are less than.
//● MUST use your RadixTree class to map attributes to values (for full credit)
//● MUST NOT use the STL map, unordered_map, multimap, or unordered_multimap types
//● MUST NOT add any new public member functions or variables
//● MAY use the STL list and vector classes
//● MAY have any private member functions or variables you choose to add
class PersonProfile{
public:
    //This constructs a PersonProfile object, specifying the member’s name and email address.
    PersonProfile(std::string name, std::string email);
    
    //You may define a destructor for PersonProfile if you need one.
    ~PersonProfile();
    
    //std::string GetName() const
    std::string GetName() const;
    
    //The getName method returns the member’s email address.
    std::string GetEmail() const;
    
    //The AddAttValPair method is used to add a new attribute-value pair to the member’s profile. If
    //the person’s profile already has an attribute-value pair with the same attribute and value as the
    //attval parameter, then this method should do nothing. More than one attribute-value pair in the
    //map can have the same attribute, as long as their corresponding values are different. We place
    //no requirements on the order that you must store your attribute-value pairs.
    void AddAttValPair(const AttValPair& attval);
    
    //This method returns the total number of distinct attribute-value pairs associated with this
    //member
    int GetNumAttValPairs() const;
    
    //This method gets the attribute-value pair specified by attribute_num (where 0 <= attribute_num
    // < GetNumAttValPairs()) and places it in the attval parameter. The method returns true if it
    //successfully retrieves an attribute; otherwise, it returns false and leaves attval unchanged. If you
    //write a loop like this
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string name;
    std::string email;
    RadixTree<std::unordered_set<std::string>> aVPairs;
//    RadixTree<std::vector<std::string>> aVPairs;
    int numAVPairs;
    std::vector<AttValPair> aVPairsVector;
};

#endif /* PersonProfile_h */
