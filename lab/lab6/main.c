#include <stdlib.h>
#include "dlist.h"

int main() {
    dlist l = createDlist(DLIST_INT);
    dlistValue v;
    v.intValue = 3;
    dlistAppend(l, "c", v);
    v.intValue = 1;
    dlistAppend(l, "a", v);
    v.intValue = 2;
    dlistAppend(l, "b", v);
    dlistPrint(l);
    dlist l2 = createDlist(DLIST_INT);
    dlistSort(l, l2, DLIST_SORT_INC);
    dlistPrint(l2);
    dlistFree(l);
    dlistFree(l2);
    return 0;
}