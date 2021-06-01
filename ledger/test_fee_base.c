#include "../hookapi.h"
#include "testmacro.h"

/*
   int64_t fee_base ();
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: Return the fee base from the current ledger.
    {
        int64_t fee = fee_base();
	trace_num(SBUF("Testcase1: fee base of current ledger:"), fee);

	ASSERT(fee == 11); // usually it'll be 11 drops. It might change. It's not a fixed value and will change with network load.
         
    } 


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
