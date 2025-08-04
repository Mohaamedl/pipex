# PIPEX - A Unix Pipeline Reimplementation

![42 Project](https://img.shields.io/badge/42-Project-blue)
![Norminette](https://img.shields.io/badge/Norminette-Passing-green)
![Tests](https://img.shields.io/badge/Tests-31%2F31-brightgreen)

## 📖 Table of Contents

1. [Project Overview](#project-overview)
2. [How Unix Pipes Work](#how-unix-pipes-work)
3. [Project Structure](#project-structure)
4. [Implementation Details](#implementation-details)
5. [Features](#features)
6. [Compilation & Usage](#compilation--usage)
7. [Technical Deep Dive](#technical-deep-dive)
8. [Testing](#testing)
9. [Troubleshooting](#troubleshooting)

## 🎯 Project Overview

**Pipex** is a 42 school project that recreates the behavior of Unix shell pipes. The goal is to understand how inter-process communication works using pipes, file descriptors, and process management in C.

### What it does:
```bash
# Instead of writing:
< file1 cmd1 | cmd2 > file2

# You can use pipex:
./pipex file1 cmd1 cmd2 file2
```

### Learning Objectives:
- **Process Management**: `fork()`, `execve()`, `wait()`
- **File Descriptor Manipulation**: `dup2()`, `pipe()`, file operations
- **Inter-Process Communication**: Understanding how processes communicate
- **Error Handling**: Robust error management in system programming
- **Memory Management**: Proper allocation and deallocation

## 🔧 How Unix Pipes Work

### The Concept
A pipe connects the output of one command to the input of another:

```
┌─────────┐    ┌──────┐    ┌─────────┐
│  cmd1   │───►│ pipe │───►│  cmd2   │
│ stdout  │    │      │    │  stdin  │
└─────────┘    └──────┘    └─────────┘
```

### What Happens Internally:
1. **Pipe Creation**: `pipe()` creates two file descriptors
   - `pipefd[0]`: Read end
   - `pipefd[1]`: Write end

2. **Process Forking**: `fork()` creates child processes
   - Parent and child share the same pipe

3. **File Descriptor Redirection**: `dup2()` redirects standard I/O
   - Child 1: `stdout` → `pipefd[1]`
   - Child 2: `stdin` ← `pipefd[0]`

4. **Command Execution**: `execve()` replaces process with new program

## 📁 Project Structure

```
pipex/
├── 🔧 Mandatory Implementation
│   ├── pipex.c              # Main program (2 commands only)
│   ├── pipex.h              # Header file
│   ├── utils.c              # Utility functions
│   └── path.c               # Path resolution & execution
│
├── 🌟 Bonus Implementation
│   ├── pipex_bonus.c        # Multiple commands + here_doc
│   ├── pipex_bonus.h        # Bonus header
│   ├── pipex_bonus_utils.c  # Bonus utilities
│   ├── pipex_bonus_path.c   # Bonus path handling
│   └── pipex_bonus_heredoc.c# Here_doc functionality
│
├── 📚 Library
    └── libft/               # Custom C library
```

## 🔨 Implementation Details

### 1. Mandatory Version (`pipex.c`)

**Usage**: `./pipex file1 cmd1 cmd2 file2`

**Equivalent to**: `< file1 cmd1 | cmd2 > file2`

```c
int main(int ac, char **av, char **env)
{
    int p_fd[2];    // Pipe file descriptors
    pid_t pid;      // Process ID
    
    // Input validation
    if (ac != 5)
        exit_error("Usage: ./pipex file1 cmd1 cmd2 file2");
    
    // Create pipe
    if (pipe(p_fd) == -1)
        exit_error("pipe");
    
    // Fork first child for cmd1
    pid = fork();
    if (pid == 0)
        child_process(av, p_fd, env);   // Execute cmd1
    
    // Parent continues with cmd2
    parent_process(av, p_fd, env);      // Execute cmd2
}
```

### 2. Child Process (First Command)

```c
void child_process(char **av, int *p_fd, char **env)
{
    int fd_in;
    
    // Open input file
    fd_in = open(av[1], O_RDONLY);
    if (fd_in == -1)
        exit_error("Input file");
    
    // Redirect stdin to input file
    dup2(fd_in, STDIN_FILENO);
    close(fd_in);
    
    // Redirect stdout to pipe write end
    dup2(p_fd[1], STDOUT_FILENO);
    close(p_fd[0]);  // Close unused read end
    close(p_fd[1]);  // Close original write end
    
    // Execute first command
    exec(av[2], env);
}
```

### 3. Parent Process (Second Command)

```c
void parent_process(char **av, int *p_fd, char **env)
{
    int fd_out;
    
    // Open output file
    fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1)
        exit_error("Output file");
    
    // Redirect stdin to pipe read end
    dup2(p_fd[0], STDIN_FILENO);
    close(p_fd[1]);  // Close unused write end
    close(p_fd[0]);  // Close original read end
    
    // Redirect stdout to output file
    dup2(fd_out, STDOUT_FILENO);
    close(fd_out);
    
    // Wait for child to finish
    wait(NULL);
    
    // Execute second command
    exec(av[3], env);
}
```

### 4. Command Execution

```c
void exec(char *cmd, char **env)
{
    char **s_cmd;
    char *path;
    
    // Split command into arguments
    s_cmd = ft_split(cmd, ' ');
    if (!s_cmd || !s_cmd[0])
        exit_error("Invalid command");
    
    // Find executable path
    path = get_path(s_cmd[0], env);
    if (!path)
        exit_error("Command not found");
    
    // Execute command
    if (execve(path, s_cmd, env) == -1)
        exit_error("execve failed");
}
```

### 5. Path Resolution

```c
char *get_path(char *cmd, char **env)
{
    char **allpath;
    char *result;
    
    // Check if command is already a full path
    if (access(cmd, F_OK | X_OK) == 0)
        return (ft_strdup(cmd));
    
    // Search in PATH environment variable
    allpath = ft_split(my_getenv("PATH", env), ':');
    result = search_in_path(allpath, cmd);
    
    ft_free_tab(allpath);
    return (result);
}
```

## 🌟 Features

### Mandatory Features
- ✅ **Two-command pipeline**: `./pipex file1 cmd1 cmd2 file2`
- ✅ **File redirection**: Input from file1, output to file2
- ✅ **Error handling**: Proper error messages and exit codes
- ✅ **PATH resolution**: Finds commands in system PATH
- ✅ **Memory management**: No memory leaks

### Bonus Features
- ✅ **Multiple pipes**: `./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdN file2`
- ✅ **Here document**: `./pipex_bonus here_doc LIMITER cmd1 cmd2 file`
- ✅ **Append mode**: When using here_doc, output appends to file

### Here Document Example
```bash
# Traditional shell:
cat << EOF | grep "hello" | wc -l > output.txt
hello world
hello there
goodbye
EOF

# With pipex_bonus:
./pipex_bonus here_doc EOF "grep hello" "wc -l" output.txt
```

## 🚀 Compilation & Usage

### Building the Project

```bash
# Compile mandatory version
make

# Compile bonus version
make bonus

# Clean build files
make clean

# Full clean (including libft)
make fclean

# Rebuild everything
make re
```

### Usage Examples

#### Mandatory Version
```bash
# Basic usage
./pipex input.txt "grep hello" "wc -l" output.txt

# Equivalent shell command:
< input.txt grep hello | wc -l > output.txt

# With absolute paths
./pipex /etc/passwd "grep root" "/usr/bin/cut -d: -f1" users.txt

# Error handling
./pipex nonexistent.txt "cat" "wc" output.txt  # Handles missing files
./pipex input.txt "invalidcmd" "wc" output.txt  # Handles invalid commands
```

#### Bonus Version
```bash
# Multiple commands
./pipex_bonus input.txt "cat" "grep hello" "sort" "uniq" output.txt

# Here document
./pipex_bonus here_doc EOF "cat" "wc -l" lines.txt
line 1
line 2
line 3
EOF

# Complex pipeline
./pipex_bonus /etc/passwd "cat" "grep sh" "cut -d: -f1" "sort" users.txt
```

## 🔍 Technical Deep Dive

### File Descriptor Management

```
Process Layout:
┌─────────────────┐
│   fd 0: stdin   │ ──► Redirected to input file/pipe
│   fd 1: stdout  │ ──► Redirected to output file/pipe  
│   fd 2: stderr  │ ──► Remains unchanged
│   fd 3: pipe[0] │ ──► Read end of pipe
│   fd 4: pipe[1] │ ──► Write end of pipe
└─────────────────┘
```

### Process Tree Structure

```
Parent Process (main)
├── Child 1 (cmd1)
│   ├── stdin:  input_file
│   └── stdout: pipe[1]
└── Child 2 (cmd2)
    ├── stdin:  pipe[0]  
    └── stdout: output_file
```

### Memory Management Strategy

1. **Allocation Tracking**: Every `malloc()` has corresponding `free()`
2. **Error Cleanup**: All error paths clean up allocated memory
3. **Libft Integration**: Uses tested library functions
4. **Tab Cleanup**: `ft_free_tab()` for string arrays

### Error Handling Philosophy

```c
// Pattern used throughout the project
if (system_call() == -1)
{
    cleanup_resources();
    exit_error("Descriptive error message");
}
```

## 🧪 Testing

### Included Test Suite

The project includes comprehensive testing:

```bash
# Run main test suite (31 tests)
cd pipex-tester && ./run.sh

# Run pipexMedic (stricter tests)
cd tester && ./test.sh basic
```

### Test Categories

1. **Basic Functionality**
   - Simple commands
   - File operations
   - Path resolution

2. **Error Handling**
   - Missing files
   - Invalid commands
   - Permission errors

3. **Edge Cases**
   - Empty files
   - Large files
   - Special devices (`/dev/urandom`)

4. **Memory Management**
   - Leak detection
   - Valgrind testing

### Manual Testing

```bash
# Test basic functionality
echo "hello world" | ./pipex /dev/stdin "cat" "wc -w" /dev/stdout

# Test error handling
./pipex nonexistent.txt "cat" "wc" output.txt

# Test complex commands
./pipex /etc/passwd "grep root" "cut -d: -f1" root_users.txt

# Test bonus features
./pipex_bonus input.txt "cat" "grep test" "sort" "uniq -c" stats.txt
```

## 🐛 Troubleshooting

### Common Issues

1. **"Command not found"**
   ```bash
   # Make sure command exists in PATH
   which your_command
   
   # Use absolute path if needed
   ./pipex file1 "/bin/cat" "/usr/bin/wc" file2
   ```

2. **"Permission denied"**
   ```bash
   # Check file permissions
   ls -la input_file
   
   # Make sure files are readable/writable
   chmod 644 input_file
   ```

3. **"Broken pipe" errors**
   - Usually indicates one process died early
   - Check if commands are valid
   - Verify input file exists and is readable

4. **Memory leaks**
   ```bash
   # Test with valgrind
   valgrind --leak-check=full ./pipex file1 "cat" "wc" file2
   ```

### Debug Tips

1. **Use strace to see system calls**:
   ```bash
   strace -f ./pipex input.txt "cat" "wc" output.txt
   ```

2. **Check file descriptors**:
   ```bash
   # While program runs, check open FDs
   lsof -p $(pgrep pipex)
   ```

3. **Test commands individually**:
   ```bash
   # Verify commands work separately
   cat input.txt | your_command
   ```

### Performance Considerations

- **Large Files**: The program handles large files efficiently through streaming
- **Memory Usage**: Minimal memory footprint, no unnecessary buffering
- **Process Overhead**: Efficient fork/exec pattern

## 📝 Implementation Notes

### Design Decisions

1. **Modular Architecture**: Separated concerns into different files
2. **Error First**: Comprehensive error handling throughout
3. **Library Integration**: Uses libft for proven utility functions

### Code Quality

- ✅ **Memory Safe**: No leaks, proper cleanup
- ✅ **Error Robust**: Handles all error conditions
- ✅ **Well Documented**: Clear function and variable names

### Future Enhancements

Potential improvements (beyond project scope):
- Advanced shell parsing (quotes, escapes)
- Built-in command support
- Job control features
- Signal handling

## 📚 Resources

### Documentation
- [pipe(2) man page](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [fork(2) man page](https://man7.org/linux/man-pages/man2/fork.2.html)
- [execve(2) man page](https://man7.org/linux/man-pages/man2/execve.2.html)
- [dup2(2) man page](https://man7.org/linux/man-pages/man2/dup2.2.html)

### Learning Resources
- [Unix Pipes Explained](https://www.geeksforgeeks.org/pipe-system-call/)
- [Process Management in Unix](https://www.tutorialspoint.com/unix/unix-processes.htm)


