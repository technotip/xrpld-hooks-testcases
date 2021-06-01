/*
 * otxn_type
 * Get the Transaction Type of the originating transaction.
*/

#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t otxn_type (
    void
 );
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: ttPAYMENT returns 0.
    {
	int64_t tt = otxn_type();
	trace_num(SBUF("Transaction Type"), tt);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
