
#include <stdio.h>

#define MAX_MEMORY 1000
int memory[MAX_MEMORY];

void initializeMemory()
{
    for (int i = 0; i < MAX_MEMORY; i++)
        memory[i] = -1;
}

void allocateMemory(int id, int size)
{
    int bestStart = -1, largest = 0, start = 0, count = 0;

    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            if (count == 0)
                start = i;
            count++;
        } else {
            if (count > largest) {
                largest = count;
                bestStart = start;
            }
            count = 0;
        }
    }

    if (count > largest) {
        largest = count;
        bestStart = start;
    }

    if (largest >= size) {
        for (int i = bestStart; i < bestStart + size; i++)
            memory[i] = id;

        printf("Process %d allocated %d units at %d\n",
               id, size, bestStart);
    } else {
        printf("Allocation failed for Process %d\n", id);
    }
}

void deallocateMemory(int id)
{
    for (int i = 0; i < MAX_MEMORY; i++)
        if (memory[i] == id)
            memory[i] = -1;

    printf("Memory released by Process %d\n", id);
}

int main()
{
    initializeMemory();

    allocateMemory(1, 200);
    allocateMemory(2, 300);
    deallocateMemory(1);
    allocateMemory(3, 400);

    return 0;
}
