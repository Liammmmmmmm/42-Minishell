<p align='center'>
   <a href="https://www.linux.org/">
      <img src="https://img.shields.io/badge/OS-Linux-blue?logo=linux&logoColor=white"
            alt="OS - Linux"></a>
   <a href="https://wakatime.com/badge/user/7d36b55a-b5ff-46c4-b7fd-57604568d382/project/7646dba2-55e4-45a5-87c0-3e0fecfb92a5">
      <img src="https://wakatime.com/badge/user/7d36b55a-b5ff-46c4-b7fd-57604568d382/project/7646dba2-55e4-45a5-87c0-3e0fecfb92a5.svg"
            alt="wakatime"></a>
</p>

# Minishell

**Minishell** is a project from 42 School that challenges us to recreate a minimal yet functional Unix shell almost from scratch. Built entirely in C, this project was developed by the two of us, pushing our skills in system programming, process management, and string parsing to the limit—while also testing our patience more times than we'd like to admit!

## 🚀 Features

- **Custom Prompt** → A stylish arrow that changes color based on the last return value.  
- **Command Execution** → Run executables from the system’s `$PATH`, including absolute and relative paths.  
- **Pipes (`|`)** → Chain multiple commands together, just like in a real shell.  
- **Redirections (`>`, `>>`, `<`, `<<`)** → Handle file input/output redirections seamlessly.  
- **Environment Variables (`$VAR`)** → Expand variables, including `$?` for the last command’s exit status.  
- **Built-in Commands** → Supports `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.  
- **Signal Handling** → Properly responds to `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`.  
- **Logical Operators (`&&` and `||`)** → Execute commands conditionally based on exit statuses.  
- **Wildcard Expansion (`*`)** → Expands wildcards (only within the current directory).  

## 🎭 Example Usages

![Example usage](./img/example.png)  

## ⚙️ How It Works

Minishell is not just a simple command parser. It follows a structured pipeline to interpret and execute commands:

1. **Lexing & Tokenization** → The input string is split into tokens and stored in a linked list.
2. **Syntax Validation** → Ensures correct use of quotes, parentheses, pipes, and redirections.
3. **Here-Document Processing** → If `<<` is detected, user input is pre-fetched and stored in a temporary file.
4. **Abstract Syntax Tree (AST) Construction** → Commands are structured hierarchically based on execution order.
5. **Execution** → The AST is recursively executed, handling pipes, redirections, and operators dynamically.

### Example  

Given the following command:  

```bash
➜ [lilefebv] 42-Minishell ❯ (echo $PWD && (ls -l | grep *.c) || echo "No .c files found") > output.txt && cat output.txt | wc -l
```

First, it is **tokenized**, resulting in:  

```
        Token                       Text     Previous       Self       Next
   PAREN_OPEN                     (null)        (nil)  0x1a78b40  0x1a78b70
      COMMAND                  echo $PWD    0x1a78b40  0x1a78b70  0x1a78ba0
          AND                     (null)    0x1a78b70  0x1a78ba0  0x1a78bf0
   PAREN_OPEN                     (null)    0x1a78ba0  0x1a78bf0  0x1a78c20
      COMMAND                      ls -l    0x1a78bf0  0x1a78c20  0x1a78c70
         PIPE                     (null)    0x1a78c20  0x1a78c70  0x1a78ca0
      COMMAND                 grep "*.c"    0x1a78c70  0x1a78ca0  0x1a78a30
  PAREN_CLOSE                     (null)    0x1a78ca0  0x1a78a30  0x1a78cf0
           OR                     (null)    0x1a78a30  0x1a78cf0  0x1a5b190
      COMMAND   echo "No .c files found"    0x1a78cf0  0x1a5b190  0x1a78950
  PAREN_CLOSE                     (null)    0x1a5b190  0x1a78950  0x1a78980
 REDIRECT_OUT                     (null)    0x1a78950  0x1a78980  0x1a789b0
       FILE_R                 output.txt    0x1a78980  0x1a789b0  0x1a78a00
          AND                     (null)    0x1a789b0  0x1a78a00  0x1a78b10
      COMMAND             cat output.txt    0x1a78a00  0x1a78b10  0x1a78a80
         PIPE                     (null)    0x1a78b10  0x1a78a80  0x1a78ab0
      COMMAND                      wc -l    0x1a78a80  0x1a78ab0      (nil)
```

Since the syntax is **valid** (no consecutive operators, misplaced parentheses, etc.), we proceed to the next step.  

### Abstract Syntax Tree (AST)  

The parsed command is converted into an **AST**:  

![AST](img/ast.png)  

### Execution

Execution happens **recursively**, following these principles:
- **Command nodes** are executed directly.
- **Redirection nodes** modify input/output for all child nodes.
- **Pipe nodes** create pipes between left and right child nodes, allowing multiple commands to interact.
- **AND/OR nodes** execute the left child first, then conditionally execute the right child based on the return value.

Here’s a visual representation of the execution flow (warning: brain overload ahead 😵):  

![Execution schema](img/exec.png)

## Conclusion  

This wasn't our favorite project, but it covered a wide range of fundamental topics and gave us a deeper understanding of how a shell really works.  

Our Minishell is **quite robust**—it survived extensive testing and abuse from fellow students, pushing it to its limits. If you find a bug or crash, feel free to open an issue (though we can't promise we'll have the motivation to fix it 😆).

Hope this README helped you understand how our Minishell works! 🚀

## 🔗 Contributors
- [Audric](https://github.com/pandhacker)
- [Liam](https://github.com/Liammmmmmmm)

</br></br></br>

## 🛠 You Might Need This Too  

Debugging a shell can be a nightmare, so here are some useful tools to help you track down memory issues and unexpected behaviors.  

### 🔍 Full Memory Leak Check with Valgrind  

To check for memory leaks, file descriptor issues, and other tricky bugs, you can use Valgrind with the following command:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-mismatched-frees=yes --track-fds=yes --trace-children=yes --suppressions=supp.supp ./minishell
```  

This will:  
- Detect **all types of memory leaks** (definitely lost, indirectly lost, etc.).  
- Track **invalid memory accesses** and **mismatched frees**.  
- Show **unclosed file descriptors**, which can be crucial for debugging a shell.  
- Trace **child processes**, ensuring that forks don’t leave memory leaks undetected.  

### 📜 Suppression File (Avoid False Positives)  

Since **readline** has known memory leaks that we can’t fix, we use a suppression file (`supp.supp`) to ignore them:  

```text
{
    ignore_libreadline_leaks
    Memcheck:Leak
    ...
    obj:*/libreadline.so.*
}
```  

This prevents Valgrind from reporting leaks inside `libreadline`, making debugging more focused on **actual leaks in Minishell**.  


### ⚔️ Torture Testing  

In the repository, you'll also find a file named **`testsdesenfer`**. This contains a collection of **extreme edge cases and tricky commands** that helped us push Minishell to its limits.  

If you want to see how well your shell holds up, run those tests—you might be surprised by what breaks! 🚀


## Try it out  

```bash
git clone https://github.com/Liammmmmmmm/42-Minishell.git
git submodule --init --recursive
```