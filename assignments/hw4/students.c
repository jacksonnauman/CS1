/*
 * Author: Jackson Nauman
 * Date: 04-2025
 * Assignment: Sort Student List based on Scores
 * Course: COP 3502
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student record with linked list functionality
typedef struct Student {
    char first[30], last[30]; // first and last name of student
    int score; // academic score of the student
    struct Student *next; // pointer to the next student in the linked list
} Student;

// Find the middle node of the linked list to facilitate merge sort
Student* findMiddle(Student* head) {
    if (head == NULL || head->next == NULL) {
        return head; // return head if list is empty or has only one node
    }
    Student* slow = head; // slow pointer moves one step at a time
    Student* fast = head->next; // fast pointer moves two steps at a time
    
    // When fast reaches the end, slow will be at the middle
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; // return the middle node
}

// Merge two sorted linked lists in descending order of scores
Student* merge(Student* left, Student* right) {
    if (left == NULL)
        return right; // if left list is empty, return right list
    if (right == NULL)
        return left; // if right list is empty, return left list
        
    Student* result = NULL;
    // Compare scores and merge in descending order
    if (left->score >= right->score) {
        result = left;
        result->next = merge(left->next, right); // recursively merge the remaining lists
    } else {
        result = right;
        result->next = merge(left, right->next); // recursively merge the remaining lists
    }
    return result;
}

// Implement merge sort algorithm for the linked list
Student* mergeSort(Student* head) {
    if (head == NULL || head->next == NULL) {
        return head; // base case: list is empty or has only one element
    }
    
    Student* middle = findMiddle(head); // find the middle of the list
    Student* right = middle->next; // right half starts after the middle
    middle->next = NULL; // split the list into two halves
    
    Student* left_sorted = mergeSort(head); // recursively sort the left half
    Student* right_sorted = mergeSort(right); // recursively sort the right half
    
    return merge(left_sorted, right_sorted); // merge the sorted halves
}

// Allocate memory for a new student node
Student* createStudent(void) {
    Student* newNode = malloc(sizeof(Student));
    if (newNode == NULL) {
        perror("Memory allocation failed\n");
        exit(1); // exit if memory allocation fails
    }
    return newNode;
}

// Read student data from input file and create linked list
Student* input(FILE* input, Student* head) {
    char buffer[100]; // buffer to store each line from the file
    
    if (head == NULL) {
        head = createStudent(); // create the first student node if list is empty
    }
    
    Student* current = head;
    // Read the first line if available
    if (fgets(buffer, sizeof(buffer), input) != NULL) {
        sscanf(buffer, "%s %s %d", current->last, current->first, &current->score); // parse last name, first name, and score
        
        // Continue reading the rest of the file
        while (fgets(buffer, sizeof(buffer), input) != NULL) {
            current->next = createStudent(); // create a new node for the next student
            current = current->next; // move to the new node
            sscanf(buffer, "%s %s %d", current->last, current->first, &current->score); // parse student data
        }
    }
    return head; // return the head of the linked list
}

// Print all students in the linked list
void printList(Student* head) {
    Student* current = head;
    while (current != NULL) {
        printf("%s %s - %d\n", current->last, current->first, current->score); // print student information
        current = current->next; // move to the next student
    }
}

// Calculate and output statistics for the student records
void output(Student* head) {
    int count = 0, total = 0; // initialize counters for student count and total score
    int high = head->score, low = head->score; // initialize highest and lowest scores
    
    Student* current = head;
    // Traverse the list to calculate statistics
    while (current != NULL) {
        if (current->score > high) high = current->score; // update highest score if needed
        if (current->score < low) low = current->score; // update lowest score if needed
        total += current->score; // accumulate total score
        count++; // increment student counter
        current = current->next; // move to the next student
    }
    float average = (float)total / count; // calculate class average
    
    // Find the median score based on the sorted list
    float median;
    if (count % 2 == 0) { // if even number of students
        int middle = count / 2;
        current = head;
        // Navigate to the node just before the middle
        for (int i = 0; i < middle - 1; i++) {
            current = current->next;
        }
        // Median is the average of the two middle scores
        median = (current->score + current->next->score) / 2.0;
    } else { // if odd number of students
        int middle = count / 2;
        current = head;
        // Navigate to the middle node
        for (int i = 0; i < middle; i++) {
            current = current->next;
        }
        median = current->score; // median is the middle score
    }
    
    // Output all stats after sorting
    printf("Sorted List by Score:\n");
    printList(head); // print the sorted list
    printf("\n");
    printf("Highest Score: %d\n", high);
    printf("Lowest Score: %d\n", low);
    printf("Median Score: %.2f\n", median); // display with 2 decimal places
    printf("Class Average: %.2f\n", average); // display with 2 decimal places
    printf("\n");
    
    // Print top 5 students based on score
    printf("Top 5 Students:\n");
    for (int i = 0; i < 5 && head != NULL; i++) { // print up to 5 students or fewer if list is shorter
        printf("%s %s - %d\n", head->last, head->first, head->score);
        head = head->next; // move to the next student
    }
}

int main(void) {
    // Open the input file
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        perror("Failed to open input file\n");
        return -1;  // exit with error if file can't be opened
    }
    Student* head = NULL; // initialize the head of the linked list
    head = input(inputFile, head); // read student data from file
    head = mergeSort(head); // sort students by score in descending order
    output(head); // calculate and display statistics
    
    return 0; // exit program successfully
}
