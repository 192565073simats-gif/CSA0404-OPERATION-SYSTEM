
#include <stdio.h>
#include <windows.h>

int main()
{
    HANDLE hPipe;
    char message[] = "Hello from sender process!";
    char buffer[100];
    DWORD written, readBytes;

    // Create a named pipe as a message channel
    hPipe = CreateNamedPipe(
        "\\\\.\\pipe\\MyMessageQueue",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024,
        1024,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE)
    {
        printf("Message channel creation failed!\n");
        return 1;
    }

    printf("Waiting for client connection...\n");

    // Wait for a client process
    if (!ConnectNamedPipe(hPipe, NULL) &&
        GetLastError() != ERROR_PIPE_CONNECTED)
    {
        printf("Connection failed!\n");
        CloseHandle(hPipe);
        return 1;
    }

    // Receive message from client
    if (ReadFile(hPipe, buffer, sizeof(buffer) - 1,
                 &readBytes, NULL))
    {
        buffer[readBytes] = '\0';
        printf("Message received: %s\n", buffer);
    }

    // Send reply
    if (WriteFile(hPipe, message, sizeof(message),
                  &written, NULL))
    {
        printf("Reply sent: %s\n", message);
    }

    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    return 0;
}
