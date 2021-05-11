#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_exponent (
        int64_t float1
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Fetching exponent of a XFL enclosing number.
    {
        int64_t result = float_exponent(float_one());
        trace_num(SBUF("Testcase1: result"), result);
	trace_float(SBUF("FloatOne: "), float_one());
        ASSERT(result == -15);
    }

    // Test case 2:  INVALID_FLOAT.
    {
        int64_t result = float_exponent(1); //Invalid XFL number.
        trace_num(SBUF("Testcase2: result"), result);
        ASSERT(result == -10024);
    }

    // Test case 3:  Fetching exponent of a XFL enclosing number.
    {
        int64_t result = float_exponent(float_set(6, 5));
        trace_num(SBUF("Testcase2: result"), result);
        trace_float(SBUF("Testcase2: "), result);
        ASSERT(result == -9);
    }    


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
