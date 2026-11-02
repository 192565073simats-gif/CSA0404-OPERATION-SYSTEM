
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    int fd, n;
    char buffer[100];

    fd = creat("sample.txt", S_IRWXU);
    if (fd == -1) {
        perror("create");
        return 1;
    }
    printf("File created successfully.\n");
    close(fd);

    fd = open("sample.txt", O_WRONLY | O_APPEND);
    write(fd, "Hello, World!\n", 14);
    printf("Data written successfully.\n");
    close(fd);

    fd = open("sample.txt", O_RDONLY);
    n = read(fd, buffer, sizeof(buffer));

    printf("Data read from file:\n");
    write(STDOUT_FILENO, buffer, n);
    close(fd);

    remove("sample.txt");
    printf("File deleted successfully.\n");

    return 0;
}
