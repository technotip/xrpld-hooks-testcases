#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_int (
        int64_t float1,
        uint32_t decimal_places,
        uint32_t absolute
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Conver an XFL floating point into an integer(float).
    {
        int64_t result = float_int(float_set(-15, 5), 15, 1 );

        trace_num(SBUF("Testcase1:"), result);
        ASSERT( result == 5 ); // Expected result: 5.
    }

    // Test case 2:  Conver an XFL floating point into an integer(float).
    {
        int64_t result = float_int(float_set(-13, 5), 15, 1 );
        trace_num(SBUF("Testcase2:"), result);
        ASSERT( result == 500 ); // Expected result: 500.
    }

    // Test case 3:  Conver an XFL floating point into an integer(float).
    {
        int64_t result = float_int(float_set(-15, 5000000000000000), 3, 1 );
        trace_num(SBUF("Testcase3:"), result);
        ASSERT( result == 5000 ); // Expected result: 5000.
    }

    // Test case 4:  Absolute value: 1
    {
        int64_t result = float_int( float_negate(float_set(-15, 5000000000000000)), 3, 1 ); // Last parameter(1) converts any negative value to positive.
        trace_num(SBUF("Testcase4:"), result);
        ASSERT( result == 5000 ); // Expected result: 5000.
    }

    // Test case 5:  Absolute value: 0
    {
        int64_t result = float_int( float_negate(float_set(-15, 5000000000000000)), 3, 0 ); // Last parameter(1) converts any negative value to positive.
       trace_float(SBUF("Testcase5:"), result);
        ASSERT( result == -5000 ); // Expected result: -5000.
    }

    // Test case 6:  INVALID_FLOAT 
    {
        int64_t result = float_int( 1, 3, 0 ); // First parameter must be valid XFL number.
       trace_num(SBUF("Testcase5:"), result);
      //  ASSERT( result == -5000 ); // Expected result: -5000.
    }    

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
