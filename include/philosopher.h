#pragma once

#include "pthread.h"

#define EATING_TIME_S 1
#define STARVING_TIME_S 5

typedef struct {
    size_t nb_forks; // size of the forks array
    size_t plates; // number of plates the philosopher have to eat
    unsigned int id; // id of the philosopher (for indentification only)
    pthread_mutex_t *f1; // first target fork
    pthread_mutex_t *f2; // second target fork
} philosopher_t;

philosopher_t *ph_create(size_t plates, pthread_mutex_t *f1, pthread_mutex_t *f2);
void *ph_add(void *ph);