# RangeMap

RangeMap is a data structure to handle frequency distributions.

I published this project because I didn't find any comparable structure which
can update symbol weights in O(log(N)) time. When I spend my time with
arithmetic coding I was searching for good implementations of frequency tables
in free compression software but found nothing. So I invented my own data
structure to solve the problem.

| Row | Left | Width | Range
|----:|-----:|------:|:---------:
|   0 |    0 |     2 |   0 - 1
|   1 |    2 |    20 |   2 - 21
|   2 |   22 |    38 |  22 - 59
|   3 |   60 |    40 |  60 - 99
|   4 |  100 |    19 | 100 - 118
|   5 |  119 |     2 | 119 - 120
|   6 |  121 |     3 | 121 - 123
|   7 |  124 |     1 | 124 - 124

In this example the offset 42 would return the row number 2 and the first
offset 22.

## Internals

The table in the example will be stored like this.

| Row | Internal
|:----|:--------
| 0   |      2
| 1   |  <s>20</s>     22
| 2   |     38
| 3   |  <s>40</s>  <s>78</s>   100
| 4   |     19
| 5   |   <s>2</s>     21
| 6   |      3
| 7   |   <s>1</s>  <s>4</s>  <s>25</s>     125

Every second row is a sum. Every second sum will be added up and so on. No
additional memory is needed. All operations are done with the internal values.

For example to get the left of the sixth row we calculate `100 + 21` instead of
`(2 + 20 + 38 + 40) + (19 + 2)`. Searching looks like a binary search with
extra additions in 50% of the steps.

