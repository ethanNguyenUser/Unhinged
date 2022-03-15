//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

const std::string MEMBERS_FILE    = "/Users/ethan/Desktop/Classes/CS_32/Project_4/Project_4/members.txt";
const std::string TRANSLATOR_FILE = "/Users/ethan/Desktop/Classes/CS_32/Project_4/Project_4/translator.txt";

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

//    while (findMatches(mdb, at))
//        ;

    std::cout << "Happy dating!" << std::endl;
    
    ///////////////////////////////////////////////////////////////////////////////
    ///AttributeTranslator Tests
    ///////////////////////////////////////////////////////////////////////////////
    
//    std::vector<AttValPair> v = at.FindCompatibleAttValPairs(AttValPair("job", "chef"));
//    for(int i = 0; i < v.size(); i++){
//        std::cerr << (v[i]).attribute << "," << (v[i]).value << std::endl;
//    }
    
    ///////////////////////////////////////////////////////////////////////////////
    ///RadixTree Tests
    ///////////////////////////////////////////////////////////////////////////////

    RadixTree<int> r;
    r.insert("hi", 1);
    r.insert("hi", 2);
    r.insert("hit", 3);
    r.insert("hill", 4);
    r.insert("hilt", 5);
    r.insert("hills", 6);
    r.insert("hilts", 7);
    r.insert("hilts", 8);
    r.print();
    assert(*(r.search("hi")) == 2);
    assert(*(r.search("hit")) == 3);
    assert(*(r.search("hill")) == 4);
    assert(*(r.search("hilt")) == 5);
    assert(*(r.search("hills")) == 6);
    assert(*(r.search("hilts")) == 8);
    assert(r.search("hello") == nullptr);

    RadixTree<int> t;
    t.insert("crown", 1);
    t.insert("car", -1);
    t.insert("carbs", -2);
    t.insert("coin", 2);
    t.insert("cash", 3);
    t.insert("coin", 4);
    t.insert("bash", 5);
    t.insert("cause", 6);
    t.insert("cause", 7);
    t.insert("crab", 8);
    t.insert("crepe", 8);
    t.insert("cr", 8);
    t.print();

    assert(*(t.search("crown")) == 1);
    assert(*(t.search("car")) == -1);
    assert(*(t.search("carbs")) == -2);
    assert(*(t.search("cash")) == 3);
    assert(*(t.search("coin")) == 4);
    assert(*(t.search("bash")) == 5);
    assert(*(t.search("cause")) == 7);
    assert(*(t.search("crab")) == 8);
    assert(*(t.search("crepe")) == 8);
    assert(*(t.search("cr")) == 8);
    assert(t.search("hello") == nullptr);

    RadixTree<int> s;
    s.insert("b", 0);
    s.insert("b", 1);
    s.insert("a", 2);
    s.insert("*", 3);
    s.insert("abacus", 4);
    s.insert("aba", 5);
    s.insert("ab", 6);
    s.insert("aa", 7);
    s.insert("aP", 8);
    s.insert("a", 9);
    s.insert("abort", 10);
    s.insert("aboriginal", 11);

    s.print();

    assert(*(s.search("b")) == 1);
    assert(*(s.search("*")) == 3);
    assert(*(s.search("abacus")) == 4);
    assert(*(s.search("aba")) == 5);
    assert(*(s.search("ab")) == 6);
    assert(*(s.search("aa")) == 7);
    assert(*(s.search("aP")) == 8);
    assert(*(s.search("a")) == 9);
    assert(*(s.search("abort")) == 10);
    assert(*(s.search("aboriginal")) == 11);
    assert(s.search("hello") == nullptr);

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
