# Minishell

Minishell is a simple shell implementation in C that mimics the behavior of a Unix shell. It supports basic shell functionalities such as command execution, environment variable management, and redirections.

```
minishell> echo $ARG

minishell> export ARG="ch" && "e$ARG"o $ARG
ch
minishell> export ARG="ch" && "e$ARG"o $ARG$ARG && ls
chch
Makefile  README.md  build  includes  lib  lib.a  minishell  src  suppressions.supp  test.sh  venv
minishell> export ARG1="nano" && export ARG1="roll" | echo $ARG1
nano
minishell>
```

## Features

- Execute commands with arguments
- Handle environment variables (`export`, `unset`, `env`)
- Built-in commands: `cd`, `echo`, `pwd`, `exit`
- Input/output redirections (`>`, `>>`, `<`, `<<`)
- Pipe support (`|`)
- && and || operators support
- Signal handling (e.g., `Ctrl+C` to interrupt)
- Error handling and reporting

## Getting Started

### Prerequisites

- GCC or Clang compiler
- GNU Make
- Readline library

### Building the Project

To build the project, run the following command:

```sh
make
```
This will compile the source code and create the minishell executable.

### Running the Shell
To start the shell, run the following command:

```sh
./minishell
```
You should see a prompt where you can start typing commands.

### Running Tests
To run the provided tests, execute the following script:
```sh
./test.sh
```
## Usage
Minishell supports the following built-in commands:

- cd [directory]: Change the current directory to the specified directory.
- echo [string ...]: Display the specified string(s) to the standard output.
- pwd: Print the current working directory.
- export [name[=value] ...]: Set environment variables.
- unset [name ...]: Unset environment variables.
- env: Display the current environment variables.
- exit [status]: Exit the shell with the specified status code.
- Additionally, you can use standard Unix commands and features such as:
	-	Input/output redirections (>, >>, <, <<)
	-	&& and || operators
	-	Pipes (|)

## Authors
[Tatyana Klimova] (https://github.com/1LisaW)
[Pasquale Landolfi](https://github.com/plandolf)
