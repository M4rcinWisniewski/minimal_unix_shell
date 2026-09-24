# my_sh

A small Unix shell written in C. Project developed for educational purposes.

Built to learn systems programming and get closer to embedded Linux.
Not a POSIX shell. Not trying to be bash. Just the core ideas, done properly.

## What it does

- REPL with prompt
- Runs any program on `PATH` via `fork` + `execvp` + `waitpid`
- Handles command arguments
- Tracks exit status internally
- Ignores `SIGINT` in the shell, so Ctrl-C kills the child, not the shell
- Clean EOF handling

## What it doesn't (yet)

- Builtins (`cd`, `exit`, `export`, ...)
- Pipes (`|`), redirections (`>`, `<`), operators (`;`, `&&`, `||`)
- Quoting, escaping, globbing
- Variable expansion (`$?`, `$HOME`, ...)
- Job control

It's a shell core, not a shell language.

## Build
```sh
make
```
In memory of my beloved dog Popi, rest in peace.

<img width="2048" height="1536" alt="815866337_1442310134489212_8548621330676981712_n" src="https://github.com/user-attachments/assets/199ecbc3-744e-444a-823f-9b081321dcf3" />
