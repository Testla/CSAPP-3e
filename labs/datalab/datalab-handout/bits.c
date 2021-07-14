/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // x ^ y = (~x & y) | (x & ~y)
  // a | b = ~(~a & ~b)
  int a = ~x & y;
  int b = x & ~y;
  int result = ~(~a & ~b);
  return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // Tmin is 0x80000000.
  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // xor-ing x + 1 sets the lowest 0 to 1.
  // However, for x ^ (x + 1) == -1, both -1 and Tmax will be true.
  // So we need to exclude -1 using ~x != 0.
  // !(a | b) means both a and b equals 0
  return !(~(x ^ (x + 1)) | !~x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // And all the odd bits together, the result should be a 1.
  // In this case the 1 should end up at the second least significant bit.
  x &= x >> 2;
  x &= x >> 4;
  x &= x >> 8;
  x &= x >> 16;
  return (x >> 1) & 1;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  // ~x = 2 ^ w - 1 - x.
  // -x = 2 ^ w - x = ~x + 1.
  return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // 1. x's higher 28 bits should be exactly 26 zeros followed by 2 ones.
  //    So (x >> 4) ^ 3 == 0.
  // 2. x's lower 4 bits should be less than 10,
  //    that is less than 16 after adding 6.
  //    ((x & 0xF) + 6) >> 4 == 0
  // Like isTmax, we use !(a | b) to require both a and b be 0.
  return !(((x >> 4) ^ 3) | (((x & 0xF) + 6) >> 4));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // a & 0 = 0, a & -1 = a
  // mask will be -1 if x is true and 0 if x is false.
  int mask = !x + ~0;
  return (mask & y) | (~mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // a. If x is Tmin, x <= y is true.
  //    x ^ (1 << 31) == 0
  // b. If x is not Tmin, then x <= y means y - x >= 0.
  //    If sign bit of y and -x are same,
  //    then the result without overflow is the same too.
  //    Otherwise, use the sign bit of the truncated sum.
  int x_is_Tmin = !(x ^ (1 << 31));
  int minus_x = ~x + 1;
  int sum_truncated = y + minus_x;
  int different_sign_bit = y ^ minus_x;
  int true_sign_bit = (y & ~different_sign_bit) | (sum_truncated & different_sign_bit);
  return x_is_Tmin | !(x_is_Tmin | true_sign_bit >> 31);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // x ^ (x - 1) fills bits lower than the lowest one bit with one,
  // but 0 will result in -1,
  // so we & it with x again to get the lowest one bit of x.
  // If we subtract by 1, only 0 will yield a one at sign bit.
  // We fill the number with sign bit by shifting right 31 bits,
  // then it will be -1 for 0 and 0 for other.
  int minus_one = ~0;
  return ((((x ^ (x + minus_one)) & x) + minus_one) >> 31) & 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // This puzzle bugged me so long, roughly all other puzzles added up.
  // A number in two's complement can be written as
  // sign_bit sign_bit ... sign_bit [not_sign_bit ...] .
  // The leading sequence of sign_bits can be replaced by one sign_bit.
  // 1. First xor every bit with sign bit, turning x into 0 0 ... [1 ...] .
  // 2. We need to find out the position of the highest 1,
  //    or equivalently, minimum number of right shifts required to make it 0,
  //    which is at most 31 because the now sign bit must be 0.
  // 3. Use bisection method because we can't afford iteration
  //    (90 < 31 * 3, I tried).
  //    If shifting l doesn't make x 0, then we have to shift at least (l + 1).
  //    Shift x and add to the count if so many shifts are required. 
  int minus_one = ~0;
  int count = 0;
  int test, length, should_shift, actual_shift_amount;

  x ^= x >> 31;

  test = 15, length = 16;
  should_shift = !(x >> test) + minus_one;
  actual_shift_amount = length & should_shift;
  x >>= actual_shift_amount;
  count += actual_shift_amount;

  test = 7, length = 8;
  should_shift = !(x >> test) + minus_one;
  actual_shift_amount = length & should_shift;
  x >>= actual_shift_amount;
  count += actual_shift_amount;

  test = 3, length = 4;
  should_shift = !(x >> test) + minus_one;
  actual_shift_amount = length & should_shift;
  x >>= actual_shift_amount;
  count += actual_shift_amount;

  test = 1, length = 2;
  should_shift = !(x >> test) + minus_one;
  actual_shift_amount = length & should_shift;
  x >>= actual_shift_amount;
  count += actual_shift_amount;

  // Now x is either 0 or 1, we can simplify it.
  count += x;

  return count + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  // For denormalized number, we can just left shift by 1.
  // The new implied one (if any) will enter the exponent part.
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac = uf & 0x7FFFFF;
  if (exp == 0) {
    frac <<= 1;
  } else if (exp < 0xFF) {
    exp += 1;
    if (exp == 0xFF) {
        frac = 0;
    }
  }
  return sign | (exp << 23) | frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  // Make exponent 0 by shifting.
  // To reduce number of operators,
  // treat denormalized number, inifinity and NaN like normal number,
  // and it's safe in this case.
  int sign = uf >> 31;
  int exp = (uf >> 23) & 0xFF;
  int frac = uf & 0x7FFFFF;

  // Add implied one.
  frac |= 0x800000;
  // 0x7F + 23
  exp -= 150;
  while (exp < 0) {
      frac >>= 1;
      exp += 1;
  }
  while (exp > 0) {
      frac <<= 1;
      exp -= 1;
      if (frac & 0x80000000) {
          return 0x80000000;
      }
  }
  return sign ? -frac : frac;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    if (x < -149 /* -126 - 23 */) {
        return 0;
    } else if (x < -126) {
        return 0x800000 >> (-126 - x);
    } else {
        int exp = ((x <= 0x7F) ? (x + 0x7F) : 0xFF);
        return exp << 23;
    }
}
