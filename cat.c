#include <stdio.h>
#include <stdlib.h>

int existingFile(char *fileName, char (*fileContent)[256]);
void newFile(char *fileName, char (*fileContent)[256]);
void reader(char *fileName, char (*fileContent)[256], FILE *fileP);
void contentPrint(char (*fileContent)[256], FILE *fileP);
FILE *readFile(char *fName, FILE *fileP);
char *askFileName(char *fileName);

int main()
{
    char existingOrNew;

    char fileName[30];
    char fileContent[256];

    printf("To use exising file type 'e', to create new type 'n': ");
    scanf("%c", &existingOrNew);

    if (existingOrNew == 'n')
        newFile(fileName, &fileContent);
    else if (existingOrNew == 'e')
        existingFile(fileName, &fileContent);
}

FILE *readFile(char *fName, FILE *fileP)
{
    fileP = fopen(fName, "r");
    if (fileP == NULL)
    {
        printf("File \"%s\" doesn't exist\n", fName);
        exit(1);
    }
    return fileP;
}

char *askFileName(char *fileName)
{
    printf("Type the name of your file: "); // Ask file name to create
    scanf("%s", fileName);
    return fileName;
}

void reader(char *fileName, char (*fileContent)[256], FILE *fileP)
{
    getchar();
    printf("Type some text: \n");
    fgets(*fileContent, 256, stdin);

    fprintf(fileP, "%s", *fileContent); // Write text in file
    fclose(fileP);

    readFile(fileName, fileP);
    contentPrint(fileContent, fileP);
}

void contentPrint(char (*fileContent)[256], FILE *fileP)
{
    printf("Content: \n");
    while (fgets(*fileContent, 256, fileP) != NULL)
        printf("%s", *fileContent);

    fclose(fileP);
}

int existingFile(char *fileName, char (*fileContent)[256])
{
    char mode; // Read or append
    FILE *fileP;

    getchar();
    printf("To read type 'r', to append 'a': ");
    scanf("%c", &mode);

    char *fName = askFileName(fileName);

    if (mode == 'r')
    {
        fileP = readFile(fName, fileP);
        contentPrint(fileContent, fileP);
    }
    else if (mode == 'a')
    {
        fileP = fopen(fileName, "a");
        reader(fileName, fileContent, fileP);
    }

    return 0;
}

void newFile(char *fileName, char (*fileContent)[256])
{
    FILE *fileP;

    char *fName = askFileName(fileName);
    fileP = fopen(fileName, "w"); // Create file and open for write
    reader(fileName, fileContent, fileP);
}