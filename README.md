# A tiny shell with a few functions about process

## Environment
- Language: C++, complier GNU C++ 14, IDE: CodeBlocks 20.07 MinGW
- Operating system: Windows 10 1909

## Commands

### Get help
- Show all command.
- Syntax: help [command], while:
 + [command] is name of the command you want to show detail.

### Create new process
- Create a new process running child.exe which only countdown to zero and stop.
- Syntax: child [name] [seconds] [option], while:
 + [name] is the name of the process. This parameters is required.
 + [seconds] is the time (seconds ) for the process to countdown.
 + [options] is the mode of the process. It is -f (foreground mode ) or -b (background mode ).

### List all running process
- List all running process.
- Syntax: list

### Kill a process
- Kill a process.
- Syntax: kill [name], while:
 + [name] is the name of the process.

### List all directory
- List all files and folder in directory.
- Syntax: dir [directory], while:
 + [directory] is a path to a directory.

### Show date and time
- Show current date and time.
- Syntax: date

### Exit shell
- Exit shell but all process will not be terminal.
- Syntax: exit