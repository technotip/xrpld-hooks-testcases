/*
 * trace_num
 * Write an integer to the XRPLD trace log.
*/

#include "../hookapi.h"
#include "../testmacro.h"

/*
 int64_t trace_num (
    uint32_t mread_ptr,
    uint32_t mread_len,
    int64_t number 
 );
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: Successful
    {
	    int32_t number = 5;
	    int64_t result = trace_num(SBUF("Testcase1: number ="), number);
	    trace_num(SBUF("Testcase1: return code:"), result);
	    ASSERT(result == 0); // Successful 
    }     

    // Test case 2: OUT_OF_BOUNDS 
    {
            int32_t number = 5;
            int64_t result = trace_num("Testcase2: number =", 99999999, number);
            trace_num(SBUF("Testcase2: return code:"), result);
            ASSERT(result == -1); // OUT_OF_BOUNDS 
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
