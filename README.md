# Lox programming language

This is the repository for the Lox programming language written in C++.

Original Java implementation - [Crafting Interpreters](http://www.craftinginterpreters.com/) by Robert Nystrom.

## Prerequisites

Project can be potentially built and/or ran on the older platforms. WIP.

- Windows 10/11 32-bit or 64-bit
- Visual Studio Build Tools 2022
- Visual Studio Community 2022
- Have the `vcvarsall.bat` in your PATH. Possible file paths:
  - `path/to/Microsoft Visual Studio/<version>/Community/VC/Auxiliary/Build/vcvarsall.bat`
  - `path/to/Microsoft Visual Studio/<version>/BuildTools/VC/Auxiliary/Build/vcvarsall.bat`
- Python 3.6+ (optionally)
    - cpplint (for code style checking).
      - Install with `pip install cpplint`
      - My rules at - [CPPLINT.cfg](https://github.com/bissakov/lox/blob/main/CPPLINT.cfg)
    - clang-format (for code formatting).
      - Install with `pip install clang-format`
      - My rules (modified, based on Google) at - [.clang-format](https://github.com/bissakov/lox/blob/main/.clang-format)

## Building
```bash
# Clone the repository
git clone https://github.com/bissakov/lox.git

# Change directory
cd lox

# Build (modify the batch script if you want to target x86)
.\build.bat

# Run
.\build\lox.exe "path\to\script.lox"
```
