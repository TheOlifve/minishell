# Minishell

## Description

Minishell is a lightweight implementation of POSIX shell designed to provide a minimalistic command-line interface for interacting with an operating system.

Minishell will support the following features:

1. Display a user-friendly prompt when waiting for a new command, providing an intuitive user experience.
2. Maintain a working command history, allowing users to easily navigate and recall previously executed commands.
3. Search and launch the correct executable based on `PATH` variable or relative/absolute paths, offering a smooth command execution process.
4. Forgo support for unclosed quotes and special characters such as `\` (backlash) and `;` (semicolon), ensuring a cleaner and less error-prone user experience.
5. Support single quotes `'` , preventing the shell from interpreting characters within the quoted sequence, allowing users to work with literal strings.
6. Support double quotes `"` , preventing the shell from interpreting characters within the quoted sequence, except for the `$` (dollar sign) for variable expansion.
7. Provide support for I/O redirections and here documents (`<` , `>` , `>>` , `<<` ), enabling users to redirect input and output between commands and files.
8. Handle environment variables, allowing users to set, modify, and retrieve variables as needed.
9. Manage `ctrl-C` , `ctrl-D` and `ctrl-\` signals, ensuring proper behavior similar to that of `bash`.
10. Support special variables, such as `$?`, for context-based command behavior.
11. Support compound commands with a subshell execution `()` .
12. Support command lists with `&&` (AND_IF) and `||` (OR_IF) operators.
13. Wildcard `*` support for current working directory.
14. Implement built-in commands, including `echo`, `cd`, `pwd`, `export`, `unset`, `env` and `exit`, providing essential shell functionality out-of-the-box.

## Installation

If you don't have `gcc` or GNU `make` do these commands:
```bash
sudo apt update
sudo apt install build-essential
```
To install `readline` use this command:
```bash
tar -xf readline-8.2.tar
make config
```
To install `minishell` just run `make` in the root of the cloned repository.

## Architecture

Minishell's architecture is designed to provide a modular and efficient command-line interface. The project is structured into six distinct modules, each responsible for a specific aspect of Minishell's functionality. These modules work together cohesively to deliver seamless user experience. The following sections outline each module's purpose and functionality.

![Minishells architecture](Assets/Architecture.svg)

### Module Descriptions

- 	`Input` module reads the user input and displays a prompt when waiting for a new command. This module uses the `readline` library, which provides line editing and command history capabilities. Custom signals required for the project are part of this module as well.
-	`Lexical Analysis` module generates a list of tokens from the given input to be later used to break it down into an abstract syntax tree.
-	`Parser` interprets the string of tokens and builds an AST.
-	`Expansion` module is responsible for shell expansions. Our project supports all bash-performed expansions, although on a more limited scale.
-	`Execution` unit executes the commands in the processed AST. This module handles built-ins, process creation, and process management. Additionally, it handles input/output redirection and pipelines, command lists, and subshell execution.
-	`Exit Status` unit collects the exit status after execution, storing it in a special variable `?`. It also cleans up the memory that is no longer in use.
