*This project has been created as part of the 42 curriculum by mohasnao, mluvisot.*

# push_swap

## Description

**push_swap** sorts a list of integers using two stacks, `a` and `b`, and a restricted set of operations. The program does not print the sorted numbers: it prints the **sequence of operations** that sorts stack `a` in ascending order (smallest number on top), with as few operations as possible.

The goal of the project is to work with algorithmic complexity in a concrete way. Every cost in this README is counted in **number of Push_swap operations generated**, not in CPU time.

The binary contains four strategies:

| Strategy | Flag | Technique | Class (in operations) |
|---|---|---|---|
| Simple | `--simple` | Min-extraction (selection sort adaptation) | O(n²) |
| Medium | `--medium` | Chunk-based sorting with √n-sized chunks | O(n√n) |
| Complex | `--complex` | LSD binary radix sort on normalized indices | O(n log n) |
| Adaptive | `--adaptive` (default) | Picks one of the above using the measured disorder | depends on regime |

### Operations

| Operation | Effect |
|---|---|
| `sa` / `sb` | Swap the first two elements of `a` / `b` (no-op if fewer than 2) |
| `ss` | `sa` and `sb` at the same time |
| `pa` / `pb` | Move the top of `b` onto `a` / the top of `a` onto `b` (no-op if source is empty) |
| `ra` / `rb` | Rotate `a` / `b` up: the first element becomes the last |
| `rr` | `ra` and `rb` at the same time |
| `rra` / `rrb` | Reverse-rotate `a` / `b`: the last element becomes the first |
| `rrr` | `rra` and `rrb` at the same time |

An operation that has no effect (for example `sa` on a stack of one element) is **not printed** and not counted.

## Instructions

### Compilation

```bash
make        # builds libft, then push_swap
make clean  # removes object files (project and libft)
make fclean # removes object files, libft.a and push_swap
make re     # fclean + all
```

Compiled with `cc -Wall -Wextra -Werror`. The Makefile does not relink.

### Usage

```bash
./push_swap [--simple | --medium | --complex | --adaptive] [--bench] <integers...>
```

- The first integer is the **top** of stack `a`.
- Each integer must be passed as a **separate argument**. A single quoted string such as `"3 2 1"` is not split and is treated as an invalid argument (`Error`).
- To pass a list stored in a variable, the shell has to split it into separate arguments. **This depends on your shell:**

  ```bash
  # bash: an unquoted variable is split on spaces
  ARG="4 67 3 87 23"; ./push_swap $ARG
  ```

  ```zsh
  # zsh: unquoted variables are NOT split by default.
  # "./push_swap $ARG" passes ONE argument and prints Error.
  # Use ${=ARG} to force the split:
  ARG="4 67 3 87 23"; ./push_swap ${=ARG}
  ```

  Check your shell with `echo $SHELL`. In zsh you can also run `bash` first and use the bash syntax.

- Options must come **before** the integers. Each option can appear at most once, and at most one strategy can be selected.
- Without a strategy flag, `--adaptive` is used.
- With no integers, or with a stack that is already sorted, nothing is printed.

### Error handling

`Error\n` is printed on **stderr** (nothing on stdout, exit code 1) when:

- an argument is not an integer (`1 a 3`, `""`, `-`, `+`, `1-2`);
- an integer is outside the `int` range (`2147483648`, `-2147483649`);
- a value appears twice (`1 2 2`, `0 -0`);
- an option is unknown, repeated, or two strategies are given (`--foo`, `--simple --medium`);
- a memory allocation fails.

Accepted forms: an optional sign followed by digits (`+5`, `-3`, `007`), with at most 11 characters in total.

### Benchmark mode

`--bench` prints statistics on **stderr** after sorting. The operations stay on stdout, so the output can still be piped into a checker.

```bash
$ ./push_swap --bench $(shuf -i 0-9999 -n 100) > /dev/null
[bench] disorder: 53.70%
[bench] strategy: Adaptive -> Complex O(n log n)
[bench] total_ops: 1084
[bench] sa  0
[bench] sb  0
[bench] ss  0
[bench] pa  384
[bench] pb  384
[bench] ra  316
[bench] rb  0
[bench] rr  0
[bench] rra 0
[bench] rrb 0
[bench] rrr 0
```

### Checking the result

```bash
# bash
ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' ')
./push_swap $ARG | ./checker_linux $ARG      # OK
./push_swap $ARG | wc -l                     # number of operations
./push_swap --complex $ARG | ./checker_linux $ARG
```

```zsh
# zsh: same commands with ${=ARG}
ARG=$(shuf -i 0-9999 -n 500 | tr '\n' ' ')
./push_swap ${=ARG} | ./checker_linux ${=ARG}
./push_swap ${=ARG} | wc -l
./push_swap --complex ${=ARG} | ./checker_linux ${=ARG}
```

