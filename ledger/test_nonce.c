#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t nonce (
    uint32_t write_ptr,
    uint32_t write_len
 );
*/

/*
nonce: Generate a 32 byte nonce for use in an emitted transaction.
*/
int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: 
    {
	uint8_t n[32];
	int64_t result = nonce(SBUF(n));	    

        if(result != 32)
                rollback(SBUF("Testcase1: Couldn't generate nonce."), 1);

        trace(SBUF("Testcase1: result "), SBUF(n), 1); 
        trace_num(SBUF("Testcase1: Current Ledger sequence"), ledger_seq()); 

	ASSERT(result == 32);
    } 


    // Test case 2: OUT_OF_BOUNDS 
    {
        uint8_t n[32];
        int64_t result = nonce(n, 999999); // 2nd argument is invalid.

	trace_num(SBUF("Testcase2: result"), result);
        trace_num(SBUF("Testcase2: Current Ledger sequence"), ledger_seq());

        ASSERT(result == -1); // -1 corresponds to OUT_OF_BOUNDS.
    }



    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
