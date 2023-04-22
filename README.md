# Infix To postfix

Convert infix notation to postfix notation with the shunting yard algorithm.

## Examples

```text
input: 10 + 5
output: 10 5 +

input: 4 * -5
output: 4 -5 *

input: 25 - 3 * 10 / 2
output: 25 3 10 * 2 / -

input: 16 - 2 * ( 3 * 18 / 2 )
output: 16 2 3 18 * 2 / * -

input: ( 6 + -9 - -2 ) * ( 4 + 3 - 11 )
output: 6 -9 + -2 - 4 3 + 11 - *
```
