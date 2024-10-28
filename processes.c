#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Check if the user provided the required argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
        return 1;
    }

    // Convert the argument to an integer
    int num_processes = atoi(argv[1]);
    if (num_processes <= 0) {
        fprintf(stderr, "Please provide a positive integer for the number of processes.\n");
        return 1;
    }

    // Loop to create the specified number of child processes
    for (int i = 0; i < num_processes; i++) {
        pid_t pid = fork();
        
        if (pid < 0) { // Error handling for fork failure
            perror("fork");
            return 1;
        } else if (pid == 0) { // In the child process
            // Child does nothing and exits
            _exit(0);
        }
    }

    // Parent process waits for all child processes to finish
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    printf("All %d processes have finished.\n", num_processes);
    return 0;
}

