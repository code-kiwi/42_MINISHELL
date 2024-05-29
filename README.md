![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
# MINISHELL

> **Note:** This is a project from **42 learning cursus**.

## Description
This program is a minimalistic shell.<br>
The user can interact with the operating system by typing commands into the Minishell.

## Requirements
As mentionned previously, this shell is minimalistic. It means that it does not implement all the classic shell features.<br><br>
**Here is a list of the features implemented into Minishell:**<br>
- Display a prompt
- Have a working history
- Search and launch the right executable for a command (based on `PATH` environment variable)
- Handle signals `SIGINT` and `SIGQUIT`
- Handle `single quotes`
- Handle `double quotes`
- Implement `var expansion`
- Implement `wildcard expansion` (only for current directory)
- Implement some redirections:
    - `<` should redirect input
    - `>` should redirect output
    - `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history
    - `>>` should redirect output in append mode
- Implement `pipes`
- Handle `environment variables`
- Handle `$?`
- Handle `&&` and `||` operators
- Handle subshells `(subshell)`

**NOTE:**<br>
- No more than one global variable is authorized
- Memory leaks and bad file descriptors handling are forbidden
- Bash has to be considered as a reference

**The project implements some `builtins`:**

|NAME   |DESCRIPTION                                            |COMMENT                               |
|-------|-------------------------------------------------------|--------------------------------------|
|echo   |Display a line of text                                 |With option `-n` only                 |
|cd     |Change the working directory                           |With only a relative or absolute path |
|pwd    |Print name of current/working directory                |with no options                       |
|export |Set the export attribute for variables                 |with no options                       |
|unset  |Unset values and attributes of variables and functions |with no options                       |
|env    |Display the shell's environment content                |with no options or arguments          |
|exit   |Cause normal process termination                       |with no options                       |

## Principles
This minishell works using an `AST` (Abstract Syntax Tree).<br>
The user input is parsed and then converted to an AST which will be executed.<br><br>
**Here is a schema describing the global working principles:**<br><br>
![PRINCIPLES](https://github.com/code-kiwi/42_MINISHELL/blob/main/assets/principles.png)
<br><br>

---
**Here is an example with a simple command:**<br><br>
![EXAMPLE](https://github.com/code-kiwi/42_MINISHELL/blob/main/assets/principles_example.png)
<br>

---
The expansion cannot be done before the execution, because the commands can have an impact on the environment and affect other command expansions.<br>
Example: `export TEST=14 && echo $TEST && export TEST+=91 && echo $TEST`


## Setup instructions
1. Clone the repo: `git clone https://github.com/code-kiwi/42_PIPEX.git`
2. Compile the project using `make` (the libft library will be downloaded automatically)
The executable `minishell` should be created.<br><br>
You can then use this executable and explore it.
> **Note:** The bonus part is included into the mandatory part.

## How to use the progam ?
Once launched, the program shows you a prompt.<br>
You can type commands in order to interact with your system, like in any other shell.<br><br>
![DEMO](https://github.com/code-kiwi/42_MINISHELL/blob/main/assets/minishell.gif)

## Testing
> Work in progress

## Grade
![MINISHELL](https://github.com/ayogun/42-project-badges/blob/main/badges/minishellm.png)<br><br>
`125/125`
## Credits
The badge comes from [this repo](https://github.com/ayogun/42-project-badges/tree/main), by [@ayogun](https://github.com/ayogun) which proposes a lot of amazing badges for 42 projects.
