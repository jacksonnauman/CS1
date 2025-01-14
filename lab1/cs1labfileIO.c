#include <stdio.h>
#include <stdlib.h>

// separate function to add portability
int readAdd(void)
{
    int sum = 0, num = 0;
    FILE* readFile = fopen("sumRead.txt", "r");
    FILE* writeFile = fopen("sumWrite.txt", "w");
    if (readFile == NULL)
    {
        perror("Error opening read file\n");
        exit(-1);
    }
    if (writeFile == NULL)
    {
        perror("Error opening write file\n");
        exit(-1);
    }
    while (fscanf(readFile, "%d", &num) != EOF)
    {
        sum += num;
    }
    fprintf(writeFile, "%d", sum);
    fclose(readFile);
    fclose(writeFile);
    return sum; // we dont use this but also improves portability; good practice
}

int main(void)
{
    readAdd();
    return 0;
}
