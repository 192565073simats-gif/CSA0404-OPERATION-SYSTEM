
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <windows.h>

int main()
{
    int fd;
    char buffer[100];
    struct _stat info;
    long pos;
    intptr_t handle;
    struct _finddata_t file;

    fd = _open("foo.txt", _O_RDWR | _O_CREAT, _S_IREAD | _S_IWRITE);

    if (fd == -1) {
        perror("File open");
        return 1;
    }

    printf("File opened successfully. FD = %d\n", fd);

    _write(fd, "Hello World!\n", 13);

    pos = _lseek(fd, 0, SEEK_SET);
    printf("File position: %ld\n", pos);

    _read(fd, buffer, 13);
    buffer[13] = '\0';
    printf("File data: %s", buffer);

    if (_fstat(fd, &info) == 0)
        printf("File size: %ld bytes\n", (long)info.st_size);

    _close(fd);

    handle = _findfirst("*", &file);
    if (handle != -1) {
        printf("\nDirectory files:\n");
        do {
            printf("%s\n", file.name);
        } while (_findnext(handle, &file) == 0);

        _findclose(handle);
    }

    return 0;
}
