# push_swap

*As part of the 42 curriculum*

## Description

**push_swap** is a project from the 42 School curriculum. The goal is to sort a list of integers using two stacks, `a` and `b`, and a limited set of operations.

The challenge is to sort the numbers in ascending order while minimizing the number of operations performed.

This project introduces algorithm design, stack manipulation, sorting strategies, and optimization.

## Authors

- **mohasnao**
- **mluvisot**

## Features

- Sorts integers using two stacks.
- Supports stack operations such as swapping, pushing, and rotating.
- Checks input validity, including duplicate values and invalid arguments.
- Uses different sorting strategies depending on the input size and disorder.
- Aims to minimize the number of operations.
- Supports benchmark mode to display sorting statistics.

## Available Operations

| Operation | Description |
|---|---|
| `sa` | Swaps the first two elements of stack A. |
| `sb` | Swaps the first two elements of stack B. |
| `ss` | Performs `sa` and `sb` simultaneously. |
| `pa` | Pushes the top element of B onto A. |
| `pb` | Pushes the top element of A onto B. |
| `ra` | Rotates stack A upwards. |
| `rb` | Rotates stack B upwards. |
| `rr` | Rotates both stacks upwards. |
| `rra` | Rotates stack A downwards. |
| `rrb` | Rotates stack B downwards. |
| `rrr` | Rotates both stacks downwards. |

## Sorting Strategies

The project uses different approaches depending on the number of elements and the selected mode.

- **Small sorting:** dedicated algorithms for small stacks.
- **Simple strategy:** a basic sorting approach.
- **Medium strategy:** uses indexes and chunks to move elements between stacks.
- **Complex strategy:** designed to handle larger inputs efficiently.
- **Adaptive strategy:** selects a strategy according to the disorder of the input.

## Installation

Clone the repository and compile the project:

```bash
git clone <repository-url>
cd push_swap
make
```

This generates the `push_swap` executable.

## Usage

Run the program with a list of integers:

```bash
./push_swap 4 2 7 1 3
```

The program prints the stack operations needed to sort the numbers.

You can also provide the numbers as a single quoted argument:

```bash
./push_swap "4 2 7 1 3"
```

### Benchmark Mode

If benchmark mode is supported by your build, use:

```bash
./push_swap --bench 4 2 7 1 3
```

The benchmark displays statistics about the sorting process.

### Testing the Result

To check whether the output correctly sorts the stack, use the checker provided by your 42 environment, if available:

```bash
ARG="4 2 7 1 3"
./push_swap $ARG | ./checker_linux $ARG
```

Replace `checker_linux` with the checker executable available on your system.

## Makefile

The project provides the following standard Makefile targets:

- `make`: compiles the project.
- `make clean`: removes object files.
- `make fclean`: removes object files and the executable.
- `make re`: recompiles the project from scratch.

## Project Structure

The project is organized into source files and headers.

- `src/`: main source files and sorting algorithms.
- `includes/`: project headers.
- `libft/`: utility library, if included in the repository.
- `Makefile`: compilation rules.

*Adapt this section if your actual directory structure differs.*

## Learning Objectives

Through this project, we worked on:

- Algorithm design and optimization.
- Linked lists and stack data structures.
- Sorting and index-based algorithms.
- Memory management in C.
- Input validation and error handling.
- Collaborative development and debugging.

## License

This project was developed for educational purposes as part of the 42 curriculum.
