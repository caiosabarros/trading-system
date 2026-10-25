# C++ Trading System

I'll start with some catching up on C++ language and then start
the project end-to-end.

## Workflow

Compiling a Specific Folder

Navigate into the folder: cd folder_name

Configure the project (only needed once): cmake -B build -G Ninja

Compile the code: ninja -C build

**OR**

When testing an individual file:
```shell
$ g++ -std=c++20 dummy.cpp -o dummy
```
