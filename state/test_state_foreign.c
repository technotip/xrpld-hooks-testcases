/*
 * state_foreign
 * Retrieve the data pointed to, on another account, by a Hook State key and write it to an output buffer.
*/

#include "../hookapi.h"
#include "../testmacro.h"

#define HOOK_INSTALLED_ACCOUNT "rJ13STEreKVDf4Z6hP2d3wVWmgXikrXAe4"

/*
 int64_t state_foreign (
    uint32_t write_ptr,
    uint32_t write_len,
    uint32_t kread_ptr,
    uint32_t kread_len,
    uint32_t aread_ptr,
    uint32_t aread_len  
 );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

        uint8_t key[32] = {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x01U};	

    // Test case 1:
    {
		uint8_t accid[20];
		uint8_t status[20];

		int64_t bytes_written = util_accid(SBUF(accid), SBUF(HOOK_INSTALLED_ACCOUNT));
			
		int64_t lookup =  state_foreign(SBUF(status), SBUF(key), SBUF(accid));
                if (lookup < 0)
		       rollback(SBUF("Testcase 1: Error: could not find key on foreign state."), 1);		
		
		trace(SBUF("Testcase 1: Foreign key state"), SBUF(status), 1);
		trace_num(SBUF("Testcase 1: Lookup value:"), lookup);

		ASSERT(lookup == 20);
    }     

    // Test case 2: OUT_OF_BOUNDS
    {
                uint8_t accid[20]; 
                uint8_t status[20];
          
                int64_t bytes_written = util_accid(SBUF(accid), SBUF(HOOK_INSTALLED_ACCOUNT));
                   
                int64_t lookup =  state_foreign((status), 99999, SBUF(key), SBUF(accid));
                if (lookup < 0)
                {
                        trace_num(SBUF("Testcase 2: Lookup value:"), lookup); 
                        //rollback(SBUF("Testcase 2:  Error: could not find key on foreign state."), 1);
                }
                trace(SBUF("Testcase 2: Foreign key state"), SBUF(status), 1);

		ASSERT(-1 == lookup);
    }

    // Test case 3: DOESNT_EXIST
    {
	    uint8_t key[32] = {0x00U, 0x05U, 0x0aU, 0x0fU, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x10U, 0x01U, 0x01U};;
	    uint8_t accid[20];
	    uint8_t status[20];

	    int64_t bytes_written = util_accid(SBUF(accid), SBUF(HOOK_INSTALLED_ACCOUNT));

	    int64_t lookup = state_foreign(SBUF(status), SBUF(key), SBUF(accid));

	    if(lookup < 0)
		    trace_num(SBUF("Testcase3: Lookup value: "), lookup);

	    trace(SBUF("Testcase3: Foreign key state"), SBUF(status), 1);

	    ASSERT( -5 == lookup );
    }

    // Test case 4: TOO_BIG
    {
	    uint8_t key[5000];
            uint8_t accid[20];
            uint8_t status[20];
    
            int64_t bytes_written = util_accid(SBUF(accid), SBUF(HOOK_INSTALLED_ACCOUNT));

            int64_t lookup = state_foreign(SBUF(status), SBUF(key), SBUF(accid));

            if(lookup < 0)
                    trace_num(SBUF("Testcase4: Lookup value: "), lookup);

            trace(SBUF("Testcase4: Foreign key state"), SBUF(status), 1);

            ASSERT( -3 == lookup );
    }    

    // Test case 5: INVALID_ARGUMENT
    {
            uint8_t key[0];
            uint8_t accid[20];
            uint8_t status[20];
    
            int64_t bytes_written = util_accid(SBUF(accid), SBUF(HOOK_INSTALLED_ACCOUNT));
          
            int64_t lookup = state_foreign(SBUF(status), SBUF(key), SBUF(accid));
          
            if(lookup < 0) 
                    trace_num(SBUF("Testcase5: Lookup value: "), lookup);

            trace(SBUF("Testcase5: Foreign key state"), SBUF(status), 1);
      
            ASSERT( -7 == lookup );
    }     

    // Test case 6: TOO_SMALL
    {
            uint8_t accid[20];
            uint8_t status[0];
    
            int64_t bytes_written = util_accid(SBUF(accid), SBUF(HOOK_INSTALLED_ACCOUNT));
          
            int64_t lookup = state_foreign(SBUF(status), SBUF(key), SBUF(accid));
          
            if(lookup < 0) 
                    trace_num(SBUF("Testcase6: Lookup value: "), lookup);

            trace(SBUF("Testcase6: Foreign key state"), SBUF(status), 1);
      
            ASSERT( -4 == lookup );
    }    

    // Test case 7: INVALID_ACCOUNT
    {
            uint8_t accid[20];
            uint8_t status[0];

           // int64_t bytes_written = util_accid(SBUF(accid), SBUF(HOOK_INSTALLED_ACCOUNT));

            int64_t lookup = state_foreign(SBUF(status), SBUF(key), SBUF(HOOK_INSTALLED_ACCOUNT));

            if(lookup < 0)
                    trace_num(SBUF("Testcase7: Lookup value: "), lookup);

            trace(SBUF("Testcase7: Foreign key state"), SBUF(status), 1);

            ASSERT( -15 == lookup );
     }



    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;


}
