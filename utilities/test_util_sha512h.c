#include "../hookapi.h"
#include "testmacro.h"

/*
   int64_t util_sha512h (
    	uint32_t write_ptr,
    	uint32_t write_len,
    	uint32_t read_ptr,
    	uint32_t read_len
   );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  
    {
	uint8_t data_in_ptr;

	uint8_t accid_out[20];
	uint8_t raddr_in[] = "rHb9CJAWyB4rj91VRWn96DkukG4bwdtyTh";

	int64_t bytes_written = util_accid(SBUF(accid_out), SBUF(raddr_in));	

        uint8_t hash_out[32];
	if (util_sha512h(SBUF(hash_out), SBUF(accid_out)) < 0)
    		rollback(SBUF("Could not generate Hash"), 100);

        trace(SBUF("Testcase1:"), SBUF(hash_out), 1);
//        ASSERT( result == 5 ); // Expected result: 5.
    }


    // Test case 2:  OUT_OF_BOUNDS
    {
        uint8_t data_in_ptr;

        uint8_t accid_out[20];
        uint8_t raddr_in[] = "rHb9CJAWyB4rj91VRWn96DkukG4bwdtyTh";

        int64_t bytes_written = util_accid(SBUF(accid_out), SBUF(raddr_in));

        uint8_t hash_out[32];
        int64_t result = util_sha512h(hash_out, 99999999, SBUF(accid_out));   //2nd parameter is OUT_OF_BOUNDS.
                

        trace_num(SBUF("Testcase2:"), result);
        ASSERT( result == -1 ); // Expected result: -1.
    }    

    // Test case 3:  TOO_SMALL
    {
        uint8_t data_in_ptr;

        uint8_t accid_out[20];
        uint8_t raddr_in[] = "rHb9CJAWyB4rj91VRWn96DkukG4bwdtyTh";

        int64_t bytes_written = util_accid(SBUF(accid_out), SBUF(raddr_in));

        uint8_t hash_out[3];
        int64_t result = util_sha512h(SBUF(hash_out), SBUF(accid_out));   //2nd parameter is OUT_OF_BOUNDS.


        trace_num(SBUF("Testcase3:"), result);
        ASSERT( result == -4 ); // Expected result: -4.
    }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;
}
