# MC/DC

Implementation of an automatic tool for the MC/DC code coverage in C (and first approach in Python).
Calculation is iterative to be light in memory and it was optimized to use multiple threads (defined by the user).

## Getting Started

These instructions will let you know how to install and use the tool on your machine.
For the installation, it will be assumed that you are in an Unix based system.

### Prerequisites

What things you need to install the software and how to install them

```
gcc
make
```

### Installing

First of all, clone the repository to your local machine

```
git clone https://github.com/gonced8/mcdc.git
```

Go to the folder with the C program

```
cd mcdc/C
```

Build the source code in your machine

```
make clean && make all
```

## Running

To setup the tool, edit the file
```
src/function.c
```
You can change the number of threads, and the function you're analyzing (be careful to also change the number of arguments, accordingly).


To execute, run the command
```
make run
```

## Built With

* C
* Python 3

## Authors

* **Gonçalo Raposo** - [gonced8](https://github.com/gonced8)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