`$(shuf …)` written directly on the command line (`./push_swap $(shuf -i 0-9999 -n 500)`) is split in both shells.

## Algorithms

### Preparation (shared by all strategies)

1. **Parsing.** Arguments are validated and stored in a singly linked list (`t_node`: `value`, `index`, `next`). The head of the list is the top of the stack.
2. **Disorder.** Before any move, `compute_disorder` counts every pair `(i, j)` with `i` before `j` and `a[i] > a[j]` (an *inversion*), and divides by the number of pairs `n(n-1)/2`. The result is between 0 (sorted) and 1 (reversed). This costs O(n²) comparisons but **zero operations**.
3. **Normalization.** Each value gets its rank `index` in `0 … n-1` (`init_rank`). The algorithms work on these indices, which removes negative numbers and large gaps (needed for radix sort).
4. If the disorder is 0, the stack is already sorted and no operation is printed.

### 1. Simple: min-extraction, O(n²)

**Idea.** Selection sort adapted to two stacks: repeatedly bring the smallest remaining element to the top of `a` and push it to `b`. `b` then holds the elements in decreasing order from the top, so pushing everything back with `pa` leaves `a` sorted.

**Steps.** For `index = 0, 1, …, n-1`:
- find the position `p` of `index` in `a` (size `k`);
- if `p ≤ k/2`, do `p` × `ra`, otherwise `k - p` × `rra` (shortest direction);
- `pb`.

Then `n` × `pa`.

**Bound.** The extraction with `k` elements left costs at most `k/2` rotations + 1 push. Total ≤ Σ(k/2 + 1) + n ≈ **n²/4 + 2n** → O(n²). Measured: ~1500–1650 operations for 100 random numbers, ~31 000 for 500.

**Space.** The two stacks hold `n` nodes in total. Extra memory: O(1).

### 2. Medium: chunk sorting, O(n√n)

**Idea.** Instead of extracting elements one by one, move them to `b` in groups (chunks) of consecutive indices, then bring them back in order. `b` stays roughly sorted chunk by chunk, so the next element to bring back is never far from the top or the bottom of `b`.

**Chunk size.** `c = s + s/2`, where `s` is the smallest integer with `s² ≥ n` (so `c ≈ 1.5√n`: 15 for 100 numbers, 34 for 500). There are about `n/c ≈ (2/3)√n` chunks.

**Phase 1: pushing to `b` (`push_chunk`).** For the window of indices `[0, max_index]`, with `max_index` growing by `c` at each round:
- scan `a` once: if the top is in the window, `pb`, otherwise `ra`;
- after a `pb`, if the element belongs to the lower half of the current chunk (`index < max_index - c/2`), `rb` sends it to the bottom of `b`.

The upper half of each chunk stays near the top of `b`, the lower half goes to the bottom. This keeps big and small values apart and shortens phase 2.

**Phase 2: bringing back (`sort_back`).** For `max = n-1` down to `0`: find `max` in `b`, rotate `b` the short way (`rb` or `rrb`), then `pa`.

**Bound.**
- Phase 1: each round scans `a` at most once, with at most 2 operations per element (`pb` + `rb`, or `ra`). That's ≤ 2n operations per round × ~`n/c` rounds → O(n · √n).
- Phase 2: thanks to the layout from phase 1, the current maximum is always in the upper half of the most recent chunk still in `b` (near the top) or in its lower half (near the bottom). It is therefore at most O(c) = O(√n) positions from one end. `n` extractions × O(√n) → O(n√n).
- Total: **O(n√n)**. Measured: ~700 operations for 100 random numbers, ~6 300 for 500.

**Space.** O(n) for the stacks, O(1) extra.

### 3. Complex: LSD radix sort, O(n log n)

**Idea.** Sort the normalized indices bit by bit, starting from the least significant bit. Each pass is a stable partition on one bit: elements whose bit is 0 go to `b`, the others stay in `a`; then `b` is pushed back on top.

**Steps.**
- `bits = ⌈log₂ n⌉`, the number of bits needed to write `n - 1` (`get_nbr_bits`).
- For each bit from 0 to `bits - 1`: look at the `n` elements of `a` once; if the bit is 0, `pb`, otherwise `ra`. Then `pa` until `b` is empty.

Because each pass is stable, after the last pass the indices are fully sorted.

**Bound.** Each pass costs exactly `n` operations (`pb` or `ra`), plus one `pa` per element that went to `b`, so ≤ 2n. Total ≤ **2n⌈log₂ n⌉** → O(n log n). Measured: 1 084 operations for 100 numbers (7 bits), 6 784 for 500 (9 bits).

