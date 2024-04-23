## The dining philosphers

the dining philosophers is a problem used to introduce concurrent programming. It puts us in the following situation: 

5 philosophers are sitting around a round table with each of them having a plate of pasta in front of them and a fork on each side. The philosophers can either eat or think. To eat, they need to use the ***2*** forks that are beside their plate. They need to finish all of their pasta while also avoiding starvation due to fork scarcity.

This is a great way to illustrate synchronization issues and concurrent programming algorithms.

### The program

This is a simple implementation of the problem using `pthread` in C. It abides by the following rules:

- There can be any number of philosophers as long as there are more than 1.
- A philosopher takes **1 second** to eat.
- If a philosopher does not eat in **5 seconds**, he starves.
- Once a philosopher finishes eating all his plates, he leaves and is out of the program.

Each philosopher is contained in his own thread and forks are managed using mutexes.

### Dependencies

- [GNU Compiler Collection](https://gcc.gnu.org/) (11.4.0+)
- [GNU Make](https://www.gnu.org/software/make/) (4.3+)

### Usage

Use `make` at the root of the repository to build the binary:

```sh
make
```

You can then start the program like the following:

```sh
./dining-philosophers MEMBERS PLATES
    MEMBERS Numbers of philosophers (and forks)
    PLATES  Numbers of plates per philosopher
```
