# Minishell

A lightweight Unix shell implemented in C, supporting built-in commands, external command execution, piped pipelines, job control, and signal handling.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Signal Handling](#signal-handling)
- [Job Control](#job-control)
- [Implementation Notes](#implementation-notes)
- [Known Limitations](#known-limitations)

---

## Overview

Minishell is a custom Unix shell written in C from scratch. It mimics core behaviors of `/bin/bash`, including command parsing, process forking, pipe chaining, and interactive job management. The project demonstrates low-level systems programming concepts such as `fork`/`exec`, file descriptor manipulation, signal handling, and process lifecycle management.

---

## Features

- **Interactive prompt** with customizable `PS1`
- **Built-in command execution** (no fork required)
- **External command execution** via `execvp` with `fork`
- **Pipe support** — chain multiple commands with `|`
- **Job control** — suspend (`Ctrl+Z`), resume (`fg`/`bg`), and list (`jobs`) background processes
- **Signal handling** — graceful `SIGINT` (`Ctrl+C`) and `SIGTSTP` (`Ctrl+Z`) behavior
- **Exit status reporting** via `echo $?`
- **Shell PID** via `echo $$`
- **`help` command** listing all built-in and external commands
- **Leading whitespace normalization** in input
- **Automatic pipe alignment** — handles `cmd|cmd` without spaces

---

## Project Structure

```
.
├── main.c                  # Entry point
├── scan_input.c            # Main REPL loop, command dispatch
├── commands.c              # Built-in and external command execution, pipe handling
├── signals.c               # Signal handler (SIGINT, SIGTSTP, SIGCHLD)
├── exception_handling.c    # Input normalization (whitespace, pipe alignment)
├── header.h                # Shared headers, macros, and function declarations
└── external_commands.txt   # Newline-separated list of recognized external commands
```

### Module Responsibilities

| File | Responsibility |
|---|---|
| `main.c` | Initializes the shell, clears screen, starts the input loop |
| `scan_input.c` | REPL loop — reads input, identifies command type, dispatches execution |
| `commands.c` | Implements built-ins, external exec, and multi-process pipe chains |
| `signals.c` | Manages signal events and the stopped-job registry |
| `exception_handling.c` | Strips leading spaces, normalizes pipe spacing |
| `header.h` | Shared types (`Stop`), constants (`BUILTIN`, `EXTERNAL`), ANSI colors |

---

## Getting Started

### Prerequisites

- GCC or any C99-compatible compiler
- Linux (uses `__fpurge` from `<stdio_ext.h>`, which is glibc-specific)

### Build

```bash
gcc main.c scan_input.c commands.c signals.c exception_handling.c -o minishell
```

Or with a Makefile:

```makefile
CC = gcc
SRCS = main.c scan_input.c commands.c signals.c exception_handling.c
TARGET = minishell

all:
	$(CC) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
```

### Run

```bash
./minishell
```

> **Note:** Run the binary directly (`./minishell`), not via `make run`, to avoid `Ctrl+Z` signal issues with the parent make process.

### External Commands

Add any external command names (one per line) to `external_commands.txt` in the working directory before launching the shell. The shell reads this file at startup to recognize external commands.

```
ls
grep
cat
wc
```

---

## Usage

```
Minishell: $
```

### Changing the Prompt

```bash
PS1=myshell:
```

### Running a Pipe

```bash
ls | grep .c | wc -l
```

### Checking Exit Status

```bash
echo $?
```

### Getting Shell PID

```bash
echo $$
```

---

## Built-in Commands

These commands run directly in the shell process without forking:

| Command | Description |
|---|---|
| `echo` | Print text; `echo $$` prints shell PID, `echo $?` prints last exit status, `echo $SHELL` prints shell path |
| `pwd` | Print current working directory |
| `cd <path>` | Change directory |
| `exit` | Exit the shell |
| `jobs` | List stopped/background jobs |
| `fg` | Resume the most recently stopped job in the foreground |
| `bg` | Resume the most recently stopped job in the background |
| `help` | Interactive guide listing all built-in and external commands |
| `export`, `set`, `unset`, `declare`, `readonly` | Environment/variable management (delegated to system) |
| `source`, `eval`, `exec` | Execution control |
| `read`, `printf` | I/O |
| `pushd`, `popd`, `dirs` | Directory stack |
| `let`, `getopts` | Arithmetic and option parsing |
| `shopt`, `bind`, `hash`, `type`, `caller` | Shell configuration |
| `true`, `false` | Boolean no-ops |

---

## Signal Handling

| Signal | Shell Behavior |
|---|---|
| `SIGINT` (`Ctrl+C`) | If no foreground child is running, reprints the prompt. If a child is running, the default handler kills it. |
| `SIGTSTP` (`Ctrl+Z`) | If no foreground child, reprints the prompt. If a child is running, records the job (PID + command name) in the stopped-jobs list. |
| `SIGCHLD` | Automatically cleans up background jobs when they finish (used by `bg`). |

---

## Job Control

Stopped jobs are stored in a fixed-size array (`signal_details[50]`) of `Stop` structs:

```c
typedef struct {
    int spid;       // stopped process PID
    char name[15];  // command name
} Stop;
```

- `jobs` — lists all stopped jobs with index and name
- `fg` — sends `SIGCONT` to the last stopped job and waits for it
- `bg` — sends `SIGCONT` to the last stopped job and registers a `SIGCHLD` handler to auto-reap it

---

## Implementation Notes

- **Pipe execution** forks one child per command segment. Each child sets up `dup2` on the appropriate pipe ends before calling `execvp`. All pipe FDs are closed in both parent and children after setup.
- **Input parsing** uses `scanf("%1023[^\n]", ...)` to read full lines including spaces, then `getchar()` clears the newline from the buffer.
- **`__fpurge(stdin)`** is used after the `help` command's `scanf` to discard leftover input; `fflush` is insufficient here because it only flushes the output buffer.
- **`echo $?`** follows POSIX semantics: `WEXITSTATUS` for normal exits, `128 + WTERMSIG` for signal-killed processes.
- **Pipe alignment** (`pipe_alligner`) ensures `cmd|cmd` is normalized to `cmd | cmd` before tokenization so `strtok` splits correctly on spaces.

---

## Known Limitations

- The stopped-job name buffer is 15 characters — long command names are truncated.
- External commands are limited to 155 entries (hardcoded in `external_commands.txt` parsing).
- `cd` without an argument does not default to `$HOME`.
- Pipe chains are limited to 50 commands.
- No support for I/O redirection (`>`, `<`, `>>`).
- No support for environment variable expansion beyond `$$`, `$?`, and `$SHELL`.
- `bg` uses a LIFO strategy (last stopped job resumed first); a proper job-ID DSA is marked as a TODO in the source.
