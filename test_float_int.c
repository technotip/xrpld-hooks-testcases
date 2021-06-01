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

    // Test case 5:  CANT_RETURN_NEGATIVE
    {
        int64_t result = float_int( float_negate(float_set(-15, 5000000000000000)), 3, 0 ); // We are using float_negate() to get negative XFL, which is not allowed in float_int().
     
        trace_num(SBUF("testcase5: "), result);
        ASSERT( result == -33 ); // Expected result: -33.
    }

    // Test case 6:  INVALID_FLOAT 
    {
        int64_t result = float_int( 1, 3, 0 ); // First parameter must be valid XFL number.
        trace_num(SBUF("Testcase6:"), result);
        ASSERT( result == -10024 ); // Expected result: --10024.
    }    

    // Test case 7:  VALID INPUT & OUTPUT
    {
        int64_t result = float_int( float_set(1, 1), 3,  0); // 10 x 10 ^ 3 = 10000.

	trace_num(SBUF("Testcase7:"), result);
        ASSERT( result == 10000 ); // Expected result: 1 x 10^1 = 10 x 10 ^ 3 = 10000.
    }    

    // Test case 8:  INVALID_ARGUMENT
    {
        int64_t result = float_int( float_set(1, 1), 81,  0); // Observe 2nd parameter. An exponent must be in the range -96 to 80.

        trace_num(SBUF("Testcase8:"), result);
        ASSERT( result == -7 ); // Expected result: -7, which represents INVALID_ARGUMENT.
    }     

    // Test case 9:  Similar condition has been reported https://github.com/XRPL-Labs/xrpld-hooks/issues/5
    {
	int64_t result = float_int(float_set(10 ,14), 0, 0);

        trace_num(SBUF("Testcase9:"), result);
        ASSERT( result == 0 ); // Results in [TimeoutError()] constion. Returns 0.
    }    

    // Test case 10:  Similar condition has been reported https://github.com/XRPL-Labs/xrpld-hooks/issues/5
    {
        int64_t result = float_int(float_set(11 , 1), 0, 0);

        trace_num(SBUF("Testcase10:"), result);
        ASSERT( result == 0 ); // Results in [TimeoutError()] constion. Returns 0.
    }    

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
