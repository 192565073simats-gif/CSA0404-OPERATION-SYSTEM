
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
    int start = -1, count = 0;

    for (int i = 0; i < MAX_MEMORY; i++) {
        if (memory[i] == -1) {
            if (count == 0)
                start = i;
            count++;
        } else {
            count = 0;
        }

        if (count >= size)
            break;
    }

    if (count >= size) {
        for (int i = start; i < start + size; i++)
            memory[i] = id;

        printf("Allocated memory block %d-%d to Process %d\n",
               start, start + size - 1, id);
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
