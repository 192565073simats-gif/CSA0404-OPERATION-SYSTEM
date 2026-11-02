#include <stdio.h>

void allocate(int mp[], int p[], int n, int m, int ch) {
    int used[20] = {0};

    for (int i = 0; i < m; i++) {
        int pos = -1;

        for (int j = 0; j < n; j++) {
            if (!used[j] && mp[j] >= p[i]) {
                if (pos == -1 ||
                    (ch == 2 && mp[j] < mp[pos]) ||
                    (ch == 3 && mp[j] > mp[pos]))
                    pos = j;

                if (ch == 1) break;
            }
        }

        if (pos != -1) {
            printf("P%d (%d) allocated to block %d (%d)\n",
                   i + 1, p[i], pos + 1, mp[pos]);
            used[pos] = 1;
        } else {
            printf("P%d (%d) not allocated\n", i + 1, p[i]);
        }
    }
}

int main() {
    int mp[20], p[20], n, m, ch;

    printf("Number of memory blocks: ");
    scanf("%d", &n);

    printf("Number of processes: ");
    scanf("%d", &m);

    printf("Enter block sizes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &mp[i]);

    printf("Enter process sizes:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &p[i]);

    printf("1.First Fit  2.Best Fit  3.Worst Fit\n");
    printf("Enter choice: ");
    scanf("%d", &ch);

    if (ch >= 1 && ch <= 3)
        allocate(mp, p, n, m, ch);
    else
        printf("Invalid choice\n");

    return 0;
}