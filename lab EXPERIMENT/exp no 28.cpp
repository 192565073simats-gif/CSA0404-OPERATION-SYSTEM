
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main()
{
    char filename[100], pattern[100];
    char line[MAX_LINE_LENGTH];
    FILE *file;

    printf("Enter file name: ");
    scanf("%99s", filename);

    printf("Enter pattern: ");
    scanf("%99s", pattern);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, pattern) != NULL)
            printf("%s", line);
    }

    fclose(file);
    return 0;
}
