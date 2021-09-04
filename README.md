# lc3-vm

I created this project to brush up on my binary arithmetic and low-level programming skills. All credit to the tutorial goes to https://justinmeiners.github.io/lc3-vm. I decided to structure my code slightly differently and make it compatible with both windows and unix. 

# About

This VM simulates an LC-3 CPU. LC-3 is an educational version of the x86 architecture which contains fewer instructions. It uses arrays to simulate the storage hardware specified by the LC-3 ISA, namely the 11 registers and 128kB main memory. This program works by loading in an assembled instruction set and updating the program counter to point here. From there it enters a loop wherein instructions are read and executed until termination.

# Screenshots

![greetings](greet.png)

![playing now](play.png)

# Installation
Create a build directory and navigate to it. Then build/compile the code. Here's what it looks like on linux/mac:
```
$ git clone https://github.com/ross-m/lc3-vm
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```

# Usage

I've included several programs in the ```programs``` directory to demonstrate the functionality of my VM. To run one of these, issue the following commands:
```
$ cd build
$ ./lc3-vm ../programs/xxx.obj
```
