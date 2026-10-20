# Learnings

## Structured Text basics

```
PROGRAM main
    VAR
        start_button : BOOL;
        pump_running : BOOL;
    END_VAR

    pump_running := start_button;
END_PROGRAM
```

- `PROGRAM ... END_PROGRAM` — a named block of logic.
- `VAR ... END_VAR` — variable declarations. Everything is typed and declared up front.
- `BOOL` — boolean type. Other base types: `INT`, `REAL` (float), `TIME`.
- `:=` is assignment. `=` is comparison, not assignment.

## Scan cycle

A PLC runs its program in a loop, not as a function you call once:

1. Read all inputs (frozen for this cycle).
2. Run the program once, top to bottom.
3. Write all outputs.
4. Repeat, every few milliseconds.

No event loop or callbacks to write yourself — the runtime loops for you. The code is just one pass through the logic.

## Compiling Structured Text with matiec

`matiec` reads a `.st` file and translates it into C code — the same role a C compiler plays for C, one level up. It's the actual compiler used inside OpenPLC, a real open-source PLC runtime.

Built from source (https://github.com/beremiz/matiec), kept outside the project at `~/tools/matiec` since it's a third-party tool, not project code.

Command used to compile `plc/main.st`:

```
~/tools/matiec/iec2c -I ~/tools/matiec/lib -T plc/build plc/main.st
```

- `-I ~/tools/matiec/lib` — points matiec at its own standard library file it needs to run.
- `-T plc/build` — writes the generated C code into `plc/build/` inside the project.
- `plc/main.st` — the input file.

Output: `plc/build/POUS.c`, `POUS.h`, `GLOBALS.h`, `LOCATED_VARIABLES.h`. `POUS.c` contains the generated C for our one line of logic:

```c
__SET_VAR(data__->,PUMP_RUNNING,,__GET_VAR(data__->START_BUTTON,));
```

That's the C equivalent of `pump_running := start_button;`.
