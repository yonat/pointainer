#pragma warning (disable : 4786)

//#define NO_MEMBER_TEMPLATES
#define NO_PARTIAL_SPECIALIZATION

#include "pointainer.h"
#include "pointerator.h"

#include <vector>
#include <list>
#include <set>
#include <deque>
#include <iostream>
#include <algorithm>

class VerboseInt
{
public:
    VerboseInt(int i = 0) : n(i) {}
    ~VerboseInt() {std::cout << "Destructing " << n << std::endl;}
    operator int() const {return n;}
private:
    int n;
};

inline void PrintVerboseInt(const VerboseInt* vi)
{std::cout << *vi << " ";}


int main()
{
    {
        std::cout << "vector" << std::endl;
        pointainer< std::vector<VerboseInt*> > v;
        v.push_back(new VerboseInt(256));
        v.push_back(new VerboseInt(17));
        v.push_back(new VerboseInt(42));
        std::cout << "The original vector: ";
        std::for_each(v.begin(), v.end(), PrintVerboseInt);
        std::cout << std::endl;
        std::cout << "Resizing to 1" << std::endl;
        v.resize(1, 0);
        std::cout << "Getting out of scope" << std::endl;
    }
    std::cout << std::endl;

    {
        std::cout << "list" << std::endl;
        pointainer< std::list<VerboseInt*> > l;
        l.push_back(new VerboseInt(256));
        VerboseInt* p17 = new VerboseInt(17);
        l.push_back(p17);
        l.push_back(new VerboseInt(42));
        std::cout << "Removing everything not 17" << std::endl;
        l.remove_if(std::bind2nd(std::not_equal_to<VerboseInt*>(), p17));
        std::cout << "Removing 17" << std::endl;
        l.remove(p17);
        std::cout << "Getting out of scope" << std::endl;
    }
    std::cout << std::endl;

    {
        std::cout << "set" << std::endl;
        pointainer< std::set<VerboseInt*> > s;
        s.insert(new VerboseInt(256));
        VerboseInt* p17 = new VerboseInt(17);
        s.insert(p17);
        s.insert(new VerboseInt(42));
        std::cout << "Erasing s.begin()" << std::endl;
        s.erase(s.begin());
        std::cout << "Erasing 17" << std::endl;
        s.erase(p17);
        std::cout << "Getting out of scope" << std::endl;
    }
    std::cout << std::endl;

    {
        std::cout << "deque" << std::endl;
        std::deque<VerboseInt*> di;
        di.push_back(new VerboseInt(256));
        di.push_back(new VerboseInt(17));
        di.push_back(new VerboseInt(42));
        pointainer< std::deque<VerboseInt*> > d(di);
        std::cout << "Assigning two 0's" << std::endl;
        d.assign(2, 0);
        std::cout << "Getting out of scope" << std::endl;
    }
    std::cout << std::endl;

    {
        std::cout << "pointerator" << std::endl;
        pointainer< std::vector<VerboseInt*> > v;
        v.push_back(new VerboseInt(42));
        typedef pointerator<std::vector<VerboseInt*>::iterator, VerboseInt> Iter;
        Iter i = std::find(Iter(v.begin()), Iter(v.end()), 42);
        std::cout << "The search result is... " << *i << std::endl;
        std::cout << "Getting out of scope" << std::endl;
    }

    return 0;
}