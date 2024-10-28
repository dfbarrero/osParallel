#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function executed by each thread
void *thread_function(void *arg) {
    // The thread does nothing and just exits
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Verify that the user provided the required argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_threads>\n", argv[0]);
        return 1;
    }

    // Convert the argument to an unsigned long integer
    unsigned long num_threads = strtoul(argv[1], NULL, 10);
    if (num_threads == 0) {
        fprintf(stderr, "Please provide a positive integer for the number of threads.\n");
        return 1;
    }

    // Dynamically allocate memory for the thread identifiers
    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    if (threads == NULL) {
        fprintf(stderr, "Error allocating memory for thread handles.\n");
        return 1;
    }

    // Loop to create the specified number of threads
    for (unsigned long i = 0; i < num_threads; i++) {
        unsigned long result = pthread_create(&threads[i], NULL, thread_function, NULL);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %lu. Reached system limit.\n", i);
            num_threads = i; // Adjust num_threads to actual created threads
            break;
        }
    }

    // Loop to wait for each successfully created thread to finish
    for (unsigned long i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All %lu threads have finished.\n", num_threads);

    // Free allocated memory
    free(threads);
    return 0;
}

