#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_one();
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: Returns one(1) as an XFL int64_t.
    {
        int64_t result = float_one();
        trace_float(SBUF("Testcase1: result"), result);
        ASSERT(result == float_one());
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
