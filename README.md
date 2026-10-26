# C++ Trading System

I'll start with some catching up on C++ language and then start
the project end-to-end.

## Workflow

### 1. Full Project Build (CMake + Ninja)
Use this for compiling the actual project, which handles multiple files, external libraries, and code optimizations.

**Navigate into the folder:** 
```shell
cd folder_name
```

Configure the project:(Run this the very first time, OR whenever you create a brand new .cpp file, so CMake can find it).
```shell
$ cmake -B cmake-build-release -G Ninja
```

Build the code:(Run this every time you edit your code to compile the changes).
```shell
$ cmake --build cmake-build-release/ --target all -j 4
```
(The above is build-tool agnostic. It will use what's in the 
system - ninja, etc.)

Run the code:
```shell
$ ./cmake-build-release/executable_name
```

• Without a build tool, you would have to manually re-compile all 1,000 files (which takes forever).
• With Ninja, it looks at your folder, says "Hey, only file #43 has changed since my last build. Compiler, go compile just file #43, and then link it back into the rest of the project."

**OR**

When testing an individual file:
```shell
$ g++ -std=c++20 dummy.cpp -o dummy
```