**Space.** O(n) for the stacks, O(1) extra.

### 4. Adaptive (default)

**Regimes.**

| Measured disorder | Method used | Class |
|---|---|---|
| `disorder < 0.2` | Simple (min-extraction) | O(n²) |
| `0.2 ≤ disorder < 0.5` | Medium (chunks) | O(n√n) |
| `disorder ≥ 0.5` | Complex (radix) | O(n log n) |

On top of that, for **n ≤ 5** the adaptive mode uses dedicated small sorts, because constants matter more than the asymptotic class at this size:
- `n = 2`: one `sa`;
- `n = 3`: `sort_three` handles the 6 cases directly, with at most 2 operations;
- `n = 4` or `5`: push the minimum to `b` (shortest rotation) until 3 elements remain, `sort_three`, then `pa`. At most 10 operations over all 120 permutations of 5 elements.

**Why these thresholds.** The thresholds 0.2 and 0.5 come from the subject, which fixes the complexity class required in each regime. Our reasoning for the mapping:
- A **random** input has a disorder close to 0.5, so it falls in the medium or high regime and gets an O(n√n) or O(n log n) method. These are the inputs measured by the benchmark (100 and 500 numbers).
- With **low disorder** (< 0.2), most elements are already in order relative to each other, so the minimum is usually close to the top of `a` and each extraction needs few rotations. The quadratic method is allowed in this regime. Its cost never drops below `2n`, though, because every element goes through `b` once.
- **Above 0.5**, the input is as messy as a random one or worse. Radix sort has a cost that does not depend on the order of the input (exactly `2n⌈log₂ n⌉` at most), which gives a guaranteed upper bound.

**Complexity argument.** The disorder is computed with 0 operations. Each regime then calls one of the three strategies above, so the number of operations is bounded by that strategy's bound: O(n²), O(n√n) or O(n log n). Space is O(n) in every regime (two linked lists holding `n` nodes in total, plus 11 counters for the benchmark).

### Measured performance

Random inputs, 20 runs each, checked with a checker:

| Input size | Adaptive (mean / worst) | Simple | Medium | Complex | Required to pass |
|---|---|---|---|---|---|
| 100 | 889 / 1 084 | ~1 600 | ~700 | 1 084 | < 2 000 |
| 500 | 6 513 / 6 784 | ~31 000 | ~6 300 | 6 784 | < 12 000 |

## Project structure

```
.
├── Makefile
├── README.md
├── main.c                    # entry point: options, parsing, start, free
├── includes/push_swap.h      # t_node and prototypes
├── libft/                    # our libft (built by the main Makefile)
└── src/
    ├── operations/           # sa sb ss pa pb ra rb rr rra rrb rrr, disorder
    ├── algo/                 # simple, medium, complex, small sorts (3 and 5)
    └── utils/                # parsing, errors, ranks, strategy start, bench
```

## Contributions

<!-- TODO: check and complete this section together before the defense -->

- **mohasnao**: project setup, stack operations (`sa` … `rrr`), first version of argument parsing and of `compute_disorder`, small sorts (`sort_three`, `sort_five`), benchmark output, README.
- **mluvisot**: radix sort (complex strategy), medium (chunk) strategy and its corrections, simple strategy, strategy selection (`ft_start`), operation counter for `--bench`, Norm compliance, Makefile.
- **Together**: choice of the algorithms and thresholds, testing, debugging.

Both of us understand and can explain every part of the code.

## Resources

- [Big O notation](https://en.wikipedia.org/wiki/Big_O_notation): how to state the complexity classes used above.
- [Inversion (discrete mathematics)](https://en.wikipedia.org/wiki/Inversion_(discrete_mathematics)): the disorder metric is the number of inversions divided by the number of pairs.
- [Selection sort](https://en.wikipedia.org/wiki/Selection_sort): basis of the simple strategy.
- [Radix sort](https://en.wikipedia.org/wiki/Radix_sort): basis of the complex strategy (LSD variant).
- [Bucket sort](https://en.wikipedia.org/wiki/Bucket_sort): the chunk strategy follows the same idea of grouping values by range.
- `man 3 malloc`, `man 2 write`, and the 42 Norm (v4.1).

### Use of AI

- **Code review and tests**: an AI assistant (Claude) reviewed the project against the subject and the Norm, and wrote a test script (error cases, all permutations of 5 elements, benchmarks on 100 and 500 numbers, valgrind). The script is not part of the submission. We used its results to fix the README and the issues it found.
- **README**: the structure and the complexity explanations of this README were drafted with AI from our code, then checked and corrected by us.
- **Algorithms and code**: [to complete: for example "no AI-generated code; AI was used to explain radix sort and to compare chunk sizes"].