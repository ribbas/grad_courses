# Homework 1: Scanner

## scanner.cpp

The C++ script, `scanner.cpp`, consists of all the functions and data structures necessary to implement the assignment. The contents of the input file are read in and passed into tokenizing functions where the string is split using whitespace and special characters as delimiters. The split substrings along with the delimiters are stored as Token objects in a std::vector container. The Token object is a simple struct that contains the token names and types as attributes. The struct also provides a member method, `std::string to_string(void)`, that formats the attributes of the Token in the `("name", type)` tuple format specified by the prompt.

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

The build files including the binary executable are located in `.build`.

## Logical tests

The script also generates statistics on the number of logical tests, i.e if, else, while, for, switch, etc. statements. When ran on the provided sample input file, 98 tests were made. Additionally, statistics on the number of comparisons made on the string to determine the token types were generated. All string comparisons were done without the use of any std::string methods for an accurate count. When ran on the provided sample input file, 900 character comparisons were made.
