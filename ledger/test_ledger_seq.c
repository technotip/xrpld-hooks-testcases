#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t ledger_seq ();
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: Fetch the current ledger sequence number.
    {
        int64_t seq = ledger_seq();
	trace_num(SBUF("Testcase1: Current Ledger sequence "), seq); 
    } 


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
