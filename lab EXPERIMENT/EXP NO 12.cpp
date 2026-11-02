#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t chop[N];

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        pthread_mutex_lock(&chop[left]);
        pthread_mutex_lock(&chop[right]);

        printf("Philosopher %d is eating\n", id);
        sleep(1);

        pthread_mutex_unlock(&chop[left]);
        pthread_mutex_unlock(&chop[right]);
    }
    return NULL;
}

int main() {
    pthread_t t[N];
    int id[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&chop[i], NULL);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&t[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(t[i], NULL);

    return 0;
}