#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_sign_set (
        int64_t float1,
        uint32_t sign 
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  1 for negative.
    {
        int64_t result = float_sign_set( float_one(), 1); // Applies negative sign.

        trace_float(SBUF("Testcase1: "), result);
        ASSERT( result == float_negate(float_one()) ); // Expected result: Negative 1 in XFL format.
    }

    // Test case 2:  0 for positive.
    {
        int64_t result = float_sign_set( float_negate(float_one()), 0); // Applies negative sign, to negative 1, resulting in +1.

        trace_float(SBUF("Testcase2: "), result);
        ASSERT( result == float_one() ); // Expected result: -(-1) = 1.
    }

    // Test case 3:  INVALID_FLOAT.
    {
        int64_t result = float_sign_set( 1, 0); // First parameter is invalid XFL number.

        trace_num(SBUF("Testcase3: "), result);
        ASSERT( result == -10024 ); // Expected result: -10024.
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
