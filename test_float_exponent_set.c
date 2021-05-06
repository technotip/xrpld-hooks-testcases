#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_exponent_set (
        int64_t float1,
        int32_t exponent
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Reset the exponent of an XFL enclosing number.
    {
        int64_t result = float_exponent_set(float_set(15, 5), 6); // Resets the exponent from 15 to 6.

        trace_float(SBUF("Testcase1: floating"), result);
        ASSERT(result == float_set(6, 5000000000000000)); // Expected result: 0. indicating positive sign. 
    }

    // Test case 2:  INVALID_FLOAT.
    {
        int64_t result = float_exponent_set( 1, 6 ); // First parameter is expected to be XFL enclosing number.

        trace_num(SBUF("Testcase2: "), result);
        ASSERT(result == -10024); // Expected result: -10024. Indicating INVALID_FLOAT.
    }

    // Test case 3:  EXPONENT_OVERSIZED.
    {
        int64_t result = float_exponent_set( float_set(-15, 5), 81 ); // Second parameter must be in the range of -96 to 80(inclusive).

        trace_num(SBUF("Testcase3: "), result);
        ASSERT(result == -28); // Expected result: -28. Indicating EXPONENT_OVERSIZED.
    }

    // Test case 4:  EXPONENT_UNDERSIZED.
    {
        int64_t result = float_exponent_set( float_set(-15, 5), -97 ); // Second parameter must be in the range of -96 to 80(inclusive).

        trace_num(SBUF("Testcase4: "), result);
        ASSERT(result == -29); // Expected result: -29. Indicating EXPONENT_UNDERSIZED.
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
