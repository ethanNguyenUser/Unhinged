//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

const std::string MEMBERS_FILE    = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
//    MemberDatabase mdb;
//    if (!mdb.LoadDatabase(MEMBERS_FILE))
//    {
//        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
//        return 1;
//    }
//    AttributeTranslator at;
//    if (!at.Load(TRANSLATOR_FILE))
//    {
//        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
//        return 1;
//    }
//
//    while (findMatches(mdb, at))
//        ;
//
//    std::cout << "Happy dating!" << std::endl;
    
//    RadixTree<int> r;
//    r.insert("hi", 1);
//    r.insert("hi", 2);
//    r.insert("hit", 3);
//    r.insert("hill", 4);
//    r.insert("hilt", 5);
//    r.insert("hills", 6);
//    r.insert("hilts", 7);
//    r.insert("hilts", 8);
//    r.print();
//
//    RadixTree<int> t;
//    t.insert("crown", 1);
//    t.insert("car", -1);
//    t.insert("carbs", -2);
//    t.insert("coin", 2);
//    t.insert("cash", 3);
//    t.insert("coin", 4);
//    t.insert("bash", 5);
//    t.insert("cause", 6);
//    t.insert("cause", 7);
//    t.insert("crab", 8);
//    t.insert("crepe", 8);
//    t.insert("cr", 8);
//    t.print();
    
//    RadixTree<int> s;
//    s.insert("b", 1);
//    s.insert("b", 1);
//    s.insert("a", 2);
//    s.insert("*", 3);
//    s.insert("abacus", 4);
//    s.insert("aba", 5);
//    s.insert("ab", 6);
//    s.insert("aa", 7);
//    s.insert("aP", 8);
//    s.insert("a", 9);
//    s.insert("abort", 10);
//    s.insert("aboriginal", 11);
//
//    s.print();

}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n'); 

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}
