/**
 * This hook just accepts any transaction coming through it
 */
#include "../hookapi.h"
#include "testmacro.h"

/*
int64_t util_accid (
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


    // Test Case 1: util_accid
    // VALID CONVERSION
    {
        uint8_t accid_out[20];
        uint8_t r_address[] = "rrrrrrrrrrrrrrrrrrrrBZbvji";
        int64_t result = util_accid(SBUF(accid_out), r_address, sizeof(r_address) - 1);
        trace_num(SBUF("Test : 1"), result);
        trace(SBUF("accid_out"), SBUF(accid_out), 1); // Expected: 0000000000000000000000000000000000000001
        ASSERT(result == 20);   
    }

    // Test Case 2: util_accid
    // TOO_BIG: - read_len was longer than an r-address can be.
    {
        uint8_t accid_out[20];
        uint8_t r_address[] = "rrrrrrrrrrrrrrrrrrrrBZbvji";
        int64_t result = util_accid(SBUF(accid_out), r_address, 99);  // read_len is longer than the r address size.
        trace_num(SBUF("Test : 2"), result);
        trace(SBUF("accid_out"), SBUF(accid_out), 1); // Expected: TOO_BIG
        ASSERT(result == -3);
    }

    // Test Case 3: util_accid
    // TOO_SMALL: write_len was not long enough to store produced account id.
    {    
        uint8_t accid_out[10];
        uint8_t r_address[] = "rrrrrrrrrrrrrrrrrrrrBZbvji";
        int64_t result = util_accid(SBUF(accid_out), r_address, sizeof(r_address) - 1);  
        trace_num(SBUF("Test : 3"), result);
        trace(SBUF("accid_out"), SBUF(accid_out), 1); // Expected: TOO_SMALL
        ASSERT(result == -4);
    }

    // Test Case 4: util_accid
    // INVALID_ARGUMENT: read_ptr pointing at invalid r-address.
    {    
        uint8_t accid_out[20];
        uint8_t r_address[] = "rrrrrrrrrrrrrrrrrrrrBZbvji`s";
        int64_t result = util_accid(SBUF(accid_out), r_address, sizeof(r_address) - 1);
        trace_num(SBUF("Test : 4"), result);
        trace(SBUF("accid_out"), SBUF(accid_out), 1); // Expected: INVALID ARGUMENT
        ASSERT(result == -7);
    }

    // Test Case 5: util_accid
    // OUT_OF_BOUNDS: length of the pointer buffer is 'out of bounds'.
    {     
        uint8_t accid_out[20];
        uint8_t r_address[] = "rrrrrrrrrrrrrrrrrrrrBZbvjis";
        int64_t result = util_accid(accid_out, 99999999, r_address, sizeof(r_address) - 1);
        trace_num(SBUF("Test : 5"), result);
        trace(SBUF("accid_out"), SBUF(accid_out), 1); // Expected: OUT_OF_BOUNDS
        ASSERT(result == -1);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;
}
