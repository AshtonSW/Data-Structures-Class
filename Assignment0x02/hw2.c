#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Node Structure
typedef struct Node {
    struct Node* prev;
    struct Node* next;
    int data;
} Node;

typedef Node* listPointer;

void insert(listPointer* listHead, int ins_data);
void delete(listPointer* listHead, int del_data);
void print_reverse(listPointer list);
void print_forward(listPointer list);

// main function
int main(int argc, char* argv[]) {
    listPointer listHead = NULL;
    char command[8];
    int data;
    
    // Check the number of command line arguments.
    if (argc != 2) {
        printf("Usage: ./hw2 input_filename\n");
        return 1;
    }
    
    // open the input file.
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("The input file does not exist.\n");
        return 1;
    }
    
    // Read commands 
    while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "INSERT") == 0) {
            fscanf(file, "%d", &data);
            insert(&listHead, data);
        }
        else if (strcmp(command, "DELETE") == 0) {
            fscanf(file, "%d", &data);
            delete(&listHead, data);
        }
        else if (strcmp(command, "ASCEND") == 0) {
            print_forward(listHead);
        }
        else if (strcmp(command, "DESCEND") == 0) {
            print_reverse(listHead);
        }
    }

    fclose(file);

    return 0;
}


// print_reverse function(Don't change!!)
void print_reverse(listPointer list) {
    listPointer curr;
    FILE* outfile;
    outfile = fopen("hw2_result.txt", "a");
    if (list) {
        curr = list->prev;
        while (curr != list) {
            fprintf(outfile, "%d ", curr->data);
            printf("%d ", curr->data);
            curr = curr->prev;
        }
        fprintf(outfile, "%d ", curr->data);
        printf("%d ", curr->data);
    }
    fprintf(outfile, "\n");
    printf("\n");
    fclose(outfile);
}

// print_forward function(Don't change!!)
void print_forward(listPointer list) {
    listPointer curr;
    FILE* outfile;
    outfile = fopen("hw2_result.txt", "a");
    if (list) {
        curr = list;
        while (1) {
            fprintf(outfile, "%d ", curr->data);
            printf("%d ", curr->data);
            curr = curr->next;
            if (curr == list) break;
        }
    }
    fprintf(outfile, "\n");
    printf("\n");
    fclose(outfile);
}

// insert function
void insert(listPointer* listHead, int ins_data) {
    // newNode
    listPointer insNode = (listPointer)malloc(sizeof(Node)); // insnode is the New node that insert to the list
    insNode->data = ins_data;

    // the list is empty
    if (*listHead == NULL) {
        insNode->next = insNode;
        insNode->prev = insNode;
        *listHead = insNode;
    }
    else if (ins_data < (*listHead)->data) {  // Insert at the beginning(listHead).
        insNode->next = *listHead;
        insNode->prev = (*listHead)->prev;
        (*listHead)->prev->next = insNode;
        (*listHead)->prev = insNode;
        *listHead = insNode;
    }
    else {  // insert the insnode in the sorted list.
        listPointer cur = *listHead;
        while (cur->next != *listHead && cur->next->data < ins_data) {
            cur = cur->next;
        }
        // If the data already exists, don't insert it.
        if (cur->next->data == ins_data) {
            free(insNode);
            return;
        }
        // Insert the insnode.
        insNode->next = cur->next;
        insNode->prev = cur;
        cur->next->prev = insNode;
        cur->next = insNode;
    }
}

// Deletion function
void delete(listPointer* listHead, int del_data) {
    // If the list is empty, then return
    if (*listHead == NULL) {
        return;
    }

    // Start from the listHead
    listPointer cur = *listHead;

    // If the head node is to be deleted
    if (cur->data == del_data) {
        if (cur->next == cur) {  // If the current node is the only node.
            *listHead = NULL;
        }
        else {
            *listHead = cur->next;
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
        }
        free(cur);
        return;
    }

    // Check the rest of the list
    cur = cur->next;
    while (cur != *listHead) {
        if (cur->data == del_data) {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            free(cur);
            return;
        }
        cur = cur->next;
    }
}
