//
//  AttributeTranslator.h
//  Project_4
//
//  Created by Ethan Nguyen on 3/7/22.
//

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <vector>
#include <list>
#include "provided.h"
#include "RadixTree.h"

//● MUST be able to retrieve all related attribute-value pairs for a specified source attribute-
//value pair in better than O(N) time where N is the number of source attribute-value pairs
//stored in the object. So for example, O(log2 N) would be acceptable (although you can
//do much better). For big-O analysis purposes, you may assume that there's a constant
//that all attribute lengths are less than. You may also assume that the number of
//compatible pairs any attribute-value pair translates to is bounded by a constant (e.g., <
//10 pairs).
//● MUST use your RadixTree class to map source attribute-value information to compatible
//attribute-values (for full credit)
//● MUST NOT use the STL map, unordered_map, multimap, or unordered_multimap types
//● MUST NOT add any new public member functions or variables
//● MAY use the STL list and vector classes
//● MAY have any private member functions or variables you choose to add
class AttributeTranslator{
public:
    //This is the AttributeTranslator constructor. It must take no arguments.
    AttributeTranslator();
    
    //You may define a destructor for AttributeTranslator if you need one to free any dynamically
    //allocated memory used by your object.
    ~AttributeTranslator();
    
    //This method loads the attribute-value translation data from the data file specified by the
    //filename parameter. The method must load the data into a data structure that enables efficient
    //translation of attribute-value pairs (meeting the big-O requirements at the top of this section).
    //The method must return true if the file was successfully loaded and false otherwise.
    bool Load(std::string filename);
    
    //This method must identify all compatible attribute-value pairs for the specified source attribute-
    //value pair in an efficient manner (meeting the requirements at the top of this section) and return
    //a vector containing them. If there are no compatible pairs, the vector returned must be empty.
    //There is no particular order required for the AttValPairs in the vector returned. The vector
    //returned must not contain two attribute-value pairs with the same attributes and values (i.e., no
    //duplicates).
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<std::vector<std::string>> sourceToComp;
};

#endif /* AttributeTranslator_h */
