#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t hook_hash (
    uint32_t write_ptr,
    uint32_t write_len
 );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: 
    {
        uint8_t hash[32];
        int64_t result = hook_hash(SBUF(hash));
	trace_num(SBUF("Testcase1: no of bytes written "), result);

        if(result != 32)
                rollback(SBUF("Testcase1: Couldn't fetch the hook account."), 1);

        trace(SBUF("Testcase1: result "), SBUF(hash), 1); 
         
    } 

    // Test case 2: OUT_OF_BOUNDS
    {
        uint8_t hash[32];
        int64_t result = hook_hash(hash, 9999999);
        trace_num(SBUF("Testcase2: no of bytes written "), result);

        trace(SBUF("Testcase2: result "), SBUF(hash), 1);

	ASSERT(result == -1); // OUT_OF_BOUNDS (-1)

    }    


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
