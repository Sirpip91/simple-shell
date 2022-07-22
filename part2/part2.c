//COSC4302 Operating Systems
// Group Project
// Januario Fuentes
// Bradley Allen
// Adam Burris

//includes for .c
// ############################## INCLUDE SECTION ######################################
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
//define some macros for checking the paths and arguments.
// ############################## DEFINE SECTION ########################################
#define WHITESPACE " ,\t\n"
#define BUFFER_SIZE 2000
#define MAX_ARGS 64
#define MAX_ARG_LEN 16

static sem_t semaphore;

void *thread_1();
void *thread_2();
void init_shell();
void printPrompt();
char *getPaths();
{
	while(1)
	{
		sem_wait(&semaphore); // p()
		
        // Output the prompt that is shown to enter commands 
        printPrompt();

        // read input and send it to the buffer.
        char buffer[BUFFER_SIZE] = {};
        fgets(buffer, BUFFER_SIZE, stdin);

 		//get the command.
        char *current_token = strtok(buffer, WHITESPACE);
		//save command to token.
        char *command = current_token;
		//if command is NULL continue waiting.
        if (command == NULL)
        {
            continue;
        }

        // array of command args.
        char *args[MAX_ARGS];
        // set first space to the command.
        args[0] = command;

        // go through the array and keep track with arg_index.
        size_t arg_index = 0;

        // While not at the end of tokens
        while (current_token != NULL)
        {
			//keep reading 
            current_token = strtok(NULL, WHITESPACE);
			//increment.
            args[++arg_index] = current_token;
        }

        // pointer paths getPaths.
        char *paths = getPaths();

        // 0 or 1 true or false
        int path_found = 0;

        // keep track of each path.
        char *current_path = strtok(paths, ":");
        // executable path
        char *executable_path;
			
			//while there are paths to search
          while (current_path != NULL)
        {
           // keep adding and going through paths.
            executable_path = strdup(current_path);
			// slash for paths.
            strcat(executable_path, "/");
            strcat(executable_path, command);

            // if the path exe is good ==0
            if (access(executable_path, X_OK) == 0)
            {
                // Set path_found will equal 1 which means found.
                path_found = 1;
                // break get out of loop
                break;
            }
			
			//reset the current_path to null.
            current_path = strtok(NULL, ":");

        }

        	//if path could not be found then return 
        if (path_found == 0)
        {	
			//command could not be found.
            printf("Command not found\n");
            continue;
        }
		exit(0);
		
	}
	sem_post(&semaphore);	//V()
}

void *thread_2()
{
	while(1)
	{
			sem_wait(&semaphore); // P()
		
		   execv(executable_path, args);
          
		   sem_post(&semaphore);		//V()
        
	}
}



//initialize with loaded screen to show user that the shell has been loaded.
void init_shell() {
    printf("******************************************************************************\n");
    printf("  #####                                    #####                              \n");
    printf(" #     # # #    # #####  #      ######    #     # #    # ###### #      #      \n");
    printf(" #       # ##  ## #    # #      #         #       #    # #      #      #      \n");
    printf("  #####  # # ## # #    # #      #####      #####  ###### #####  #      #      \n");
    printf("       # # #    # #####  #      #               # #    # #      #      #      \n");
    printf(" #     # # #    # #      #      #         #     # #    # #      #      #      \n");
    printf("  #####  # #    # #      ###### ######     #####  #    # ###### ###### ###### \n");
    printf("******************************************************************************\n");
    printf("\n");
	printf("Developers: Bradley Allen, Januario Fuentes, Adam Burris\n\n");

}


//This is the prompt that will act as a txt/cmd line.
void printPrompt()
{
    printf("Simple-Shell$  ");
}
	//getter function for the paths of current dir
char *getPaths()
{
       char *paths = getenv("PATH");
	   //returns the paths of type char.
       		 return strdup(paths);
}

//main.. this starts the shell. while true get commands and search.. 
//if command is found fork() execute command and return back to main aka parent loop.
int main(int argc, char **argv)
{

	//initialize or show that the shell is running
	init_shell();
	//while true run the shell and wait for commands
   
    return 0;
}