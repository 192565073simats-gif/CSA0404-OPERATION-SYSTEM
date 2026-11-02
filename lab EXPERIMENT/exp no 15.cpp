#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

int main()
{
    char mainDir[] = "OS";
    char fileName[] = "example.txt";
    char filePath[200];

    if (_mkdir(mainDir) == 0)
        printf("Directory created successfully\n");

    snprintf(filePath, sizeof(filePath),
             "%s/%s", mainDir, fileName);

    FILE *file = fopen(filePath, "w");

    if (file == NULL) {
        printf("Error creating file\n");
        return 1;
    }

    fprintf(file, "This is an example file content.");
    fclose(file);

    printf("File created successfully: %s\n", filePath);

    return 0;
}