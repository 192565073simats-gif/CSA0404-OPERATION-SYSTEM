
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int source, dest;
    char buffer[1024];
    int n;

    source = open("source.txt", O_RDONLY);

    if (source < 0)
    {
        perror("Error opening source file");
        return 1;
    }

    dest = open("destination.txt",
                O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (dest < 0)
    {
        perror("Error opening destination file");
        close(source);
        return 1;
    }

    while ((n = read(source, buffer, sizeof(buffer))) > 0)
    {
        if (write(dest, buffer, n) != n)
        {
            perror("Error writing file");
            close(source);
            close(dest);
            return 1;
        }
    }

    if (n < 0)
        perror("Error reading file");
    else
        printf("File copied successfully!\n");

    close(source);
    close(dest);

    return (n < 0) ? 1 : 0;
}
