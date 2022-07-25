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
//define some macros for checking the paths and arguments.
// ############################## DEFINE SECTION ########################################
#define WHITESPACE " ,\t\n"
#define BUFFER_SIZE 2000
#define MAX_ARGS 64
#define MAX_ARG_LEN 16

char *executable_path;
char *args[MAX_ARGS];


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
char *getPath()
{
       char *path = getenv("PATH");
	   //returns the paths of type char.
       		 return strdup(path);
}



//THREAD1
void *thread_1(){
            // Execute the command with included arguments.
            execv(executable_path, args);
            // The child process should now exit so that the parent can return
            // to the prompt.
            exit(0);
}

//main.. this starts the shell. while true get commands and search.. 
//if command is found fork() execute command and return back to main aka parent loop.
int main(int argc, char **argv)
{

	//initialize or show that the shell is running
	init_shell();
	//while true run the shell and wait for commands
    while (1)
    {
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
        char *paths = getPath();

        // 0 or 1 true or false
        int path_found = 0;

        // keep track of each path.
        char *current_path = strtok(paths, ":");
        // executable path
        
			
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

        // create the fork so the command can run.
        //pid_t pid = fork();
		
        //INSTEAD CREATE PTHREAD TO EXECUTE COMMAND

		//if pid ==0
        /*
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
            // parent wait to finish child.
            wait(NULL);
        }
        */
        pthread_t t1;
       pthread_create (&t1, NULL, thread_1,NULL);

       pthread_exit(NULL);
    }

    return 0;
}