
*This project has been created as part of the 42 curriculum by mohasnao.*

# Libft

## Description

Libft is the first project of the 42 curriculum.

The goal of this project is to create a personal C library containing
functions that reproduce the behavior of several standard C library
functions, as well as additional useful functions.

This project helps to understand memory allocation, strings, characters,
pointers, file descriptors and linked lists.

The library is divided into three parts:

- Part 1: functions based on the standard C library.
- Part 2: additional functions for string manipulation, memory management
  and file descriptors.
- Part 3: functions for manipulating linked lists.

## Library

### Part 1 - Libc functions

The following functions are implemented:

- ft_isalpha
- ft_isdigit
- ft_isalnum
- ft_isascii
- ft_isprint
- ft_strlen
- ft_memset
- ft_bzero
- ft_memcpy
- ft_memmove
- ft_strlcpy
- ft_strlcat
- ft_toupper
- ft_tolower
- ft_strchr
- ft_strrchr
- ft_strncmp
- ft_memchr
- ft_memcmp
- ft_strnstr
- ft_atoi
- ft_calloc
- ft_strdup

### Part 2 - Additional functions

- ft_substr
- ft_strjoin
- ft_strtrim
- ft_split
- ft_itoa
- ft_strmapi
- ft_striteri
- ft_putchar_fd
- ft_putstr_fd
- ft_putendl_fd
- ft_putnbr_fd

### Part 3 - Linked lists

The linked list part contains:

- ft_lstnew
- ft_lstadd_front
- ft_lstsize
- ft_lstlast
- ft_lstadd_back
- ft_lstdelone
- ft_lstclear
- ft_lstiter
- ft_lstmap

## Technical choices

The project is written in C and follows the 42 Norm.

Dynamic memory allocation is handled using malloc and free.

The linked list functions use the following structure:

typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;

All functions are compiled with:

-Wall -Wextra -Werror

## Instructions

### Compilation

To compile the library, run:

make

This creates the `libft.a` static library.

To remove object files:

make clean

To remove object files and the library:

make fclean

To recompile everything:

make re

### Using the library

Include the header file in your C program:

#include "libft.h"

Then compile your program together with the library:

cc main.c -L. -lft

## Project structure

The project contains the following files:

- Makefile
- README.md
- libft.h
- ft_isalpha.c
- ft_isdigit.c
- ft_isalnum.c
- ft_isascii.c
- ft_isprint.c
- ft_strlen.c
- ft_memset.c
- ft_bzero.c
- ft_memcpy.c
- ft_memmove.c
- ft_strlcpy.c
- ft_strlcat.c
- ft_toupper.c
- ft_tolower.c
- ft_strchr.c
- ft_strrchr.c
- ft_strncmp.c
- ft_memchr.c
- ft_memcmp.c
- ft_strnstr.c
- ft_atoi.c
- ft_calloc.c
- ft_strdup.c
- ft_substr.c
- ft_strjoin.c
- ft_strtrim.c
- ft_split.c
- ft_itoa.c
- ft_strmapi.c
- ft_striteri.c
- ft_putchar_fd.c
- ft_putstr_fd.c
- ft_putendl_fd.c
- ft_putnbr_fd.c
- ft_lstnew.c
- ft_lstadd_front.c
- ft_lstsize.c
- ft_lstlast.c
- ft_lstadd_back.c
- ft_lstdelone.c
- ft_lstclear.c
- ft_lstiter.c
- ft_lstmap.c

## Resources

The main resources used for this project were:

- C standard library documentation
- 42 Libft subject
- `man` pages for C functions
- 42 peer discussions and explanations

### AI usage

AI was used as a learning and debugging tool during the project.

It was used to:
- understand how some functions work;
- identify bugs and memory errors;
- understand pointers and dynamic memory allocation;
- review the implementation of `ft_split`, `ft_itoa` and linked list functions;
- understand the Makefile and project structure.

The code was tested and understood before being integrated into the project.

## Conclusion

Libft is an important introduction to C programming at 42.

This project helped me improve my understanding of memory management,
pointers, strings, file descriptors and linked lists.
