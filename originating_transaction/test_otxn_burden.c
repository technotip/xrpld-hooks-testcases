/*
 * otxn_burden
 * Get the burden of the originating transaction.
*/

#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t otxn_burden (
     void
 );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: No burden was present on the originating transaction.
    {
	int64_t result = otxn_burden();

        trace_num(SBUF("Testcase1: Burden"), result); 
    } 

    // Test case 2: 
    {
       	int64_t result = otxn_burden();

        trace_num(SBUF("Testcase2: Burden"), result);
    }    



    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
