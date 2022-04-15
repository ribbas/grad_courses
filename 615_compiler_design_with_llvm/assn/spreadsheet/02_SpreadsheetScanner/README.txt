# Homework 2: Spreadsheet Scanner

## Modifications

The following modifications were made to achieve the requirements:

1. The files SS_Cell.h and Token.h were included in Scanner.h to resolve errors caused by missing headers. Prototypes for functions implemented in Scanner.cpp were added in the file as well. The following functions were added:
```
void parseText(char*& ch, SS_Cell* cell);
void parseNumber(char*& ch, SS_Cell* cell);

int getHwIndex(char ch);
void lstrip(char*& ch);

Token* getToken(char*& ch);
```

2. The aforementioned functions were implemented in Scanner.cpp.

## Compilation

The attached CMakeLists.txt was used to compile the assignment files. The following are the version numbers of the tools used:

| Tool    | Version |
| ------- | ------- |
| Clang++ | 13.0.0  |
| CMake   | 3.22.2  |

The target machine used was an Ubuntu 20.04 64-bit virtual machine. The Linux kernel version is 5.13.0-28-generic. The following is a snippet of the output generated from `uname -a`:

```
Linux ribbas-virtual-machine 5.13.0-28-generic #31~20.04.1-Ubuntu SMP Wed Jan 19 14:08:10 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
```
