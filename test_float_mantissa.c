#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t float_mantissa (
    int64_t float1
 );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Fetching mantissa of a XFL enclosing number.
    {
        int64_t result = float_mantissa(float_one());
        trace_num(SBUF("Testcase1: result"), result);
        ASSERT(result == 1000000000000000); // Expected result 1000000000000000
    }

    // Test case 2:  Fetching mantissa of a XFL enclosing number.
    {
        int64_t result = float_mantissa(float_set(5, 123456789));
        trace_num(SBUF("Testcase2: result"), result);
        ASSERT(result == 1234567890000000); // Expected 1234567890000000
    }

    // Test case 3:  INVALID_FLOAT.
    {
        int64_t result = float_mantissa(1); //Invalid XFL number.
        trace_num(SBUF("Testcase3: result"), result);
        ASSERT(result == -10024);
    }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
