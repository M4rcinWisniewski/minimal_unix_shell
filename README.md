# my_sh

A small Unix shell written in C.

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
