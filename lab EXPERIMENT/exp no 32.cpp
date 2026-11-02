
#include <stdio.h>

#define MAX_FRAMES 3

int main()
{
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int frames[MAX_FRAMES] = {-1, -1, -1};
    int lastUsed[MAX_FRAMES] = {0, 0, 0};
    int n = sizeof(pages) / sizeof(pages[0]);
    int faults = 0, time = 0, found;

    printf("Page\tFrames\t\tStatus\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        found = 0;
        time++;

        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                lastUsed[j] = time;
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = -1;

            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            if (pos == -1) {
                pos = 0;
                for (int j = 1; j < MAX_FRAMES; j++)
                    if (lastUsed[j] < lastUsed[pos])
                        pos = j;
            }

            frames[pos] = page;
            lastUsed[pos] = time;
            faults++;
        }

        printf("%d\t", page);
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
