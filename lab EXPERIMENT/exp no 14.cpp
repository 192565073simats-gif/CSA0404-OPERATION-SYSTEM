#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SRC "sasi.txt"
#define DEST "sk.txt"

void create()
{
    FILE *fp = fopen(SRC, "w");

    if (fp != NULL) {
        printf("File created successfully\n");
        fclose(fp);
    } else {
        printf("File creation failed\n");
    }
}

void copy()
{
    int s = open(SRC, O_RDONLY);
    int d;
    char buffer[1024];
    int n;

    if (s < 0) {
        printf("Source file not found\n");
        return;
    }

    d = open(DEST, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (d < 0) {
        printf("Destination file creation failed\n");
        close(s);
        return;
    }

    while ((n = read(s, buffer, sizeof(buffer))) > 0) {
        write(d, buffer, n);
    }

    close(s);
    close(d);

    printf("File copied successfully\n");
}

void deleteFile()
{
    if (remove(SRC) == 0)
        printf("File deleted successfully\n");
    else
        printf("File not found\n");
}

int main()
{
    int choice;

    printf("1. Create  2. Copy  3. Delete\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            create();
            break;

        case 2:
            copy();
            break;

        case 3:
            deleteFile();
            break;

        default:
            printf("Invalid choice\n");
    }

    return 0;
}