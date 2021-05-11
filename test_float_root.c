#include "../hookapi.h"
#include "testmacro.h"

/*
	int64_t float_root (
    		int64_t float1,
    		uint32_t n
	);
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  
    {
        int64_t result = float_root(2, 6);
	trace_float(SBUF("Testcase1: floating "), result);
        trace_num(SBUF("Testcase1:"), result);
//        ASSERT( result == 5 ); // Expected result: 5.
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
