#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining struct for linked list
struct Linked_List
{
    char Refernce_String[10];
    struct Linked_List *next;
};

typedef struct Linked_List node;
node *Head = NULL;
node *Tail = NULL;

void FIFO_algorithm(int file_number, int frame_size)
{

    char reference_string[10], operator;
    FILE *fp;
    if (file_number == 1)
    {
        char *fileName = "bzip.txt";
        fp = fopen(fileName, "r");
    }
    else if (file_number == 2)
    {
        char *fileName = "gcc.txt";
        fp = fopen(fileName, "r");
    }
    else
    {
        char *fileName = "test.txt";
        fp = fopen(fileName, "r");
    }

    if (fp == NULL)
    {
        printf("File does not exist \n");
        exit(0);
    }

    int frame_count = 0, page_miss = 0, page_hit = 0, read_count = 0, write_count = 0;
    while (fscanf(fp, "%s %c\n", reference_string, &operator) != EOF)
    {
        if (frame_count < frame_size)
        {
            if (search_Item(reference_string) == 0) // Check if page is present in Frame queque
            {
                insert_Operation(reference_string);
                frame_count++; // Update frame index as page has been added
                page_miss++;
                if (operator== 'R')
                {
                    read_count++;
                }
                else
                {
                    write_count++;
                }
            }
            else
            {
                page_hit++;
            }
        }
        else
        {
            if (search_Item(reference_string) == 0) // Check if page is present in Frame queue
            {
                delete_Node();
                insert_Operation(reference_string);
                page_miss++;
                if (operator== 'R')
                {
                    read_count++;
                }
                else
                {
                    write_count++;
                }
            }
            else
            {
                page_hit++;
            }
        }
    }
    print_List();
    printf("\nNumber of Reads: %d\nNumber of Writes: %d\n", read_count, write_count);
    fclose(fp);
}

void LRU_algorithm(int file_number, int frame_size)
{
    char reference_string[10], operator;
    FILE *fp;
    if (file_number == 1)
    {
        char *fileName = "bzip.txt";
        fp = fopen(fileName, "r");
    }
    else if (file_number == 2)
    {
        char *fileName = "gcc.txt";
        fp = fopen(fileName, "r");
    }
    else
    {
        char *fileName = "test.txt";
        fp = fopen(fileName, "r");
    }

    if (fp == NULL)
    {
        printf("File does not exist \n");
        exit(0);
    }

    int frame_count = 0, page_miss = 0, page_hit = 0, read_count = 0, write_count = 0;
    while (fscanf(fp, "%s %c\n", reference_string, &operator) != EOF)
    {
        int position;
        if (frame_count < frame_size)
        {
            position = search_Item_LRU(reference_string);
            if (position == -1) // Check if page is present in Frame queque
            {
                insert_Operation(reference_string);
                frame_count++; // Update frame index as page has been added
                page_miss++;
                if (operator== 'R')
                {
                    read_count++;
                }
                else
                {
                    write_count++;
                }
            }
            else
            {
                page_hit++;
                delete_Node_LRU(position);
            }
        }
        else
        {
            position = search_Item_LRU(reference_string);
            if (position == -1) // Check if page is present in Frame queue
            {
                delete_Node();
                insert_Operation(reference_string);
                page_miss++;
                if (operator== 'R')
                {
                    read_count++;
                }
                else
                {
                    write_count++;
                }
            }
            else
            {
                page_hit++;
                delete_Node_LRU(position);
            }
        }
    }
    print_List();
    printf("\nNumber of Reads: %d\nNumber of Writes: %d\n", read_count, write_count);
    // Closing the file
    fclose(fp);
}

void insert_Operation(char *value)
{
    node *temp_node;
    temp_node = (node *)malloc(sizeof(node));

    strcpy(temp_node->Refernce_String, value);
    temp_node->next = NULL;

    // For the 1st element
    if (Head == NULL)
    {
        Head = temp_node;
        Tail = temp_node;
    }
    else
    {
        Tail->next = temp_node;
        Tail = temp_node;
    }
}

void delete_Node_LRU(int pos)
{
    node *temp = Head; // Creating a temporary variable pointing to Head
    int i;
    if (pos == 0)
    {
        Head = Head->next; // Advancing the Head pointer
        temp->next = NULL;
        insert_Operation(temp->Refernce_String);
    }
    else
    {
        for (i = 0; i < pos - 1; i++)
        {
            temp = temp->next;
        }
        node *del = temp->next; // del pointer points to the node to be deleted
        temp->next = temp->next->next;
        insert_Operation(del->Refernce_String);
        del->next = NULL;
    }
    return;
}

void delete_Node()
{
    node *toDelete;
    if (Head == NULL)
    {
        printf("List is already empty.");
    }
    else
    {
        toDelete = Head;
        Head = Head->next;
    }
}

int search_Item(char *value)
{
    node *searchNode = Head;
    int flag = 0;
    while (searchNode != NULL)
    {
        if (strcmp(searchNode->Refernce_String, value) == 0)
        {
            flag = 1;
            break;
        }
        else
            searchNode = searchNode->next;
    }
    if (flag == 0)
    {
    }
    return flag;
}

int search_Item_LRU(char *value)
{
    node *searchNode = Head;
    int position = -1;
    int count = -1;

    while (searchNode != NULL)
    {
        count++;
        if (strcmp(searchNode->Refernce_String, value) == 0)
        {
            position = count;
            break;
        }
        else
            searchNode = searchNode->next;
    }

    return position;
}

void print_List()
{
    printf("\nContents of Page Frame are\n");
    node *myLinkList;
    myLinkList = Head;
    while (myLinkList != NULL)
    {
        printf("%s ", myLinkList->Refernce_String);
        myLinkList = myLinkList->next;
    }
    puts("");
}

// Main fuction
int main()
{
    int frames, file_name_value, algorithm_type_value;
    int file_name = 0;
    int algorithm_type = 0;

    printf("\nPlease Select one of the file you want to perform the Page replacement algorithm on :");
    printf("\n1. bzip.txt");
    printf("\n2. gcc.txt");
    printf("\n3. test.txt");
    printf("\nEnter your choice:\t");
    scanf("%d", &file_name);
    switch (file_name)
    {
    case 1:
        printf("\nYou selected bzip.txt");
        file_name_value = 1;
        break;
    case 2:
        printf("\nYou selected gcc.txt");
        file_name_value = 2;
        break;
    case 3:
        printf("\nYou selected test.txt");
        file_name_value = 3;
        break;
    default:
        printf("\nPlease Select correct option ");
    }

    printf("\nPlease Select the algorithm you want to perform on the file : ");
    printf("\n1. FIFO");
    printf("\n2. LRU");
    printf("\nEnter your choice:\t");
    scanf("%d", &algorithm_type);
    switch (algorithm_type)
    {
    case 1:
        printf("\nYou selected FIFO");
        algorithm_type_value = 1;
        break;
    case 2:
        printf("\nYou selected LRU");
        algorithm_type_value = 2;
        break;
    default:
        printf("\nPlease Select correct option ");
    }

    printf("\nWhat are the total number of frames:\t");
    scanf("%d", &frames);

    if (algorithm_type_value == 1)
    {
        FIFO_algorithm(file_name_value, frames);
    }
    else
    {
        LRU_algorithm(file_name_value, frames);
    }
    return 0;
}

// <------------------ FIFO Algorithms ------------------>



// <------------------ LRU ------------------>


// <------------------ Linked List Functions ------------------>

