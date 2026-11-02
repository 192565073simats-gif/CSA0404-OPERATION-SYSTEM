
#include <stdio.h>
#include <windows.h>
#include <string.h>

int main()
{
    HANDLE hMapFile;
    char *shared_memory;
    char message[] = "Hello from shared memory!";

    // Create shared memory
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        1024,
        "MySharedMemory"
    );

    if (hMapFile == NULL)
    {
        printf("Shared memory creation failed!\n");
        return 1;
    }

    // Map shared memory into process address space
    shared_memory = (char *)MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        1024
    );

    if (shared_memory == NULL)
    {
        printf("Mapping failed!\n");
        CloseHandle(hMapFile);
        return 1;
    }

    // Write data into shared memory
    strcpy(shared_memory, message);

    printf("Data written to shared memory.\n");

    // Read data from shared memory
    printf("Message received: %s\n", shared_memory);

    // Clean up
    UnmapViewOfFile(shared_memory);
    CloseHandle(hMapFile);

    return 0;
}
