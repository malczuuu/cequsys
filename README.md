# CEquSys

Solving system of linear equations.

Loads matrix and vector for the system of linear equation to solve from `input.txt` file located in working directory.

## Usage instructions

* Using CMake

    ```bash
    $ cmake .
    $ make
    $ ./cequsys
    ```

* Using GCC (since it's just one file)

    ```bash
    $ g++ cequsys.cpp -o cequsys
    $ ./cequsys
    ```

Generate equation system with following pattern with command `./gen.py {size} > input.txt`.

```text
2 2 0 0 0 0 ; 2
2 2 2 0 0 0 ; 2
0 2 2 2 0 0 ; 2
0 0 2 2 2 0 ; 2
0 0 0 2 2 2 ; 2
0 0 0 0 2 2 ; 2
```

**Note** that it's possible to use fractions using `/` and without spaces between.

```text
1/3 1/3   0   0   0   0 ; 1/3
1/3 1/3 1/3   0   0   0 ; 1/3
  0 1/3 1/3 1/3   0   0 ; 1/3
  0   0 1/3 1/3 1/3   0 ; 1/3
  0   0   0 1/3 1/3 1/3 ; 1/3
  0   0   0   0 1/3 1/3 ; 1/3
```

## Code style

Code should be formatted with `./format.sh` script (which internally uses `clang-format`).
