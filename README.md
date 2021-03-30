# Tiny-Shell
Tiny Shell for Windows. Use command "help" for detail.

# Environment
-	Language: C++, GNU C++ 14, IDE: CodeBlock 20.07 MinGW
-	Oparating System: Windows 10 1909

## Commands

### Get help
- Show all command.
- Syntax: <code>help [command]</code>, while:
 + [command] is name of the command you want to show detail.

### Create new process
- Create a new process running child.exe which only countdown to zero and stop.
- Syntax: <code>child [name] [seconds] [option]</code>, while:
 + [name] is the name of the process. This parameters is required.
 + [seconds] is the time (seconds ) for the process to countdown.
 + [options] is the mode of the process. It is -f (foreground mode ) or -b (background mode ).

### List all running process
- List all running process.
- Syntax: <code>list</code>

### Kill a process
- Kill a process.
- Syntax: <code>kill [name]</code>, while:
 + [name] is the name of the process.

### List all directory
- List all files and folder in directory.
- Syntax: <code>dir [directory]</code>, while:
 + [directory] is a path to a directory.

### Show date and time
- Show current date and time.
- Syntax: <code>date</code>

### Exit shell
- Exit shell but all process will not be terminal.
- Syntax: <code>exit</code>