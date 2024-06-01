# 🐚 Simple-Shell
Simple Shell is a Unix-based shell program created in C. This shell is designed to be run in the Unix terminal, where it starts an infinite loop waiting for user commands. When a command is entered, Simple Shell searches for it, executes it in a child process, and then returns to the parent process to wait for the next command. The shell can be exited by typing `exit`.
<br>
## ✨ Features
- Waits for user commands in an infinite loop.
- Searches for and executes commands.
- Runs commands in a child process.
- Exits cleanly when `exit` is typed.

## ⚙️ Installation

1. **Download** the required `.c` file.
2. **Compile** the `.c` file using a C compiler. For example:
   ```bash
   gcc -o simple_shell simple_shell.c

3. **Run** the compiled program:
  ```bash
./simple_shell
```
4. The shell will begin to run and can be used in the terminal.

## 🛠️ Usage
Start the shell: Once compiled and run, the shell will start and wait for commands.<br>
Execute commands: Enter any valid Unix command.<br>
Exit the shell: Type exit to quit the shell.


## 🖥️ Technologies Used
Simple Shell utilizes the following technologies:
<br>
**Linux/Unix Environment:** The shell is designed to run in Unix-based operating systems, leveraging the underlying system calls and command structure.<br>
**C Programming Language:** The core logic and functionality are implemented in C, providing low-level access to system resources and efficient execution.

## 📊 Project Flow
    A[Start Shell] --> B{Wait for Command}
    B -->|User enters command| C[Search for Command]
    C --> D{Command Found?}
    D -->|Yes| E[Create Child Process]
    E --> F[Execute Command]
    F --> G[Return to Parent Process]
    G --> B
    D -->|No| H[Show Error]
    H --> G
    B -->|User types "exit"| I[Exit Shell]

<br>

## Screenshot:

![shell pic](https://github.com/Sirpip91/simple-shell/blob/main/img/shell1.PNG)
