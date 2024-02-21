#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Node represents a Node data structure.
 * StrList represents a StrList data structure.
 */
typedef struct _node
{
    char *data;
    struct _node *_next;
} Node;

typedef struct _StrList
{
    Node *_head;
    size_t _size;

} StrList;

/*
 * Allocates a new empty StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_alloc()
{
    // Allocate memory for the StrList structure
    StrList *newList = (StrList *)malloc(sizeof(StrList));
    if (newList == NULL)
    {
        // Handle memory allocation failure
        return NULL;
    }

    // Initialize members
    newList->_head = NULL;
    newList->_size = 0;

    return newList;
}

/*
 * Frees the memory and resources allocated to StrList.
 * If StrList==NULL does nothing (same as free).
 */
void StrList_free(StrList *StrList)
{
    if (StrList == NULL)
        return;
    else
    {
        Node *current = StrList->_head;
        while (current != NULL)
        {
            Node *next = current->_next;
            free(current->data); // Free the memory for the string data
            free(current);       // Free the memory for the node itself
            current = next;
        }
        free(StrList); // Free the memory for the StrList structure
    }
}

/*
 * Returns the number of elements in the StrList.
 */
size_t StrList_size(const StrList *StrList)
{
    return StrList->_size;
}

/*
 * Inserts an element in the end of the StrList.
 */
void StrList_insertLast(StrList *StrList, const char *data)
{
    if (StrList == NULL)
    {
        return;
    }

    // Allocate memory for a new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return;
    }

    // Allocate memory for the string data
    newNode->data = (char *)malloc(strlen(data) + 1); // +1 for the \0
    if (newNode->data == NULL)
    {
        // Handle memory allocation failure
        free(newNode); // Free the previously allocated memory for the node
        return;
    }

    // Copy the string into the allocated memory
    strcpy(newNode->data, data);

    // Set _next pointer to NULL
    newNode->_next = NULL;

    // If the list is empty, set the new node as the head
    if (StrList->_head == NULL)
    {
        StrList->_head = newNode;
    }
    else
    {
        // Traverse to the last node
        Node *current = StrList->_head;
        while (current->_next != NULL)
        {
            current = current->_next;
        }
        // Link the new node to the last node
        current->_next = newNode;
    }

    // Increment the size of the list
    StrList->_size++;
}

/*
 * Inserts an element at given index
 */
void StrList_insertAt(StrList *StrList, const char *data, int index)
{
    if (StrList == NULL)
    {
        return;
    }

    // Allocate memory for a new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return;
    }

    // Allocate memory for the string data
    newNode->data = (char *)malloc(strlen(data) + 1); // +1 for the null terminator
    if (newNode->data == NULL)
    {
        // Handle memory allocation failure
        free(newNode); // Free the previously allocated memory for the node
        return;
    }

    // Copy the string into the allocated memory
    strcpy(newNode->data, data);

    // Check if the index is valid
    if (index < 0 || index > StrList->_size)
    {
        // Handle invalid index
        free(newNode->data);
        free(newNode);
        return;
    }

    // If the index is 0, update the _head pointer of the list
    if (index == 0)
    {
        newNode->_next = StrList->_head;
        StrList->_head = newNode;
    }
    else
    {
        // Traverse to the node at the previous index
        int currentNodeIndex = 0;
        Node *currentNode = StrList->_head;
        while (currentNodeIndex + 1 != index)
        {
            currentNode = currentNode->_next;
            currentNodeIndex++;
        }
        // Insert the new node after the current node
        newNode->_next = currentNode->_next;
        currentNode->_next = newNode;
    }

    // Increment the size of the list
    StrList->_size++;
}

/*
 * TODO what if some node is null???????
 * Returns the StrList first data.
 */
char *StrList_firstData(const StrList *StrList)
{
    if (StrList == NULL || StrList->_head == NULL)
    {
        // if StrList is NULL or empty
        return NULL;
    }
    return StrList->_head->data;
}

/*
 * Prints the StrList to the standard output.
 */
