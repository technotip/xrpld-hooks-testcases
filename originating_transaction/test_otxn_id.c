/*
 * otxn_id
 * Output the canonical hash of the originating transaction.
*/

#include "../hookapi.h"
#include "testmacro.h"

/*
int64_t otxn_id (
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
	uint8_t txn_id[32];
	int64_t bytes_written =  otxn_id(SBUF(txn_id));

	if(bytes_written != 32)
		rollback(SBUF("Testcase1: Couldn't fetch transaction hash."), 100);

	trace_num(SBUF("Testcase1: bytest written"), bytes_written);
	trace(SBUF("Testcase1: txn_id"), SBUF(txn_id), 1);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
