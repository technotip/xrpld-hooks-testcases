/*
 * state_set
 * Set the Hook State for a given key and value.
*/

#include "../hookapi.h"
#include "../testmacro.h"

/*
 int64_t state_set (
    uint32_t read_ptr,
    uint32_t read_len,
    uint32_t kread_ptr,
    uint32_t kread_len  
 );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: All is well
    {
	        uint8_t key[32]; // initially all zeros
	        uint8_t account_field[20];
    		int32_t account_field_len = otxn_field(SBUF(account_field), sfAccount);

		int64_t result = state_set(SBUF(account_field), SBUF(key));	
		
		trace_num(SBUF("Testcase1: result"), result);

		if(result != 20)
			trace_num(SBUF("Testcase1: something is wrong!"), result);
		else
		{
			uint8_t count[20];
			uint64_t statelen = state(SBUF(count), SBUF(key));
			trace_num(SBUF("Testcase1: state len"), statelen);
		}

		ASSERT( result == 20);
    }     

    // Test case 2: OUT_OF_BOUNDS
    {
                uint8_t key[32]; // initially all zeros
                uint8_t account_field[20];
                int32_t account_field_len = otxn_field(SBUF(account_field), sfAccount);

                int64_t result = state_set((account_field), 99999, SBUF(key));
                
                trace_num(SBUF("Testcase2: result"), result);
         
                if(result != 20)
                        trace_num(SBUF("Testcase2: something is wrong!"), result);
                else
                {
                        uint8_t count[20];
                        uint64_t statelen = state(SBUF(count), SBUF(key));
                        trace_num(SBUF("Testcase2: state len"), statelen);
                }

                ASSERT( result == -1 ); // OUT_OF_BOUNDS
    }         

    // Test case 3: TOO_BIG
    {
                uint8_t key[320]; // initially all zeros
                uint8_t account_field[20];
                int32_t account_field_len = otxn_field(SBUF(account_field), sfAccount);

                int64_t result = state_set(SBUF(account_field), SBUF(key));
                
                trace_num(SBUF("Testcase3: result"), result);
         
                if(result != 20)
                        trace_num(SBUF("Testcase3: something is wrong!"), result);
                else
                {
                        uint8_t count[20];
                        uint64_t statelen = state(SBUF(count), SBUF(key));
                        trace_num(SBUF("Testcase3: state len"), statelen);
                }

                ASSERT( result == -3 ); // TOO_BIG
    }

    // Test case 4: TOO_SMALL
    {
                uint8_t key[0]; // initially all zeros
                uint8_t account_field[20];
                int32_t account_field_len = otxn_field(SBUF(account_field), sfAccount);

                int64_t result = state_set(SBUF(account_field), SBUF(key));

                trace_num(SBUF("Testcase4: result"), result);
         
                if(result != 20)
                        trace_num(SBUF("Testcase4: something is wrong!"), result);
                else
                {
                        uint8_t count[20];
                        uint64_t statelen = state(SBUF(count), SBUF(key));
                        trace_num(SBUF("Testcase4: state len"), statelen);
                }
      
                ASSERT( result == -4 ); // TOO_SMALL
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;


}
