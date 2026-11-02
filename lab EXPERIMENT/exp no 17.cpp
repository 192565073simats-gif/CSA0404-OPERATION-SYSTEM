#include <stdio.h>

#define P 5
#define R 3

int available[R] = {3, 3, 2};

int maximum[P][R] = {
    {7,5,3}, {3,2,2}, {9,0,2},
    {2,2,2}, {4,3,3}
};

int allocation[P][R] = {
    {0,1,0}, {2,0,0}, {3,0,2},
    {2,1,1}, {0,0,2}
};

int safe() {
    int work[R], finish[P] = {0}, count = 0;

    for (int i = 0; i < R; i++)
        work[i] = available[i];

    while (count < P) {
        int found = 0;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int j;

                for (j = 0; j < R; j++)
                    if (maximum[i][j] - allocation[i][j] > work[j])
                        break;

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if (!found)
            return 0;
    }

    return 1;
}

int main() {
    int p, req[R];

    printf("Enter process number (0-4): ");
    scanf("%d", &p);

    if (p < 0 || p >= P) {
        printf("Invalid process number\n");
        return 0;
    }

    printf("Enter resource request: ");
    for (int i = 0; i < R; i++)
        scanf("%d", &req[i]);

    for (int i = 0; i < R; i++) {
        if (req[i] > available[i] ||
            req[i] > maximum[p][i] - allocation[p][i]) {
            printf("Request denied\n");
            return 0;
        }
    }

    for (int i = 0; i < R; i++) {
        available[i] -= req[i];
        allocation[p][i] += req[i];
    }

    if (safe()) {
        printf("Request granted. System is safe.\n");
    } else {
        for (int i = 0; i < R; i++) {
            available[i] += req[i];
            allocation[p][i] -= req[i];
        }
        printf("Request denied. System is unsafe.\n");
    }

    return 0;
}