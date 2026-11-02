
#include <stdio.h>

int main()
{
    int n, i, tq, time = 0;
    int bt[20], rem_bt[20], wt[20], tat[20];
    int completed;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    if (n <= 0 || n > 20 || tq <= 0)
    {
        printf("Invalid input!\n");
        return 1;
    }

    for (i = 0; i < n; i++)
        wt[i] = 0;

    do
    {
        completed = 1;

        for (i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                completed = 0;

                if (rem_bt[i] > tq)
                {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else
                {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
    } while (!completed);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];

        printf("P%d\t%d\t\t%d\t\t%d\n",
               i + 1, bt[i], wt[i], tat[i]);
    }

    return 0;
}
