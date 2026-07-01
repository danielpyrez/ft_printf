*This project has been created as part of the 42 curriculum by danipere.*

# ft_printf

## Description

ft_printf is a recreation of the C standard library's `printf()` function.
The goal of this project is to understand how variadic functions work in C
and to build a small, working formatted-output engine from scratch, without
implementing the original's internal buffering mechanism.

The library exposes three functions:

```c
int ft_printf(char const *format, ...);
int ft_putstr_mod(char *st, int fd);
int print_mem(unsigned long mem);
```

It parses the format string, reads the corresponding variadic arguments,
and writes the formatted output to standard output, returning the number
of characters printed (matching the original `printf()` behavior).

The following conversions are supported:

| Conversion | Description |
|---|---|
| `%c` | Single character |
| `%s` | String |
| `%p` | Pointer address, in hexadecimal format |
| `%d` | Signed decimal integer |
| `%i` | Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` | Unsigned hexadecimal integer, lowercase |
| `%X` | Unsigned hexadecimal integer, uppercase |
| `%%` | A literal percent sign |

## Instructions

### Compilation

The project builds a static library named `libftprintf.a`.

```bash
make        # compiles all source files and builds libftprintf.a
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # fclean + make
```

All source files are compiled with `-Wall -Wextra -Werror`, and the
library is generated with `ar` at the root of the repository.

### Usage in another project

Copy the project directory into your project and link against it in your
`Makefile`:

```makefile
PRINTF_DIR = ft_printf
PRINTF_LIB = $(PRINTF_DIR)/libftprintf.a

$(PRINTF_LIB):
	make -C $(PRINTF_DIR)

$(NAME): $(PRINTF_LIB) $(OBJS)
	$(CC) $(OBJS) -L$(PRINTF_DIR) -lftprintf -o $(NAME)
```

Then include the header and call the function:

```c
#include "ft_printf.h"

ft_printf("Hello %s, you are %d years old (%p)\n", name, age, &age);
```

## Algorithm and data structure choices

`ft_printf` is built around three sequential stages, applied once per
conversion specifier found in the format string:

1. **Parsing.** The format string is scanned character by character. Each
   regular character is written directly to standard output. When a `%` is
   encountered, the following character is read to identify which
   conversion handler should be called. No flags, width, or precision
   parsing is implemented, since the subject restricts the project to the
   nine specifiers listed above (`cspdiuxX%`).

2. **Argument retrieval.** A single `va_list` is used throughout the call,
   initialized with `va_start` and read with `va_arg`. Each conversion
   handler consumes exactly one argument of the appropriate type
   (`char`, `char *`, `void *`, `int`, or `unsigned int`), so the order of
   reads always matches the order of conversions in the format string.

3. **Conversion and output.** Each specifier has its own static handler
   function (e.g. `ft_print_char`, `ft_print_str`, `ft_print_ptr`,
   `ft_print_nbr`, `ft_print_unsigned`, `ft_print_hex`). Numeric
   conversions reuse a shared base-conversion routine, since `%d`/`%i`,
   `%u`, `%x`, and `%X` all boil down to printing a number in a given
   base with an optional sign and case. This avoids duplicating digit-
   extraction logic across handlers.

No intermediate buffer is built up for the whole output; each piece is
written directly via `write()` as it's produced, since the subject
explicitly forbids reimplementing the original's internal buffering
behavior. A running character counter is incremented after every `write`
call so the function can return the correct total, mirroring the return
value of the original `printf()`.

This design was chosen because it keeps each conversion isolated and
testable on its own, keeps the main parsing loop simple (look at the
character after `%`, dispatch to a handler), and avoids unnecessary heap
allocations: only `%s`-style operations that legitimately need it (none,
in this case, since strings are written directly) would require dynamic
memory, so the library relies purely on `write`, `malloc`/`free` where
needed by helper functions from `libft`, and the variadic-argument macros
authorized by the subject.

## Resources

- [Linux man page for `printf(3)`](https://man7.org/linux/man-pages/man3/printf.3.html) — reference for expected output formatting per conversion.
- [`stdarg.h` documentation](https://en.cppreference.com/w/c/variadic) — reference for `va_start`, `va_arg`, `va_copy`, and `va_end`.
- [42 Norm v4](https://github.com/42School/norminette) — coding style enforced on every file of the project.

**Use of AI:** No AI tool was used to generate or write any part of the
source code for this project, in line with 42's pedagogical approach,
which emphasizes building real, independently-acquired skills through
research, documentation, and peer learning rather than AI-generated
solutions.