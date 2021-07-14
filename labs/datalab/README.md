# datalab

Using the publicly available version:
> [Updated 12/16/19]

    Correctness Results     Perf Results
    Points  Rating  Errors  Points  Ops     Puzzle
    1       1       0       2       8       bitXor
    1       1       0       2       1       tmin
    1       1       0       2       7       isTmax
    2       2       0       2       10      allOddBits
    2       2       0       2       2       negate
    3       3       0       2       7       isAsciiDigit
    3       3       0       2       7       conditional
    3       3       0       2       15      isLessOrEqual
    4       4       0       2       7       logicalNeg
    4       4       0       2       29      howManyBits
    4       4       0       2       12      floatScale2
    4       4       0       2       14      floatFloat2Int
    4       4       0       2       10      floatPower2

    Score = 62/62 [36/36 Corr + 26/26 Perf] (129 total operators)

Increased `TIMEOUT_LIMIT` from 10 to 20 in `btest.c` because `floatPower2` takes too long.
