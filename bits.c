/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y) & ~(~x&~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x){
        if (!y){
            return 1;
        }
        else{
            return 0;
        }
    }
    else {
        if (!y){
            return 0;
        }
    }

    return !((x^y)>>31);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int b,t;
    b = ((v>>16) >0)<<4;
    v=v>>b;
    t = ((v>>8) >0)<<3;
    v=v>>t;
    b = b|t;
    t = ((v>>4) >0)<<2;
    v=v>>t;
    b=b|t;
    t = ((v>>2) >0)<<1;
    v=v>>t;
    b=b|t;
    t = (v>>1) >0;

    return b|t;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int a,b;
    n = n<<3;
    m = m<<3;
    a = (x>>n)&0xFF;
    b = (x>>m)&0xFF;
    int p;
    p = 0xFF<<n|0xFF<<m;
    x = x&(~p);
    return x|a<<m|b<<n;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned k = 0;
    for (unsigned i=0;i-32;i++){
        unsigned t = (v>>i)&0x1;
        k += t<<(31-i);
    }
    return k;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int z = !n;
    int m = 0x7FFFFFFF|(~z+1);
    m = m >> (n+~0+z);
    x = (x>>n)&m;
    return x;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int b1,b2,b3,b4,b5,b6,p=0;
    b1 = (!((x>>16)+1))<<4;
    p=p+b1;
    b2 = (!((x>>(25+~p))+1))<<3;
    p=p+b2;
    b3 = (!((x>>(29+~p))+1))<<2;
    p=p+b3;
    b4 = (!((x>>(31+~p))+1))<<1;
    p=p+b4;
    b5 = !((x>>(32+~p))+1);
    p=p+b5;
    b6 = !((x>>(32+~p))+1);
    return p+b6;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign, ux, frac, exp;
    unsigned t, sig, bias;
    int e = 0;
    int sh;

    if (x == 0)
        return 0;

    sign = x&0x80000000;
    ux = x;

    if (x < 0)
        ux = ~ux + 1;

    t = ux;

    while (t > 1) {
        t = t >> 1;
        e = e + 1;
    }

    exp = e + 127;
    if (e < 24) {
        frac = (ux << (23 - e)) & 0x7FFFFF;
    } else {
        sh = e - 23;

        bias = (1 << (sh - 1)) - 1
             + ((ux >> sh) & 1);

        sig = (ux + bias) >> sh;

        exp = exp + (sig >> 24);
        frac = sig & 0x7FFFFF;
    }

    return sign | (exp << 23) | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned exp = uf & 0x7F800000;

    if (exp == 0x7F800000)
        return uf;

    if (exp == 0){
        return (uf & 0x80000000)|((uf & 0x7FFFFFFF) << 1);
    }

    if (exp == 0x7F000000)
        return (uf & 0x80000000)|0x7F800000;

    return uf + 0x00800000;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int exp = (uf2 >> 20) & 0x7FF;
    int E = exp - 1023;

    unsigned mant;
    unsigned val;

    if (exp > 0x7FE)
        return 0x80000000;

    if (E < 0)
        return 0;

    if (E >= 31)
        return 0x80000000;

    mant = (uf2 & 0xFFFFF) | 0x100000;

    if (E <= 20) {
        val = mant >> (20 - E);
    } else {
        val = (mant << (E - 20))
            | (uf1 >> (52 - E));
    }

    if (uf2 >> 31)
        return ~val + 1;

    return val;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x){
    if (x < -149)
        return 0;
    if (x < -126)
        return 1 << (x + 149);
    if (x > 127)
        return 0x7F800000;

    return (x + 127) << 23;
}
