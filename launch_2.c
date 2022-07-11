// COSC4302 Operating Systems
// Group Project
// Januario Fuentes
// Bradley Allen
// Adam Burris

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define WHITESPACE " ,\t\n"
#define BUFFER_SIZE 2000
#define MAX_ARGS 64
#define MAX_ARG_LEN 16

/*
 * Print out the prompt for the user.
 */
void printPrompt()
{
    printf("Simple-Shell$  ");
}

/*
 * Return the path string from the environment.  All paths contained are 
 * separated by the colon character (':').  Commands will be searched for using
 * every path contained within.
 */
char *getPaths()
{
    // Get the PATH variable from the environment.
    char *paths = getenv("PATH");
    // Return a copy so that the original is left intact.
    return strdup(paths);
}

/*
 * Accept user commands within a loop.  Each command is searched for 
 * on the paths contained in the PATH environment variable.  If found, the program
 * is forked so that the command may be run in a child process.  This is done so that,
 * should a fatal error occur, it only crashes the child and not the parent process.
 */
int main(int argc, char **argv)
{
    // The shell will accept commands in a continuous loop.
    while (1)
    {
        // Display the prompt.
        printPrompt();

        // Read the user input from stdin into a buffer.
        char buffer[BUFFER_SIZE] = {};
        fgets(buffer, BUFFER_SIZE, stdin);

        // Retrieve the command, which should be the first token in the buffer.
        char *current_token = strtok(buffer, WHITESPACE);
        char *command = current_token;
        if (command == NULL)
        {
            continue;
        }

        // Create an array to hold the arguments that follow the command.
        char *args[MAX_ARGS];
        // The command itself is the first argument.
        args[0] = command;

        // Use arg_index to keep track of the number of args read.
        size_t arg_index = 0;

        // Read the args into the args array.
        while (current_token != NULL)
        {
            // Continue reading after the command was read and assign each
            // token in the order it appeared.
            current_token = strtok(NULL, WHITESPACE);
            args[++arg_index] = current_token;
        }

        // Get a copy of all paths contained in the PATH environment variable.
        char *paths = getPaths();

        // Use path_found as a boolean to track if the command is found on the
        // system along one of the paths.
        int path_found = 0;

        // Use current_path to test one path at a time.
        char *current_path = strtok(paths, ":");
        // Use executable_path to hold the path concatenated with the command.
        char *executable_path;

        // Test every path in paths until a match is found.
        while (current_path != NULL)
        {
            // Concatenate the current path with the command, for testing.
            executable_path = strdup(current_path);
            strcat(executable_path, "/");
            strcat(executable_path, command);

            // Test the concatenated path to see if it is executable.
            if (access(executable_path, X_OK) == 0)
            {
                // Set path_found to 1 on success.
                path_found = 1;
                // Quit the search.
                break;
            }

            current_path = strtok(NULL, ":");

        }

        // If the command was not found, print a message to the user
        // and go back to the prompt.
        if (path_found == 0)
        {
            printf("Command not found\n");
            continue;
        }

        // Fork so that a child process can run the command.
        pid_t pid = fork();

        if (pid == 0)
        {
            // Execute the command with included arguments.
            execv(executable_path, args);
            // The child process should now exit so that the parent can return
            // to the prompt.
            exit(0);
        }
        else
        {
            // The parent should wait for the child to exit
            // and then continue to the prompt for next iteration of the loop.
            wait(NULL);
        }
    }

    return 0;
}
