#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
//#include <crtdbg.h>

#include "List.h"
//#include "ListIter.hpp"

#include "TestHjälp.h"
#include <cassert>

#include <iostream>
using std::cout;
using std::endl;

/*	== och !=	*/
void TestEq() {
    Cont cont("raBooF");
    assert((cont.begin() == cont.begin())
        && !(cont.begin() == cont.end()));
    assert(!(cont.begin() != cont.begin())
        && (cont.begin() != cont.end()));
}

void TestPP() {
    Cont cont("FooBar");
    Iter begin = cont.begin();;
    Iter end = cont.end();
    for (auto i = begin; i != end; ++i)
        cout << *i;
    cout << " står det FooBar?" << endl;
    auto it = begin;
    assert(*it == 'F');
    assert(*(it++) == 'F' && *it == 'o');
    *(++it) = 'y';
    assert(*++it == 'B');
    assert(*(++it) == 'a');
}

void TestMM() {
    //revers!
    Cont cont("raBooF");
    Iter begin = cont.end(); --begin;
    Iter end = cont.begin(); --end;
    for (auto i = begin; i != end; --i)
        cout << *i;
    cout << " står det FooBar?" << endl;
    auto it = begin;
    assert(*it == 'F');
    assert(*(it--) == 'F' && *it == 'o');
    *(--it) = 'y';
    assert(*--it == 'B');
    assert(*(--it) == 'a');
}

struct IterTestClass {
    int x = 3;
};

void TestListIter() {
    Cont Hej("Hej"), Tom("");
    //Konstruktorer och tilldelning
    {
        Iter a;
        Iter b(Hej.begin());
        Iter c(b);
        assert(b == c && a != c);
        Iter d;
        d = b;
        assert(b == d && a != d);
    }
    //* och ->
    {
        List<IterTestClass> cont{}; cont.push_back(IterTestClass());
        auto a = cont.begin();
//        assert((*a).x == 3 && a->x == 3);   //Ska vara med!

    }
    //Equality, ++ and --
    TestEq();   // == !=
    TestPP();   // ++ * begin end
    TestMM();   // --

    //-	typdef för iterator
    /*Cont::iterator iter;
    Cont vec("hej");
    iter = vec.begin();*/

}
