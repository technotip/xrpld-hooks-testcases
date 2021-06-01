/*
 * trace
 * Write the contents of a buffer to the XRPLD trace log.
*/

#include "../hookapi.h"
#include "../testmacro.h"

/*
 int64_t trace (
    uint32_t mread_ptr,
    uint32_t mread_len,
    uint32_t dread_ptr,
    uint32_t dread_len,
    uint32_t as_hex
 );
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

        uint8_t actual[27];
        uint8_t expected[] = "rrrrrrrrrrrrrrrrrrrrrhoLvTp";
        uint8_t accountid[20] = {}; // all zeros

        int64_t actual_len = util_raddr(SBUF(actual), SBUF(accountid));	

    // Test case 1: 
    {
	    uint8_t output[] = "rHdkzpxr3VfabJh9tUEDv7N4DJEsA4UioT";
	    trace(SBUF("Testcase1: "), SBUF(actual), 1); //    If 1 output the buffer as hex.
    }     

    // Test case 2: OUT_OF_BOUNDS
    {
            uint8_t output[] = "rHdkzpxr3VfabJh9tUEDv7N4DJEsA4UioT";
            int64_t result = trace(SBUF("Testcase2: "), actual, 9999999, 1); //    If 1 output the buffer as hex.
	    trace_num(SBUF("Testcase2: result"), result);

	    ASSERT(result == -1); // OUT_OF_BOUNDS
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