void StrList_print(const StrList *StrList)
{
    if(StrList->_head == NULL){
        return;
    }
    if (StrList == NULL)
    {
        return;
    }
    if (StrList->_size == 0)
    {
        return;
    }
    Node *current = StrList->_head;
    while (current != NULL)
    {
        // Print the string without the trailing space
        printf("%s", current->data);

        // Move to the next node
        current = current->_next;

        // If there's another node, print a space
        if (current != NULL)
        {
            printf(" ");
        }
    }
    printf("\n"); // Print a newline after printing the list
}

/*
* TODO what if some node is null???????
 Prints the word at the given index to the standard output.
*/
void StrList_printAt(const StrList *Strlist, int index)
{
    if (Strlist == NULL)
    {
        return;
    }
    if (index < 0 || index >= Strlist->_size)
    {
        return;
    }

    int currentIndex = 0;
    Node *current = Strlist->_head;
    while (currentIndex != index) // go over the index
    {
        current = current->_next;
        currentIndex++;
    }
    printf("%s\n", current->data); // print the string
}

/*
 * Return the amount of chars in the list.
 */
int StrList_printLen(const StrList *Strlist)
{
    if (Strlist == NULL || Strlist->_head == NULL)
    {
        return 0;
    }

    int len = 0;
    Node *current = Strlist->_head;
    while (current != NULL)
    {
        // Calculate the length of the current string and add it to the total
        len += strlen(current->data);
        current = current->_next;
    }
    return len;
}

/*
Given a string, return the number of times it exists in the list.
*/
int StrList_count(StrList *StrList, const char *data)
{
    if (data == NULL)
    {
        return -1;
    }
    int counter = 0; // a counter
    Node *current = StrList->_head;
    while (current != NULL)
    {
        if (strcmp(current->data, data) == 0) // check if he data is the given string
        {
            counter++;
        }
        current = current->_next;
    }
    return counter; // return the number of the appearence
}

/*
    Given a string and a list, remove all the appearences of this string in the list.
*/
void StrList_remove(StrList *StrList, const char *data)
{
    if (data == NULL)
    {
        return;
    }
    if (StrList == NULL)
    {
        return;
    }
    // go over all the nodes in the list and check if the string is in
    Node *current = StrList->_head;
    Node *currentPrev = StrList->_head;
    while (current->_next != NULL)
    {
        if (current == StrList->_head && strcmp(current->data, data) == 0)
        { // if yes in index 0
            StrList->_head = current->_next;
            free(current->data);
            free(current);
            current = StrList->_head;
            currentPrev = StrList->_head;
            StrList->_size--;
        }
        else // all other index
        {
            current = current->_next;
            if (strcmp(current->data, data) == 0)
            {
                currentPrev->_next = current->_next;
                free(current->data);
                free(current);
                current = currentPrev;
                StrList->_size--;
            }
            else
            {
                currentPrev = current;
            }
        }
    }
}

/*
    Given an index and a list, remove the string at that index.
*/
void StrList_removeAt(StrList *StrList, int index)
{
    if (index < 0 || index > StrList->_size)
    {
        return;
    }
    if (StrList == NULL)
    {
        return;
    }
    // go over the nodes and find the index
    Node *current = StrList->_head;
    Node *currentPrev = StrList->_head;
    for (int i = 0; i < index - 1; i++)
    {
        current = current->_next; // ignore this node
        currentPrev = current;
    }
    current = current->_next;
    currentPrev->_next = current->_next;
    free(current->data); // free the node
    free(current);
    StrList->_size--;
}

/*
 * Checks if two StrLists have the same elements
 * returns 0 if not and any other number (1) if yes
 */
int StrList_isEqual(const StrList *StrList1, const StrList *StrList2)
{
    if (StrList1 == NULL || StrList2 == NULL) // if one of them is null?????????????????????
    {
        return 0;
    }
    if (StrList1->_size != StrList2->_size) // if the size is not the same they are not equals
    {
        return 0;
    }
    Node *current1 = StrList1->_head;
    Node *current2 = StrList2->_head;
    for (int i = 0; i < StrList1->_size; i++)
    {
        if (strcmp(current1->data, current2->data) != 0)
        {
            return 0;
        }
        current1 = current1->_next;
        current2 = current2->_next;
    }
    return 1;
}
/*
 * Clones the given StrList.
 * It's the user responsibility to free it with StrList_free.
 */
