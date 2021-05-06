#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_mantissa_set (
        int64_t float1,
        uint64_t mantissa
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Reset the mantissa of an XFL enclosing number.
    {
        int64_t result = float_mantissa_set(float_set(0, 3), 5000000000000000ULL); // Resets the mantissa from 3 to 5.

        trace_float(SBUF("Testcase1: floating"), result);
        ASSERT(result == float_set(0, 5)); // Expected result:  5000000000000000*10^(-15)
    }

    // Test case 2: INVALID_FLOAT.
    {
        int64_t result = float_mantissa_set( 1, 5000000000000000ULL); // Fisrt parameter is not a valid XFL enclosing number.

        trace_num(SBUF("Testcase2: "), result);
        ASSERT(result == -10024); // Expected result: -10024.
    }

    // Test case 3: MANTISSA_OVERSIZED.
    {
        // 2nd parameter, which is mantissa, has more than 16 digits.
        int64_t result = float_mantissa_set( float_set(0, 3), 5000000000000000000ULL);
        
        trace_num(SBUF("Testcase3: "), result);
        ASSERT(result == -26); // Expected result: -10024.
    }

    // Test case 4: MANTISSA_UNDERSIZED.
    {
        // 2nd parameter, which is mantissa, has less than 16 digits.
        int64_t result = float_mantissa_set( float_set(0, 3), 5000ULL); 
        
        trace_num(SBUF("Testcase4: "), result);
        ASSERT(result == -27); // Expected result: -10024.
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
