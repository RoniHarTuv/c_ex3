#include "StrList.h"
#include "StrList.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
 * this class represent a menu that the user can choose between options, and make some actions on a StrList
 */
int main()
{
    int s;
    scanf("%d", &s);
    StrList *mylist = StrList_alloc();
    while (s != 0)
    {
        if (s == 1)
        {
            int j;
            scanf("%d", &j);
            for (int i = 0; i < j; i++)
            {
                char string[128];
                scanf("%s", string);
                StrList_insertLast(mylist, string);
            }
        }
        if (s == 2)
        {
            int index;
            scanf("%d", &index);
            char string[128];
            scanf("%s", string);
            StrList_insertAt(mylist, string, index);
        }
        if (s == 3)
        {
            StrList_print(mylist); //prints error if delete the list and than try to print
        }
        if (s == 4)//prints list size
        {
            printf("%zu\n", mylist->_size);
        }
        if (s == 5)//prints string at index
        {
            int index;
            scanf("%d", &index);
            StrList_printAt(mylist, index);
        }
        if (s == 6)//prints numbers of chars in all list
        {
            printf("%d\n", StrList_printLen(mylist));
        }
        if (s == 7)
        {
            char string[128];
            scanf("%s", string);
            printf("%d\n", StrList_count(mylist, string));
        }
        if (s == 8)
        {
            char string[128];
            scanf("%s", string);
            StrList_remove(mylist, string);
        }
        if (s == 9)
        {
            int index;
            scanf("%d", &index);
            StrList_removeAt(mylist, index);
        }
        if (s == 10) //reverse the list
        {
            StrList_reverse(mylist);
        }
        if (s == 11) ////////need to check
        {
            StrList_removeAll(mylist);
        }
        if (s == 12)
        {
            StrList_sort(mylist);
        }
        if (s == 13) // returns 1 for sorted = "true",0 otherwise= "false"
        {
            int a = StrList_isSorted(mylist);
            if (a == 1)
            {
                printf("true\n");
            }
            if (a == 0)
            {
                printf("false\n");
            }
        }
        if (s == 0)
        {
            StrList_removeAll(mylist);
            printf("\n");
            return 0;
        }
        scanf("%d", &s);
    }
    return 0;
}
