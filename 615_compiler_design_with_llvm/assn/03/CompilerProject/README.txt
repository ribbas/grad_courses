# Compiler Project C- ANTLR4 Grammar

The ANTLR4 tool was installed and ran using the instructions in the official documentations, https://github.com/antlr/antlr4/blob/master/doc/getting-started.md.

The tool and its dependencies were installed on the system using `apt`. The following commands were used to generate the java and class files:

```
antlr4 Cminus.g4
javac Cminus*.java
```

The generated files are moved to `CompilerProject`.

Once the files were generated, ANTLR4's gui.TestRig was used to generate the tree and token files. The tree outputs are saved as C-Input-X-Tree.txt and the token outputs as C-Input-X-Tokens.txt, with C-Input-X corresponding to the files in `C-Input-files/`.

The following command was used to generate the tree file for each of the input files in `C-Input-files`:
```
grun Cminus program -tree < C-Input-files/C-Input-X.txt > C-Input-X-Tree.txt
```

The following command was used to generate the token file for each of the input files in `C-Input-files`:
```
grun Cminus program -tokens < C-Input-files/C-Input-X.txt > C-Input-X-Tokens.txt
```

The commonly used commands for this assignment were consolidated into the attached Makefile.

## System

The target machine used was an Ubuntu 20.04 64-bit virtual machine. The Linux kernel version is 5.13.0-28-generic. The following output is generated from running the command `uname -orm`:

```
5.13.0-28-generic x86_64 GNU/Linux
```
