#include <stdio.h>
#include <string.h>
#include "SimpleHeap.h"

int DataPriorityComp(char *ch1, char *ch2) {
    return strlen(ch2) - strlen(ch1);
}

int main() {
    Heap heap;
    HeapInit(&heap, DataPriorityComp);

    HInsert(&heap, "A");
    HInsert(&heap, "AB");
    HInsert(&heap, "ABC");
    printf("%s \n", HDelete(&heap));

    HInsert(&heap, "A");
    HInsert(&heap, "BB");
    HInsert(&heap, "CCC");
    printf("%s \n", HDelete(&heap));

    while (!HIsEmpty(&heap)) {
        printf("%s \n", HDelete(&heap));
    }

    return 0;
}
