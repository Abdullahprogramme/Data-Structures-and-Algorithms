# Build & Run

This project contains implementations for WordNet, a Digraph type, a ShortestCommonAncestor utility, and an Outcast detector. It includes three main programs in the `Mains/` folder:

- `Mains/WordNet_main.cpp` — randomized rooted-DAG SCA unit test (requires two args: `n m`).
- `Mains/SCA_main.cpp` — small ShortestCommonAncestor unit test (no args).
- `Mains/Outcast_main.cpp` — Outcast demo that constructs `WordNet` from `synsets.csv` / `hypernyms.csv` (requires optional argument: `k`).

## Requirements

- A C++17 compiler (g++, clang++, or MSVC).
- PowerShell on Windows (commands below are shown for PowerShell).

## Compile (g++)

Run these commands from the repository root (the directory that contains `Sources/`, `Mains/`, and `Headers/`):

```powershell
g++ -std=c++17 -O2 -I"Headers" -o WordNet_main.exe Mains/WordNet_main.cpp Sources/Digraph.cpp Sources/ShortestCommonAncestor.cpp
g++ -std=c++17 -O2 -I"Headers" -o SCA_main.exe Mains/SCA_main.cpp Sources/Digraph.cpp Sources/ShortestCommonAncestor.cpp
g++ -std=c++17 -O2 -I"Headers" -o Outcast_main.exe Mains/Outcast_main.cpp Sources/WordNet.cpp Sources/Digraph.cpp Sources/ShortestCommonAncestor.cpp Sources/Outcast.cpp
```

Notes:

- The `-I"Headers"` flag adds the project header directory; remove or change it if your headers are elsewhere.
- If you get linker errors, ensure the correct `Sources/*.cpp` files are included for the symbols that error.

## Run examples

- Run the randomized SCA unit test (example `n=1000 m=1000`):

```powershell
.\WordNet_main.exe 1000 1000
```

- Run the SCA small unit test:

```powershell
.\SCA_main.exe
```

- Run the Outcast demo (default limits to the first `K=20` nouns to keep runtime reasonable). Optionally pass `K` as the first argument:

```powershell
.\Outcast_main.exe          # runs with default K=20
.\Outcast_main.exe 100      # runs Outcast on first 100 nouns
```

## Known Issues
The Outcast file is not running for large numbers, I have tested it for default value of 20 and it works fine, for 50 its also fine but for large number such as 1000, it stops working.