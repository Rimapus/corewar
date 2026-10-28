# Demo champions

Four Redcode programs used in the screenshots. Each one stays alive and paints a
different pattern in the shared memory.

| File | Number | Load address | Behavior |
| :--- | ---: | ---: | :--- |
| `aster.cor` | 1 | 0 | Dense alternating ribbon |
| `borealis.cor` | 2 | 1024 | Moving ladder of values |
| `cinder.cor` | 3 | 2048 | Three forks and a painted ring |
| `drift.cor` | 4 | 3072 | Six spaced stripes with drifting values |

Load them with the ncurses bonus:

```sh
./bonus/corewar \
  -a 0 -n 1 champions/aster.cor \
  -a 1024 -n 2 champions/borealis.cor \
  -a 2048 -n 3 champions/cinder.cor \
  -a 3072 -n 4 champions/drift.cor
```
