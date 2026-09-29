# Shellforge

## A Unix Style Shell Written in C

Shellforge is a custom Unix-style command-line shell developed in the C programming language. The project is designed to understand how a shell works internally, including command-line input, lexical analysis, parsing, variable expansion, built-in commands, command execution, and command history.

Instead of depending completely on the default Linux shell, Shellforge provides its own interactive shell environment with a custom prompt and basic shell functionality.

---

## Project Objective

The main objective of Shellforge is to understand the internal working of a Unix shell and implement its major components using C.

The project focuses on:

- Reading commands from the user
- Breaking commands into tokens
- Parsing commands
- Expanding variables
- Identifying built-in commands
- Executing commands
- Managing command history
- Supporting pipelines
- Creating a custom interactive shell prompt
- Understanding Linux system-level programming concepts

This project provides practical experience with C programming, Linux, processes, command-line interfaces, and shell implementation.

---

## Features

Shellforge contains several components that work together to provide a shell-like environment.

### 1. Interactive Command Line

Shellforge provides an interactive prompt:

```text
shellforge$
