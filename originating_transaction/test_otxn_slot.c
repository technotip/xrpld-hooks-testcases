/*
 * otxn_slot
 * Load the originating transaction into a slot.
*/

#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t otxn_slot (
    uint32_t slot_no
 );
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:
    {
	    int64_t otxn_slot_no = otxn_slot(0);
	    trace(SBUF("Testcase1: otxn_slot"), SBUF(otxn_slot_no), 1);
    }

    // Test case 2: INVALID_ARGUMENT
    {
            int64_t otxn_slot_no = otxn_slot('s');
            trace(SBUF("Testcase2: otxn_slot"), SBUF(otxn_slot_no), 1);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
