#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philosopher.h"

static const char *help_msg = \
"USAGE: ./dining-philosophers MEMBERS PLATES\n" 
"\tMEMBERS\tNumbers of philosophers (and forks)\n"
"\tPLATES\tNumbers of plates per philosopher";

int init_dining_table(unsigned int nb_ph, unsigned int nb_plates)
{
    pthread_t threads[nb_ph];
    pthread_mutex_t forks[nb_ph];
    philosopher_t *ph = NULL;

    for (size_t i = 0; i < nb_ph; i++) {
        if (pthread_mutex_init(&forks[i], NULL) == -1) {
            fprintf(stderr, "Failed to init mutex.\n");
            return EXIT_FAILURE;
        }
    }
    for (size_t i = 0; i < nb_ph; i++) {
        ph = ph_create(nb_plates, &forks[i % nb_ph], &forks[(i + 1) % nb_ph]);
        pthread_create(&threads[i], NULL, ph_add, ph);
    }
    for (size_t i = 0; i < nb_ph; i++)
        pthread_join(threads[i], NULL);
    for (size_t i = 0; i < nb_ph; i++)
        pthread_mutex_destroy(&forks[i]);
    return EXIT_SUCCESS;
}

void print_help(void)
{
    puts(help_msg);
}

int main(int argc, const char **argv)
{
    int nb_ph = 0;
    int nb_plates = 0;

    if (argc != 3) {
        print_help();
        return 0;
    }
    if ((nb_ph = atoi(argv[1])) <= 1 || (nb_plates = atoi(argv[2])) <= 0) {
        fprintf(stderr, "Invalid arguments.\n");
        return EXIT_FAILURE;
    }
    return init_dining_table(nb_ph, nb_plates);
}
