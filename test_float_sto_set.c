#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_sto_set (
        uint32_t read_ptr,
        uint32_t read_len
    ); 
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1:  Using XRP currency code and accountid
    {
    uint8_t currency[20] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0, 0, 0, 0,0,0,0,0};
    uint8_t accountid[20] = {0x00U,0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

       uint8_t amt_out[8];
       int64_t amt_out_len = float_sto(SBUF(amt_out), SBUF(currency), SBUF(accountid), float_set(0, 5), -1);
       int64_t result;
       
       if(amt_out_len == 8)
          result = float_sto_set(SBUF(amt_out));
       else
          rollback(SBUF("Testcase1: Couldn't write to amt_out buffer .."), 100);
       
       trace(SBUF("testcase1: serialization"), SBUF(amt_out), 1);
       trace_float(SBUF("Testcase1: De-serialization "), result);

       ASSERT(result == float_set(0, 5));
    }


    // Test case 2:  Setting currency code and account id to 0.
    {
       uint8_t amt_out[8];
       int64_t amt_out_len   = float_sto(SBUF(amt_out), 0, 0, 0, 0, float_set(0, 5), -1);
       int64_t result;

       if(amt_out_len == 8)
          result = float_sto_set(SBUF(amt_out));
       else
          rollback(SBUF("Testcase2: Couldn't write to the buffer amt_out"), 100);
       
       trace(SBUF("testcase2: serialization"), SBUF(amt_out), 1);
       trace_float(SBUF("Testcase2: De-serialization "), result);

       ASSERT(result == float_set(0, 5));
    }

    //Test case 3: OUT_OF_BOUNDS
    {
        uint32_t amt_out;
        int64_t result = float_sto_set(amt_out, 999999);

        trace_num(SBUF("Testcase3: OUT_OF_BOUNDS"), result);
        
        ASSERT(result == -1);
    }

    //Test case 4: NOT_AN_OBJECT
    {
        uint32_t amt_out;
        int64_t result = float_sto_set(SBUF(amt_out));

        trace_num(SBUF("Testcase4: NOT_AN_OBJECT"), result);
    
        ASSERT(result == -23);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
