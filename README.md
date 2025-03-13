<p align='center'>
   <a href="https://www.linux.org/">
      <img src="https://img.shields.io/badge/OS-Linux-blue?logo=linux&logoColor=white"
            alt="OS - Linux"></a>
   <a href="https://wakatime.com/badge/user/7d36b55a-b5ff-46c4-b7fd-57604568d382/project/7646dba2-55e4-45a5-87c0-3e0fecfb92a5">
      <img src="https://wakatime.com/badge/user/7d36b55a-b5ff-46c4-b7fd-57604568d382/project/7646dba2-55e4-45a5-87c0-3e0fecfb92a5.svg"
            alt="wakatime"></a>
</p>

# Minishell

**Minishell** is a project from 42 School that challenges us to recreate a minimal yet functional Unix shell almost from scratch. Built entirely in C, this project was built by the two of us, pushing our skills in system programming, process management, and string parsing to the limit—while also pushing our patience to its breaking point more times than we'd like to admit!

## 🚀 Features

- **Custom Prompt** → A stylish arrow that changes color based on the last return value.
- **Command Execution** → Run executables from the system's `$PATH`, including absolute and relative paths.
- **Pipes (`|`)** → Chain multiple commands together, just like in a real shell.
- **Redirections (`>`, `>>`, `<`, `<<`)** → Handle file input/output redirections seamlessly.
- **Environment Variables (`$VAR`)** → Expand variables, including `$?` for the last command’s exit status.
- **Built-in Commands** → Includes `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Signal Handling** → Proper response to `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.
- **Logical Operators (`&&` and `||`)** → Execute commands conditionally based on exit statuses.
- **Wildcard Expansion (`*`)** → Expand wildcards (only on the current directory).

## ⚙️ How It Works

Minishell is not just a simple command parser. It follows a structured pipeline to interpret and execute commands:

1. **Lexing & Tokenization** → The input string is split into tokens and stored in a linked list.
2. **Syntax Validation** → We ensure the correct use of quotes, parentheses, pipes, and redirections.
3. **Here-Document Processing** → If `<<` is detected, we pre-fetch user input and store it in a temporary file.
4. **Abstract Syntax Tree (AST) Construction** → Commands are structured hierarchically based on their execution order.
5. **Execution** → The AST is recursively executed, handling pipes, redirections, and operators dynamically.

---

## 🎭 Example Usages

```bash
➜ minishell
➜ echo "Hello, World!"
Hello, World!
➜ ls | grep .c
main.c exec.c parser.c
➜ cat file.txt > output.txt
➜ echo $?  # Last command's exit status
0
➜ (mkdir test && cd test) || echo "Failed to create directory"
➜ echo *  # Wildcard expansion
file1.txt file2.txt script.sh
➜ exit
```

---

## 🛠️ Technologies & Concepts Used
- C (no external libraries apart from standard functions)
- Process management (`fork`, `execve`, `waitpid`)
- File descriptors and redirections
- Signal handling (`SIGINT`, `SIGQUIT`)
- Dynamic memory management (linked lists, AST structures)
- Lexing, Parsing, and Shell Expansion

---

## 🔗 GitHub Repository
Check out the full code and documentation here: *[GitHub Link of Your Teammate]*

