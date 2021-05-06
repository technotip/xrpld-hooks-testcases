/**
 * This hook just accepts any transaction coming through it
 */
#include "../hookapi.h"
#include "testmacro.h"

/*
int64_t util_raddr (
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

    // Test case 1: all zero account id
    {
        uint8_t actual[50];
        uint8_t expected[] = "rrrrrrrrrrrrrrrrrrrrrhoLvTp";
        uint8_t accountid[20] = {}; // all zeros
        
        int64_t actual_len =
            util_raddr(SBUF(actual), SBUF(accountid));
        
        int equal = 0;
        BUFFER_EQUAL_STR(equal, actual, actual_len, expected);
    
     
        ASSERT(equal); 
    }

    // test case 2: ... testing with a regular, randomly generated r-address
    {
        uint8_t actual[50];
        uint8_t expected[] = "rM4XQJa5aPH6gxUPYVQX1BHdQYxCA5cksr";
   
        uint8_t accountid[20] = {0xdfU,0x74U, 0xa0U, 0xfeU, 0x40U, 0x68U, 0x14U, 0x30U, 0x13U, 0x39U, 0xdcU, 0xa8U, 0x30U, 0x99U, 0xe7U, 0x5eU, 0x46U, 0x77U, 0x15U, 0x30U};


        int64_t actual_len =
            util_raddr(SBUF(actual), SBUF(accountid));

        int equal = 0;
        BUFFER_EQUAL_STR(equal, actual, actual_len, expected);

        ASSERT(equal);
    }   


    // test case 3: ... testing with a regular, randomly generated r-address 
    {
        uint8_t actual[50];
        uint8_t expected[] = "r9h2oyCX2KCfxeHTorJh6PLmc9LmHYejVz";

        uint8_t accountid[20] = {0x58U,0x6EU,0x7AU,0x2EU,0xEFU,0x5CU,0xE3U,0x4AU,0xAEU,0x4BU,0x45U,0x2CU,0x69U,0x96U,0x95U,0x67U,0x9BU,0x51U,0x1CU,0xE2U};
        

        int64_t actual_len =
            util_raddr(SBUF(actual), SBUF(accountid));

        int equal = 0;
        BUFFER_EQUAL_STR(equal, actual, actual_len, expected);


        ASSERT(equal);
    }

    // test case 4: ...  expected account ID for the r-address is: 0000000000000000000000000000000000000001
    {
        uint8_t actual[50];
        uint8_t expected[] = "rrrrrrrrrrrrrrrrrrrrBZbvji";

        uint8_t accountid[20] = {};
        accountid[19] = 0x01U;


        int64_t actual_len =
            util_raddr(SBUF(actual), SBUF(accountid));

        int equal = 0;
        BUFFER_EQUAL_STR(equal, actual, actual_len, expected);


        ASSERT(equal);
    }



    // Test case 5: It requires atleast 35 bytes to store the r-address. Lets allocate less bytes and try to execute
    {
        uint8_t actual[26]; // for uint8_t actual[25], the transaction fails.
        uint8_t expected[] = "rrrrrrrrrrrrrrrrrrrrBZbvji";

        uint8_t accountid[20] = {};
        accountid[19] = 0x01U;


        int64_t actual_len =
            util_raddr(SBUF(actual), SBUF(accountid));

        int equal = 0;
        BUFFER_EQUAL_STR(equal, actual, actual_len, expected);
        

        ASSERT(equal);
    }

    
    // Test Case 6: TOO_SMALL
    {
        uint8_t acc[20];

        int64_t result = util_raddr(0, 0, SBUF(acc)); // write_len not large enough to store produced r-address.
        trace_num(SBUF("Test 7: "), result);
        ASSERT(result == -4); // TOO_SMALL expected
    }
    

    // Test Case 7: OUT_OF_BOUNDS
    {
        uint8_t acc[20];

        int64_t result = util_raddr(999999999, 999999999, SBUF(acc)); // pointer/length specified outside of hook memory.
        trace_num(SBUF("Test 7: "), result);
        ASSERT(result == -1); //  OUT_OF_BOUNDS expected
    }

    // Test Case 8: INVALID_ARGUMENT
    {   
        uint8_t acc[2];
             
        int64_t result = util_raddr(99, 99, SBUF(acc)); // read_len is not 20. Check the above line - uint8_t acc[2];
        trace_num(SBUF("Test 7: "), result);
        ASSERT(result == -7); //  INVALID_ARGUMENT expected
    }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
