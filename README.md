# Task & Habit Tracker (C++ CLI)

A clean, dependency-free command-line task/habit tracker built with modular
OOP: `Task`, `TaskManager`, and `FileHandler`.

## Features
- Add, edit, delete, and view tasks from an interactive terminal menu
- Priority tags (`Low` / `Medium` / `High`)
- Optional due dates (`YYYY-MM-DD`)
- Sort the task list by priority or due date
- Persists automatically to a plain-text file (`data/tasks.txt`) after every
  change — no database, no external JSON library required

## Build

### With CMake
```bash
mkdir build && cd build
cmake ..
cmake --build .
./tasktracker
```

### Without CMake (single g++ call)
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o tasktracker
./tasktracker
```

Run the binary from the project root (or make sure a `data/` directory
exists alongside it) — `main.cpp` stores tasks at `data/tasks.txt` relative
to the working directory.

## Storage format
Each line in `data/tasks.txt` is one task, pipe-delimited:
```
id|title|description|priority|dueDate|completed
```
`|` and newlines inside free text are percent-escaped so titles/descriptions
can contain them safely. Swapping this for real JSON later only requires
rewriting `FileHandler` — `Task` and `TaskManager` don't know or care about
the storage format.

## Suggested commit history (incremental build-up)
1. `Init: CLI menu skeleton and input loop`
2. `Add Task struct and in-memory vector storage`
3. `Implement FileHandler for persistent save/load`
4. `Add priority tags and due-date sorting`
5. `Refactor into TaskManager/Task/FileHandler OOP split`

## Ideas for further increments
- Recurring "habit" tasks with streak tracking
- Colorized terminal output (ANSI codes) for priority/overdue tasks
- Filtering (by tag, completion status, overdue only)
- Swap `FileHandler` internals for `nlohmann/json` if you want real JSON on disk
- Unit tests for `TaskManager` with a mocked `FileHandler`
