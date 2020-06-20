#!/usr/bin/env python3

import sys
import random

if __name__ == '__main__':
    size = int(sys.argv[1]) if len(sys.argv) > 1 else 10

    num = random.randint(1, 9)

    for i in range(0, size):
        if i == 0:
            print(f'{num} {num}' + (size - 2) * ' 0' + f' ; {num}')
        elif i == size - 1:
            print((size - 2) * '0 ' + f'{num} {num} ; {num}')
        else:
            print((i - 1) * '0 ' + f'{num} {num} {num}' + (size - 2 - i) * ' 0' + f' ; {num}')
