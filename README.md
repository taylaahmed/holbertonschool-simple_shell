# Shell project

Developed a simple shell using C that can interpret and execute standard commands using environ.

## Description
The simple shell supports both interactive and non-interactive modes, finds executable path through the path environ, forks processes into child and parent, and implements standard built-in commands.

## Features
- Displays a prompt ($) and waits for user input (interactive mode)
- Executes commands with arguments (e.g. ls -l)
- Exectute via explicit paths (/bin/ls)
- Search directories before execution (ls)
- Implements built-in commands (exit: terminates shell, env: print current enviroment variables)
- Can also use non-interactive modes using pipes.
- Ignored standart interrupt signals (ctrl C)

## File structure
Repository: holbertonschool-simple_shell

#### main.h
Header file that contains function prototypes, standard library includes, and external variable

#### simple_shell.c
Receives user input from terminal in 'main'. It reads (read_line) and splits into tokens (split_line). Finally, it determines if input will be sent to execve_wait or get_path. 

#### path_finder.c
Function for locating commants (find_path) and parsing the enviroment (get_path). Prints enviroment (print_environment).

#### execute.c
Function that contains the forking process determining executable for child and parent functions (execve_wait).

#### man_1_simple_shell
Manual page documenting shell's features.

## Installation / Compilation
git clone https://github.com/taylaahmed/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

## Examples
#### Interactive mode
./hsh
($) /bin/ls
AUTHORS    execute.c  main.c  man_1_simple_shell  simple_shell.c
README.md  hsh        main.h  path_finder.c
($) exit

#### Non-interactive mode
echo "/bin/ls" | ./hsh
AUTHORS    execute.c  main.c  man_1_simple_shell  simple_shell.c
README.md  hsh        main.h  path_finder.c

## Authors
Tayla Ahmed
Kalyani Lao-Khiev
