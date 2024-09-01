# Muehle CommandLine

## Game Rules

The game is played with the optional **flying** or **jumping** phase.
[Click here for rule explanation from Wikipedia](https://en.wikipedia.org/wiki/Nine_men%27s_morris)



## Getting started

```
git clone https://github.com/KurtWagner23/Muehle.git
cd Muehle
```

## Prerequisites

- CMake 3.20 or Visual Studio CMakeTools
- ninja (install with apt install ninja or brew install ninja)
- C++ Compiler
- **Optional** CMake Tools Extension in VS Code for easier building and testing

## How to build with Command Line
```
cmake --preset "debug-config"
cmake --build --preset "build-debug"
```
### Start Program
```
./build/muehle_commandline
```

## In VS Code

- Open in VS Code with CMake Tools and C/C++ Extension installed
- Choose Preset "Debug configuration"
- Click on build on bottom bar
  
### Start Program in VS Code

- Click on Arrow on bottom bar
