/*
 Author: Jackson Nauman
 Course: CS1
 Assignment: Library Book Tracker with Sorting
 Date: 1/21/25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char title[100];
    char author[100];
    int publishDate;
} Book;

void bubbleSort(Book* arr, int n) {
    // sort the array in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) { // run through the entire array n times
            if (arr[j].publishDate > arr[j + 1].publishDate) {
                // swap elements if out of order
                Book temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(void) {
    int bookNum = 0;
    printf("Please input the number of books: ");
    scanf("%d", &bookNum);
    getchar(); // consume newline character
    Book *books = malloc(sizeof(Book) * bookNum);
    if (books == NULL) { // error check
        printf("Memory allocation failed\n");
        return -1;
    }
    for (int i = 0; i < bookNum; i++) { // iterate over every book
        printf("Enter the details for book %d\n", i + 1);
        printf("Title: ");
        fgets(books[i].title, 100, stdin);
        // books[i].title[strcspn(books[i].title, "\n")] = '\0';
        printf("Author: ");
        fgets(books[i].author, 100, stdin);
        while (1) {
            printf("Year: ");
            scanf("%d", &books[i].publishDate);
            getchar(); // consume newline character
            if (books[i].publishDate < 0 || books[i].publishDate > 9999) {
                printf("Invalid year, please enter a year from 0-9999\n");
                continue;
            }
            break;
        }
    }
    bubbleSort(books, bookNum);
    printf("Libary Inventory (sorted by year of publication)\n");
    for (int i = 0; i < bookNum; i++) {
        printf("%d. Title: %s", i + 1, books[i].title);
        printf("   Author: %s", books[i].author);
        printf("   Year: %d\n\n", books[i].publishDate);
    }
    free(books);
    return 0;
}
