#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_sum (
        int64_t float1,
        int64_t float2
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: 1 + 1 = 2.
    {
       int64_t result = float_sum(float_one(), float_one()); 
       trace_num(SBUF("Testcase1: "), result);
       ASSERT(result == float_set(0, 2));
    }

    // Test case 2: EXPONENT_UNDERSIZED.
    {
       int64_t result = float_sum(float_one(), float_negate(float_one()));
       trace_num(SBUF("Testcase2: "), result);
       ASSERT(result == -29); 
    }

    // Test case 3: EXPONENT_UNDERSIZED.
    {
       int64_t number = float_set(0, 2);
       int64_t result = float_sum(number, float_negate(number));
       trace_num(SBUF("Testcase3: "), result);
       ASSERT(result == -29); // 2 - 2 = 0.
    }

    // Test case 4: OVERFLOW.
    {
       int64_t number = float_set(80, 9999999999999999);
       int64_t result = float_sum(number, number);
       trace_num(SBUF("Testcase4: "), result);
       ASSERT(result == -30); // resulted in a value larger than XFL format.
    }

    // Test case 5: INVALID_FLOAT
    {
       int64_t number = float_set(0, 2);
       int64_t result = float_sum(2, number); //First argument is invalid floating point number
       trace_num(SBUF("Testcase5: "), result);
       ASSERT(result == -10024); 
    }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
