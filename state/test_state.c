/*
 * state
 * Retrieve the data pointed to by a Hook State key and write it to an output buffer.
*/

#include "../hookapi.h"
#include "../testmacro.h"

/*
 int64_t state (
    uint32_t write_ptr,
    uint32_t write_len,
    uint32_t kread_ptr,
    uint32_t kread_len  
 );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Testcase 1:
    {
	        uint8_t key[32]; // initially it'll be 0.
		uint8_t hook_addr[20];
		uint8_t outbuff[20];

		hook_account(SBUF(hook_addr));

                int64_t result = state_set(SBUF(hook_addr), SBUF(key));
                
		int64_t lookup =  state(SBUF(outbuff), SBUF(key));
                if (lookup < 0)
		     rollback(SBUF("Testcase1: Error: could not find data at specified key."), 1);		

		trace(SBUF("Testcase1: "), SBUF(outbuff), 1);

    }     

    // Testcase 2: OUT_OF_BOUNDS
    {
	    uint8_t key[32];
	    uint8_t hook_addr[20];
	    uint8_t outbuff[20];

	    hook_account(SBUF(hook_addr));

	    uint64_t result = state_set(SBUF(hook_addr), SBUF(key));

	    int64_t lookup = state((outbuff), 99999, SBUF(key));
	    if(lookup < 0)
		    trace(SBUF("Testcase2: couldn't find data at specified location."), SBUF(outbuff), 1);

	    trace_num(SBUF("Testcase2: lookup"), lookup);

	    ASSERT( -1 == lookup );
    }

    // Testcase 3: DOESNT_EXIT
    {
	    uint8_t key[32];
	    uint8_t hook_addr[20];
	    uint8_t outbuff[20];
	    key[1] = 1;
 
	    int64_t lookup = state(SBUF(outbuff), SBUF(key));
	    if(lookup < 0)
		    trace(SBUF("Testcase3: couldn't find data at specified location"), SBUF(outbuff), 1);
	    trace(SBUF("Testcase3: outbuff"), SBUF(outbuff), 1);
	    trace_num(SBUF("Testcase3: lookup"), lookup);

	    ASSERT( -5 == lookup );
    }

    // Testcase 4: TOO_BIG
    {
	    uint8_t key[999];
	    uint8_t hook_addr[20];
	    uint8_t outbuff[20];

	    int64_t lookup = state(SBUF(outbuff), SBUF(key));
	    if(lookup < 0)
		    trace(SBUF("Testcase4: couldn't find data at specified location."), SBUF(outbuff), 1);

	    trace(SBUF("Testcase4: outbuff"), SBUF(outbuff), 1);
	    trace_num(SBUF("Testcase4: lookup"), lookup);

	    ASSERT( -3 == lookup );
    }

    //Testcase 5: INVALID_ARGUMENT
    {
	    uint8_t key[0];
	    uint8_t hook_addr[20];
	    uint8_t outbuff[20];

	    int64_t lookup = state(SBUF(outbuff), SBUF(key));
	    if(lookup < 0)
		    trace(SBUF("Testcase5: cound't find valid data at specified key."), SBUF(outbuff), 1);

	    trace(SBUF("Testcase5: lookup"), SBUF(outbuff), 1);
	    trace_num(SBUF("Testcase5: lookup"), lookup);

	    ASSERT( -7 == lookup );
    }

    //Testcase 6: TOO_SMALL
    {
            uint8_t key[32];
            uint8_t hook_addr[20];
            uint8_t outbuff[0];

            int64_t lookup = state(SBUF(outbuff), SBUF(key));
            if(lookup < 0)
                    trace(SBUF("Testcase6: cound't find valid data at specified key."), SBUF(outbuff), 1);

            trace(SBUF("Testcase6: lookup"), SBUF(outbuff), 1);
            trace_num(SBUF("Testcase6: lookup"), lookup);

            ASSERT( -4 == lookup );
    }    

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;


}
