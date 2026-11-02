
#include <stdio.h>

#define MAX_FRAMES 3

int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames[MAX_FRAMES] = {-1, -1, -1};
    int pointer = 0, faults = 0, found;

    printf("Page\tFrames\t\tStatus\n");

    for (int i = 0; i < n; i++) {
        found = 0;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % MAX_FRAMES;
            faults++;
        }

        printf("%d\t", pages[i]);

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        printf("\t%s\n", found ? "Hit" : "Fault");
    }

    printf("\nTotal Page Faults: %d\n", faults);

    return 0;
}
