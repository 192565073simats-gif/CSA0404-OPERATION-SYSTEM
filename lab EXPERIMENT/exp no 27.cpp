
#include <stdio.h>
#include <windows.h>

int main()
{
    WIN32_FIND_DATAA data;
    HANDLE h = FindFirstFileA("*", &data);

    if (h == INVALID_HANDLE_VALUE) {
        printf("No files found.\n");
        return 1;
    }

    do {
        printf("%s\n", data.cFileName);
    } while (FindNextFileA(h, &data));

    FindClose(h);
    return 0;
}
