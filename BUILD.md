# Build and run

## Requirements

- GCC
- GNU make
- ncursesw development files for the terminal bonus

## CLI

```sh
make
./corewar -h
./corewar champions/aster.cor champions/borealis.cor
```

The VM prints the execution trace to standard output.

## Terminal bonus

```sh
make -C bonus
./bonus/corewar \
  -a 0 -n 1 champions/aster.cor \
  -a 1024 -n 2 champions/borealis.cor \
  -a 2048 -n 3 champions/cinder.cor \
  -a 3072 -n 4 champions/drift.cor
```

Controls:

- Left and right arrows halve and double the speed.
- Up and down arrows scroll the memory view.
- Space pauses the VM; press it again to resume.
- `q` or Escape quits.

Use a wide terminal for the full layout; 200 columns by 62 rows fits the title,
champion panels, logs and the 128-column memory view.

## Compiler notes

The bundled `my_printf` library compiles with `-Werror`. GCC 15 reports the
ignored result of `write` in that library, so pass a relaxed flag when building:

```sh
make CFLAGS='-I./include -Wall -Wextra -Wno-error=unused-result -g'
make -C bonus CFLAGS='-I./include -Wall -Wextra -Wno-error=unused-result -g'
```

The bonus Makefile links with `-lcurses`. If your ncurses package only provides
`libncursesw`, override the linker flags:

```sh
make -C bonus \
  CFLAGS='-I./include -Wall -Wextra -Wno-error=unused-result -g' \
  LDFLAGS='-L./lib -lmy_printf -lncursesw'
```
