#include "dllist.h"
#include <cassert>

void testCopyConstructor() {
    DLList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    DLList<int> copy(list);
    assert(copy.size() == 3);
    DLList<int>::iterator copyIt = copy.begin();
    assert(copyIt != list.begin());
    assert(*copyIt == 1);
    ++copyIt;
    assert(*copyIt == 2);
    ++copyIt;
    assert(*copyIt == 3);
    ++copyIt;
    assert(copyIt == copy.end());
}

int main() {
    testCopyConstructor();
}