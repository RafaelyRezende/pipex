# Pipex - A 42 Network Project

![42 Project](https://img.shields.io/badge/42_Project-Pipex-00babc?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)
![Bonus](https://img.shields.io/badge/Bonus-Complete-brightgreen?style=for-the-badge)

## Project Overview

The Pipex project is an introduction to UNIX mechanisms. The goal is to implement a C program that simulates the behavior of the shell's pipe (`|`) operator. This project explores process creation, file descriptor management, and inter-process communication.

## Implementation Highlights

This implementation focused on robust process and resource management.
* **File Descriptors:** Careful management of file descriptors across multiple forked processes to ensure the correct input and output redirection for each command.
* **Process Synchronization:** Ensuring all file descriptors were properly closed in both parent and child processes was critical to prevent hangs and resource leaks.
* **Memory Management:** Rigorous checking and freeing of all allocated memory to ensure zero memory leaks.
* **Bonus Structure:** A linked list was used in the bonus part to manage an arbitrary number of commands.

## Mandatory Part

The mandatory part requires the program to replicate the behavior of a simple shell command with one pipe.

**Program Execution:**
```

./pipex file1 cmd1 cmd2 file2

````

**Shell Equivalent:**
This command must behave exactly like the following shell command:
```shell
< file1 cmd1 | cmd2 > file2
````

**Examples:**

```shell
# Shell equivalent: < infile ls -l | wc -l > outfile
./pipex infile "ls -l" "wc -l" outfile

# Shell equivalent: < infile grep a1 | wc -w > outfile
./pipex infile "grep a1" "wc -w" outfile
```

## Bonus Part

The bonus part adds support for multiple pipes and `here_doc`.

### Multiple Pipes

This feature allows for an arbitrary number of commands to be piped together. This implementation uses a linked list to manage the command chain.

**Program Execution:**

```
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

**Shell Equivalent:**

```shell
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

### "Here Document" (here\_doc)

This feature implements the `here_doc` (heredoc) redirection, allowing for multi-line string input until a specific `LIMITER` is encountered.

**Program Execution:**

```
./pipex here_doc LIMITER cmd cmd1 file
```

**Shell Equivalent:**

```shell
cmd << LIMITER | cmd1 >> file
```

## Usage & Compilation

### Compilation

The project is compiled using `make`. The `libft` library is a dependency and will be compiled automatically by the main `Makefile`.

  * `all`: Compiles the mandatory part (`pipex`).
  * `bonus`: Compiles the bonus part (`pipex`).
  * `clean`: Removes object files.
  * `fclean`: Removes object files and the final executable.
  * `re`: Runs `fclean` and `all`.

### How to Run

To compile the bonus version and run a simple example:

```bash
make bonus
./pipex infile "ls -l" "wc -l" outfile
```

## Authorized Functions

This project was completed using only the following external functions:

  * `open`
  * `close`
  * `read`
  * `write`
  * `malloc`
  * `free`
  * `perror`
  * `strerror`
  * `access`
  * `dup`
  * `dup2`
  * `execve`
  * `exit`
  * `fork`
  * `pipe`
  * `unlink`
  * `wait`
  * `waitpid`

<!-- end list -->
