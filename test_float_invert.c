#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_invert (
        int64_t float1
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Dividing 1 by 1, is still 1.
    {
        int64_t result = float_invert(float_one());
        trace_float(SBUF("Testcase1: result"), result);
        //ASSERT(result == float_one());
    }


    // Test case 2:  Division by 0.
    {
        int64_t result = float_invert(float_set(0, 0));
        trace_num(SBUF("Testcase2: result"), result);
        ASSERT(result == -25); // Error code -25 corresponds to DIVISION_BY_ZERO.
    }

    // Test case 3:  INVALID_FLOAT.
    {
        int64_t result = float_invert(1);
        trace_num(SBUF("Testcase2: result"), result);
        ASSERT(result == -10024); // Error code -10024 corresponds to INVALID_FLOAT.
    }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
