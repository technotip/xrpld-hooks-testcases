#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_sign (
        int64_t float1
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Gets the sign of an XFL enclosing number.
    {
        int64_t result = float_sign(float_one());
        trace_num(SBUF("Testcase1: result"), result);
        ASSERT(result == 0); // Expected result: 0. indicating positive sign. 
    }

    // Test case 2:  Gets the sign of an XFL enclosing number.
    {
        int64_t result = float_sign( float_negate(float_one()) );
        trace_num(SBUF("Testcase2: result"), result);
        ASSERT(result == 1); // Expected result: 1. indicating negative sign. 
    }

    // Test case 3:  INVALID_FLOAT.
    {
        int64_t result = float_sign( 1 ); // We are passing invalid float as parameter to float_sign() method.
        trace_num(SBUF("Testcase3: result"), result);
        ASSERT(result == -10024); // Expected result: -10024, which indicates INVALID_FLOAT. 
    }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
