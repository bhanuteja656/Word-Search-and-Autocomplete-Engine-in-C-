# Word Search & Autocomplete Engine (C)

A command-line tool that loads a dictionary from a text file and lets
you search words, autocomplete by prefix, and track search history —
built in C as a mini-project to apply data structures beyond the
basics (hash tables, tries, linked lists).

## Features

- **Hash table** — O(1) exact word lookup with collision chaining
- **Trie** — prefix-based autocomplete ("show me all words starting with...")
- **Search history** — singly linked list, tracks every word searched
- **Most frequent search** — sorted doubly circular linked list, ranks
  words by how often they were searched
- **Multi-file support** — load one or more dictionary files, or add
  more files mid-session
- **Timing** — measures how long insertion/search operations take
- **Session logging** — both program output and user input are saved
  to `session_log.txt`, giving a full transcript of each run

## File structure

| File | Purpose |
|---|---|
| `main.c` | Menu loop, ties all modules together |
| `stdmine.c` / `stdmine.h` | Custom input helper functions (get_str, get_int, etc.) |
| `hashtable.c` / `hashtable.h` | Hash table insert, search, frequency tracking |
| `tries.c` / `tries.h` | Trie insert and prefix search |
| `circularlist.c` / `circularlist.h` | Search history + frequency-sorted list |
| `words.txt` | Sample dictionary file |
| `Makefile` | Build instructions |

## Build & run

\`\`\`
make
./run words.txt
\`\`\`

You can also load multiple files at once:
\`\`\`
./run words.txt words2.txt
\`\`\`

## Menu

\`\`\`
1. Search
2. Enter new file
3. History (recent searches / most frequent)
4. All strings (print full table)
5. Advanced search (prefix / autocomplete)
6. Exit
\`\`\`

Type `done` at any point in the search prompt to return to the main menu.

## Notes

- Session logging (program output + user input) uses `popen`/`dup2`/`tee`
  — this technique was adapted from research rather than being my own
  original idea, implementation adjusted to fit this project.
- Hash function buckets words by first letter (A–Z); collisions are
  chained and kept sorted within each bucket.
- This project was built incrementally while learning pointers,
  dynamic memory allocation, sorting, searching, and linked list
  variants (singly, circular, doubly linked).

## Author

Kolluri Bhanuteja — B.Tech ECE
