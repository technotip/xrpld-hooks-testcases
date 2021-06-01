#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t etxn_burden (
    void
 );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: Returns one(1) as an XFL int64_t.
    {
	uint8_t emitdet[105];
	int64_t result = etxn_details(emitdet, 105);

	if (result != 105)
    		rollback("Etxndetails failed.", 19, 1);

	trace(SBUF("result content"), SBUF(result), 1);
        trace_num(SBUF("Testcase1: result"), result);

	trace(SBUF("etxn details "), SBUF(emitdet), 1);
        //ASSERT(result == float_one());
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
