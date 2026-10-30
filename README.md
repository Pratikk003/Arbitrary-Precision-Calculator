# Arbitrary Precision Calculator (APC) in C

A command-line calculator that works on integers of **any length**, far beyond
what `int` or `long long` can hold. Each number is stored as a doubly linked
list with one digit per node, and the arithmetic is done digit by digit, the
same way you would on paper.

Supported operations: **addition, subtraction, multiplication, division
(with remainder)**, including negative numbers.

## Build

Requires `gcc` and `make`.

```bash
make          # builds ./apc
make demo     # builds and runs a few example calculations
make clean    # removes object files and the executable
```

## Usage

```bash
./apc <operand1> <operator> <operand2>
```

Operators: `+`  `-`  `*`  `/`

The shell treats `*` as a wildcard, so write it as `"*"` or `'*'`. You can also
use `x` instead.

### Examples

```bash
$ ./apc 123 + 456
Result    : 579

$ ./apc 100 - 250
Result    : -150

$ ./apc -12 + 5
Result    : -7

$ ./apc 99999999999999999999 x 99999999999999999999
Result    : 9999999999999999999800000000000000000001

$ ./apc 1000 / 7
Result    : 142
Remainder : 6

$ ./apc -17 / 5
Result    : -3
Remainder : -2
```

For division, the remainder takes the sign of the dividend (like C's `%`).

### Error handling

- Operands must be integers: optional `+` or `-` followed by digits only
- Invalid operators are rejected
- Division by zero is reported as an error
- Wrong number of arguments prints the usage message

## How it works

1. Each operand is validated and converted to a doubly linked list of digits
   (most significant digit at the head).
2. The magnitudes are compared, and `sign.c` decides the sign of the result and
   whether to add or subtract the magnitudes. For example, `a - b` is treated
   as `a + (-b)`.
3. The operation runs on the lists from the last node to the first, carrying
   or borrowing as needed:
   - **Addition:** digit-wise sum with carry
   - **Subtraction:** digit-wise difference with borrow (larger minus smaller)
   - **Multiplication:** multiply by each digit of the second number, shift,
     and add the partial products
   - **Division:** long division using repeated subtraction
4. The result list is printed with the correct sign, and all lists are freed.

## Project structure

| File | Purpose |
|------|---------|
| `main.c` | Argument handling and the `calculate()` driver |
| `apc.h` | Node structure and all function prototypes |
| `list.c` | Doubly linked list helpers (insert, delete, convert, print) |
| `validate.c` | Operator/operand validation and magnitude comparison |
| `sign.c` | Sign handling for the result |
| `add.c` | Addition |
| `sub.c` | Subtraction |
| `mul.c` | Multiplication |
| `div.c` | Division with remainder |
| `Makefile` | Build script |

## Limitations

- Integers only (no decimals)
- Division uses repeated subtraction, so it is slow for very large quotients
- One operation per run

---

Author: Pratik Kambire
