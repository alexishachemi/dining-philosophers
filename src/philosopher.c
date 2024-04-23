#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "philosopher.h"

philosopher_t *ph_create(size_t plates, pthread_mutex_t *f1, pthread_mutex_t *f2)
{
    philosopher_t *ph = NULL;

    ph = malloc(sizeof(philosopher_t));
    if (!ph)
        return NULL;
    ph->f1 = f1;
    ph->f2 = f2;
    ph->plates = plates;
    return ph;
}

static void exit_failure(philosopher_t *ph)
{
    if (ph) {
        printf("\033[0;31mPhilosopher %d has starved...\n\033[0m", ph->id);
        free(ph);
    }
    pthread_exit(NULL);
}

static void exit_success(philosopher_t *ph)
{
    if (ph) {
        printf("\033[0;32mPhilosopher %d finished eating!\n\033[0m", ph->id);
        free(ph);
    }
    pthread_exit(NULL);
}

static bool try_eat(philosopher_t *ph)
{
    if (pthread_mutex_trylock(ph->f1) != 0)
        return false;
    if (pthread_mutex_trylock(ph->f2) != 0) {
        pthread_mutex_unlock(ph->f1);   
        return false;
    }
    printf("\033[0;34mPhilosopher %d is eating...\033[0m\n", ph->id);
    sleep(EATING_TIME_S);
    ph->plates--;
    pthread_mutex_unlock(ph->f1);   
    pthread_mutex_unlock(ph->f2);
    return true;
}

void *ph_add(void *ph_ptr)
{
    philosopher_t *ph = ph_ptr;
    time_t last_eat = time(NULL);
    
    if (!ph)
        exit_failure(NULL);
    while (ph->plates > 0) {
        if (time(NULL) - last_eat >= STARVING_TIME_S)
            exit_failure(ph);
        if (try_eat(ph))
            last_eat = time(NULL);
    }
    exit_success(ph);
    return NULL;
}
