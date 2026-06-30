# get_next_line

A C function that reads a line from a file descriptor, one line at a time.

## Description

`get_next_line` returns the next line from a file descriptor, including the trailing newline character (`\n`) when present. Successive calls read through the file line by line until EOF.

## Features

- **Mandatory** — single file descriptor
- **Bonus** — multiple file descriptors (up to 4096) managed simultaneously
- Configurable buffer size at compile time via `-D BUFFER_SIZE=N`
- No external dependencies beyond standard libc
- Memory safe — no leaks, no undefined behavior

## Files

| File | Description |
|------|-------------|
| `get_next_line.c` | Core logic (single FD) |
| `get_next_line.h` | Header (single FD) |
| `get_next_line_utils.c` | Helper functions (single FD) |
| `get_next_line_bonus.c` | Core logic (multiple FDs) |
| `get_next_line_bonus.h` | Header (multiple FDs) |
| `get_next_line_utils_bonus.c` | Helper functions (multiple FDs) |

## Usage

### Compilation

```c
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

### Example

```c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int  fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Buffer Size

Define `BUFFER_SIZE` at compile time (default: 42 if unspecified):

```c
cc -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c
```

## Functions

### Public

| Function | Prototype | Description |
|----------|-----------|-------------|
| `get_next_line` | `char *get_next_line(int fd)` | Returns the next line from `fd`, or `NULL` on error/EOF |

### Internal Helpers

| Function | Description |
|----------|-------------|
| `ft_strlen` | String length |
| `ft_strchr` | Locate character in string |
| `ft_strdup` | Duplicate a string |
| `ft_substr` | Extract substring |
| `ft_strjoin` | Concatenate two strings (frees first) |
| `free_and_return` | Free a pointer and return `NULL` |

## Algorithm

1. Read chunks of `BUFFER_SIZE` bytes until a newline or EOF is found
2. Extract the line (including `\n` if present)
3. Save any leftover data in a static variable for the next call
4. Return the extracted line

For the bonus version, a static array of 4096 pointers handles multiple file descriptors simultaneously.

## Norminette

Passes the 42 Norminette v3 style checker.
