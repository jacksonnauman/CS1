/*
 * Author: Jackson Nauman
 * Course: CS1
 * Assignment: Library System with Linked List
 * Date: 2/15/25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_NAME 50

typedef struct node_t {
    char title[MAX_TITLE];
    char lastName[MAX_NAME];
    char firstName[MAX_NAME];
    struct node_t* next;
    struct node_t* prev;
} node_t;

node_t *borrowBook(node_t *head, char *title, char *lastName, char *firstName);
node_t *returnBook(node_t *head, char *title, char *lastName, char *firstName);
void checkBook(node_t *head, char *title, char *lastName, char *firstName);
void displayBorrowedBooks(node_t *head);
void freeList(node_t *head);

node_t *borrowBook(node_t *head, char *title, char *lastName, char *firstName) {
    // open file, create + allocate node and error check
    FILE* file = fopen("output.txt", "a");
    node_t* borrow = malloc(sizeof(node_t));
    if (borrow == NULL) {
        printf("Malloc failure\n");
        exit(-1);
    }
    // put info in the new node
    strcpy(borrow->firstName, firstName);
    strcpy(borrow->lastName, lastName);
    strcpy(borrow->title, title);
    // handle if list is empty
    if (head == NULL) {
        head = borrow;
        borrow->prev = NULL;
        fprintf(file,"Borrowed \"%s\" by %s, %s\n", title, lastName, firstName);
        fclose(file);
        return borrow;
    }
    // otherwise insert node at head
    head->prev = borrow;
    borrow->next = head;
    borrow->prev = NULL;
    fprintf(file,"Borrowed \"%s\" by %s, %s\n", title, lastName, firstName); // output to file
    fclose(file);
    return borrow;
}

node_t *returnBook(node_t *head, char *title, char *lastName, char *firstName) {
    // open file, create temp node to traverse list, error check
    FILE* file = fopen("output.txt", "a");
    node_t* temp = head;
    if (temp == NULL) {
        fprintf(file,"\"%s\" is not currently borrowed by %s, %s\n", title, lastName, firstName);
        return NULL;
    }
    // set while loop conditions for readability
    int condition1 = strcmp(temp->title, title);
    int condition2 = strcmp(temp->lastName, lastName);
    int condition3 = strcmp(temp->firstName, firstName);
    while (condition1 || condition2 || condition3) {
        temp = temp->next; // traverse linked list to find the correct node
        if (temp == NULL) {
            fprintf(file,"\"%s\" is not currently borrowed by %s, %s\n", title, lastName, firstName);
            return NULL; // if it ever hits this if statement, the book isnt in the list
        }
        // update the strcmps for next loop
        condition1 = strcmp(temp->title, title);
        condition2 = strcmp(temp->lastName, lastName);
        condition3 = strcmp(temp->firstName, firstName);
    }
    node_t* book = temp; // set the correct book bode
    if (book->prev == NULL) {
        head = book->next; // if correct book is the current head, head must be next node
        fprintf(file, "Returned \"%s\" by %s, %s\n", book->title, book->lastName, book->firstName);
        // finish out the function, freeing the node and closing file, returning the head
        free(book);
        fclose(file);
        return head;
    }
    book->prev->next = book->next; // link the books previous node to the books next node, removing it
    fprintf(file, "Returned \"%s\" by %s, %s\n", book->title, book->lastName, book->firstName); // output to file
    // finish out the function, freeing the node and closing file, returning the head
    free(book);
    fclose(file);
    return head;
}

void checkBook(node_t *head, char *title, char *lastName, char *firstName) {
    // open file, create temp node to traverse list, error check
    FILE* file = fopen("output.txt", "a");
    node_t* temp = head;
    if (temp == NULL) {
        fprintf(file,"\"%s\" is not currently borrowed by %s, %s\n", title, lastName, firstName);
        return;
    }
    // set while loop conditions for readability
    int condition1 = strcmp(temp->title, title);
    int condition2 = strcmp(temp->lastName, lastName);
    int condition3 = strcmp(temp->firstName, firstName);
    while (condition1 || condition2 || condition3) {
        temp = temp->next;
        if (temp == NULL) {
            fprintf(file,"\"%s\" is not currently borrowed by %s, %s\n", title, lastName, firstName);
            fclose(file);
            return; // if this if statement happens the book is not in the list
        }
        // update strcmps for next loop
        condition1 = strcmp(temp->title, title);
        condition2 = strcmp(temp->lastName, lastName);
        condition3 = strcmp(temp->firstName, firstName);
    }
    // otherwise, output to file and close file
    fprintf(file, "\"%s\" is currently checked out by %s, %s\n", title, lastName, firstName);
    fclose(file);
}

void displayBorrowedBooks(node_t *head) {
    // open file, create temp node to traverse list, error check
    FILE* file = fopen("output.txt", "a");
    node_t *temp = head;
    if (temp == NULL) {
        fprintf(file,"There are currently no borrowed books\n");
        return;
    }
    int increment = 0; // for numbering in list
    fprintf(file,"Borrowed books:\n");
    // this while loop just prints out each node line by line
    while (temp != NULL) {
        increment++;
        fprintf(file,"%d. \"%s\" - %s, %s\n", increment, temp->title, temp->lastName, temp->firstName);
        temp = temp->next;
    }
    fclose(file); // close file
}

void freeList(node_t *head) {
   // simply traverse list and free node by node
    while (head != NULL) {
        node_t *temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    // initialize all necessary variables
    int operator = 0;
    node_t* head = NULL;
    char firstName[MAX_NAME], lastName[MAX_NAME], title[MAX_TITLE], buffer[100];
    // open the files and error check
    FILE* inputFile = fopen("library_records.txt", "r");
    FILE* outputFile = fopen("output.txt", "a");
    if (inputFile == NULL) {
        printf("File does not exist\n");
        return -1;
    }
    // run loop line by line until input 5 to exit
    while (operator != 5 && fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        // parse buffer for data
        sscanf(buffer, "%d \"%[^\"]\" %s %s", &operator, title, firstName, lastName);
        // switch statement assigns operator to functions
        switch (operator) {
            case 1:
                head = borrowBook(head, title, lastName, firstName);
                break;
            case 2:
                head = returnBook(head, title, lastName, firstName);
                break;
            case 3:
                checkBook(head, title, lastName, firstName);
                break;
            case 4:
                displayBorrowedBooks(head);
                break;
            default:
                fprintf(outputFile, "Thank you for using the Library System!\n");
        }
    }
    // free list, close files, return 0
    freeList(head);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