StrList *StrList_clone(const StrList *Strlist)
{
    if (Strlist == NULL)
    {
        return NULL;
    }
    StrList *StrListNew = StrList_alloc(); // alloc a new StrList
    Node *current = Strlist->_head;
    for (int i = 0; i < Strlist->_size; i++) // go over all the data and deep copy to the new StrList
    {
        StrList_insertLast(StrListNew, current->data);
        current = current->_next;
    }
    return StrListNew;
}

void StrList_reverse(StrList *StrList)
{
    if (StrList == NULL || StrList->_head == NULL || StrList->_head->_next == NULL)
    {
        return; // If the list is NULL, empty, or has only one node, it's already reversed
    }

    Node *nodeI = StrList->_head;
    Node *nodeJ = StrList->_head;

    // Traverse to the last node
    while (nodeJ->_next != NULL)
    {
        nodeJ = nodeJ->_next;
    }

    // Reverse the list
    while (nodeI != nodeJ && nodeI->_next != nodeJ)
    {
        // Swap the data between nodeI and nodeJ
        char *temp = nodeJ->data;
        nodeJ->data = nodeI->data;
        nodeI->data = temp;

        // Move nodeI to the next node
        nodeI = nodeI->_next;

        // Move nodeJ to the previous node
        Node *prevJ = StrList->_head;
        while (prevJ->_next != nodeJ)
        {
            prevJ = prevJ->_next;
        }
        nodeJ = prevJ;
    }
}
// if (StrList == NULL)
// {
//     return;
// }
// if (StrList->_size == 1)
// {
//     return;
// }
// Node *nodeI = StrList->_head;
// Node *nodeJ = StrList->_head;
// for (int i = 0; i < StrList->_size / 2; i++) //2 pointers- one on the start and one on the end
// {
//     for (int j = i; j < (StrList->_size) - i - 1; j++)
//     {
//         nodeJ = nodeJ->_next;
//     }
//     char *temp = nodeJ->data; //swap the nodes
//     nodeJ->data = nodeI->data;
//     nodeI->data = temp;
//     nodeI = nodeI->_next;
//     nodeJ = nodeI;
// }

/*
 * Sort the given list in lexicographical order
 *using "bubble sort" algorithm
 */
void StrList_sort(StrList *StrList)
{
    if (StrList == NULL)
    {
        return;
    }
    if (StrList->_size == 1)
    {
        return;
    }
    Node *nodeJ = StrList->_head;
    for (int i = 0; i < StrList->_size; i++) // bubble sort
    {
        for (int j = 0; j < (StrList->_size) - i - 1; j++)
        {
            if (strcmp(nodeJ->data, nodeJ->_next->data) > 0) // check equals by ASCII
            {
                char *temp = nodeJ->data; // swap
                nodeJ->data = nodeJ->_next->data;
                nodeJ->_next->data = temp;
            }
            nodeJ = nodeJ->_next;
        }
        nodeJ = StrList->_head;
    }
}

/*
 * Checks if the given list is sorted in lexicographical order
 * returns 1 for sorted,   0 otherwise
 */

int StrList_isSorted(StrList *StrList)
{
    if (StrList == NULL)
    {
        return 1;
    }
    if (StrList->_size == 1)
    {
        return 1;
    }
    Node *nodeJ = StrList->_head;
    for (int j = 0; j < StrList->_size - 1; j++) // go over the Strlist and check if any swap needed
    {
        if (strcmp(nodeJ->data, nodeJ->_next->data) > 0)
        {
            return 0; // if we need to swap- than the list is not sorted
        }
        nodeJ = nodeJ->_next;
    }
    return 1;
} ////////didnt checked
/*
 * this function delete and free all the strlist
 */
void StrList_removeAll(StrList *StrList)
{
    Node *current = StrList->_head;
    Node *next;
    while (current != NULL)
    {
        next = current->_next;
        free(current->data); // Free the data
        free(current);       // Free the node
        current = next;
    }
    StrList->_head = NULL; // Reset the head pointer to NULL
}