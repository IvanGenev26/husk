# husk 🐚

A small Unix shell written in C, built from scratch to learn how shells
and processes work under the hood.

> 🚧 Work in progress. Built a feature at a time.

## Features
- [x] Prompt and reading input
- [x] Running commands (fork + exec)
- [ ] Built-ins: `cd`, `exit`
- [ ] Pipes (`|`)
- [ ] Redirection (`>`, `<`)

## Build
​```bash
mkdir build && cd build
cmake ..
make
./husk
​```

## Why
I'm building this to understand fork/exec, file descriptors, and how
the OS runs programs.
