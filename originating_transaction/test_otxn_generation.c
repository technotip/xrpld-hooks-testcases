/*
 * otxn_generation
 * Get the generation of the originating transaction.
*/

#include "../hookapi.h"
#include "testmacro.h"

/*
int64_t otxn_generation (
    void
);
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:     1 if no generation was present on the originating transaction.

    {
	int64_t generation =  otxn_generation();

	trace_num(SBUF("Testcase1: result"), generation);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
