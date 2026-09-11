# chell

A small Unix shell written in C, built to understand how shells actually work:
process creation, program replacement, and the parent/child relationship behind
every command you run in a terminal.

**Status: WIP.** Currently reads and executes a single command, then exits.

---

## Build

Requires `gcc` and a POSIX system.

```bash
chmod +x build     # first time only
./build
```

Enter `b` at the prompt for a standard build. The binary lands in `bin/chell`
and runs immediately.

To build by hand:

```bash
gcc -Wall -Wextra -Iinclude -o bin/chell main.c src/chell.c
```

---

## Usage

```
$ ls -al
$ date
$ gcc --version
```

Commands are resolved through `PATH`, so anything on your system works.
Can compile itself (cool)

---

## How it works

Each command goes through four steps:

1. **Read** — `fgets` pulls a line from stdin; the trailing newline is trimmed.
2. **Tokenize** — `strtok` splits on spaces into a NULL-terminated `argv` array.
3. **Fork** — the process duplicates itself, producing a parent and a child.
4. **Exec** — the child calls `execvp`, replacing its own memory image with the
   target program. The parent blocks in `wait` until the child finishes.

---

## Layout

```
chell/
├── main.c            # entry point; forwards argc/argv
├── include/
│   └── chell.h       # public interface
├── src/
│   └── chell.c       # implementation
├── build             # build script
└── bin/              # output (gitignored)
```
---

## Notes

Written as a learning project. The interesting constraint is doing everything
with POSIX primitives`fork`, `execvp`, `wait` rather than shelling out to
`system()`, which would just delegate the hard parts back to `/bin/sh`.
