/* Author: Jackson Nauman
 * Course: CS1
 * Assignment: Trie Predict
 * Date: Spring 25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 100

typedef struct TrieNode {
    bool end;
    int frequency;
    int maxFrequency;
    char* mostFrequentWord;
    struct TrieNode* children[ALPHABET_SIZE];
} TrieNode;

// Function to create a new Trie node
TrieNode* createNode(void) {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    // set all values to base starting values
    newNode->end = 0;
    newNode->frequency = 0;
    newNode->maxFrequency = 0;
    newNode->mostFrequentWord = NULL;
    // iterate through and set entire array to NULL
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Function to insert a word into the Trie
void insertWord(TrieNode* root, const char* word, int frequency) {
    TrieNode* current = root; // current to iterate through without touching root
    int length = (int)strlen(word);

    for (int i = 0; i < length; i++) {
        int index = word[i] - 'a'; // ascii value of current letter - ascii value of a = letter of alphabet - 1, as in an array
        // if the next letter you want does not exist, create it
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index]; // set current to the next letter
        // if the frequency of new word is > old maximum frequency, update the most frequent word
        if (frequency > current->maxFrequency) {
            current->maxFrequency = frequency;
            if (current->mostFrequentWord != NULL) {
                free(current->mostFrequentWord); // free the most current word
            }
            current->mostFrequentWord = strdup(word); // update most frequent word to new most frequent word
        }
    }
    current->end = true; // end flag
    current->frequency = frequency; // this field is redundant given what we have
}

// Function to query the most frequent word for a given prefix
char* queryPrefix(TrieNode* root, const char* prefix) {
    TrieNode* current = root; // current to iterate through without touching root
    int length = (int)strlen(prefix);

    for (int i = 0; i < length; i++) {
        int index = prefix[i] - 'a'; // ascii value of current letter - ascii value of a = letter of alphabet - 1, as in an array
        if (current->children[index] == NULL) {
            return "unknown word"; // valid word doesnt exist
        }
        current = current->children[index]; // update current
    }
    // if the given prefix has a most frequent word, return it, else it doesnt exist
    if (current->mostFrequentWord != NULL) {
        return current->mostFrequentWord;
    } else {
        return "unknown word";
    }
}

// function to free the entire trie
void freeTrie(TrieNode* node) {
    // base case
    if (node == NULL) {
        return;
    }
    // iterate through entire alphabet to check for any non null pointers
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            freeTrie(node->children[i]); // if a node exists, recursive call free it
        }
    }
    if (node->mostFrequentWord != NULL) {
        free(node->mostFrequentWord); // any node with a mostFrequentWord must have that freed first
    }
    free(node); // free the node
}

int main(void) {
    TrieNode* root = createNode(); // create root
    int input;
    scanf("%d", &input); // get number of input/output operations to perform

    for (int i = 0; i < input; i++) {
        int command;
        scanf("%d", &command); // command 1 or 2
        if (command == 1) { // insert word logic
            char word[MAX_WORD_LENGTH];
            int frequency;
            scanf("%s %d", word, &frequency); // get word and frequency from user
            insertWord(root, word, frequency); // insert word into trie
        } else if (command == 2) { // predict word logic
            char prefix[MAX_WORD_LENGTH];
            scanf("%s", prefix); // get prefix from user
            printf("%s\n", queryPrefix(root, prefix)); // print the full word found or unknown word
        }
    }
    freeTrie(root);
    return 0;
}
