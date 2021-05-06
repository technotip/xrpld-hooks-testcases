#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_divide (
        int64_t float1,
        int64_t float2
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Dividing 1 by 1, is still 1.
    {
        int64_t result = float_divide(float_one(), float_one());
        trace_float(SBUF("Testcase1: result"), result);
        //ASSERT(result == float_one());
    }

    // Test case 2:  Division by 0.
    {
        int64_t result = float_divide(float_one(), 0);
        trace_num(SBUF("Testcase2: result"), result);
        ASSERT(result == -25); // Error code -25 represents DIVISION_BY_ZERO
    }

    // Test case 3:  INVALID_FLOAT.
    {
        int64_t result = float_divide(float_one(), 1); // Second parameter is not a valid float
        trace_num(SBUF("Testcase3: result"), result);
        ASSERT(result == -10024); // Error code -10024 represents INVALID_FLOAT.
    }

    // Test case 4:  INVALID_FLOAT.
    {
        int64_t result = float_divide(1, float_set(0, 5)); // First parameter is not a valid float
        trace_num(SBUF("Testcase4: result"), result);
        ASSERT(result == -10024); // Error code -10024 represents INVALID_FLOAT.
    }

    // Test case 5:  INVALID_FLOAT.
    {
        int64_t result = float_divide(1, 1); // Both first & second parameters are not valid floats.
        trace_num(SBUF("Testcase5: result"), result);
        ASSERT(result == -10024); // Error code -10024 represents INVALID_FLOAT.
    }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
