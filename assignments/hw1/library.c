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
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].publishDate > arr[j + 1].publishDate) {
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
    getchar();
    Book *books = malloc(sizeof(Book) * bookNum);
    for (int i = 0; i < bookNum; i++) {
        printf("Enter the details for book %d\n", i + 1);
        printf("Title: ");
        fgets(books[i].title, 100, stdin);
        printf("Author: ");
        fgets(books[i].author, 100, stdin);
        printf("Year: ");
        scanf("%d", &books[i].publishDate);
        getchar();
    }
    bubbleSort(books, bookNum);
    printf("Libary Inventory (sorted by year of publication)\n");
    for (int i = 0; i < bookNum; i++) {
        printf("%d. Title: %s", i + 1, books[i].title);
        printf("   Author: %s", books[i].author);
        printf("   Year: %d\n\n", books[i].publishDate);
    }
}
