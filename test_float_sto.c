#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_sto (
        uint32_t write_ptr,
        uint32_t write_len,
        uint32_t cread_ptr,
        uint32_t cread_len,  
        uint32_t iread_ptr,
        uint32_t iread_len,  
        int64_t float1,
        uint32_t field_code
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    int64_t hook_acc_id[20];
    hook_account(SBUF(hook_acc_id));
    uint8_t currency[20] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 'U', 'S', 'D', 0,0,0,0,0};

    // Test case 1: Serialize currency code, hook a/c, amount. 
    {
       uint8_t amt_out[8];
       int64_t result = float_sto(SBUF(amt_out), SBUF(currency), SBUF(hook_acc_id), float_set(9, 5), 0);
//       if(float_sto(SBUF(amt_out), SBUF(currency), SBUF(hook_acc_id), float_set(0, 5), 0) < 0)
//        rollback(SBUF("Testcase1"), 1);
    
       trace(SBUF("Testcase1: Serialized: "), SBUF(amt_out), 1);
       trace_num(SBUF("Testcase1: result "), result);
    }

    //Test case 2: INVALID_FLOAT
    {
       uint8_t amt_out[48];
       int64_t result =  float_sto(SBUF(amt_out), SBUF(currency), SBUF(hook_acc_id), 2, 0); // 4th parameter is INVALID_FLOAT
      
       trace_num(SBUF("Testcase2: INVALID_FLOAT:"), result);
       ASSERT(result == -10024);
    }

    //Test case 3: OUT_OF_BOUNDS https://github.com/XRPL-Labs/xrpld-hooks/issues/9
    {
       uint8_t amt_out[48];
       int64_t result =  float_sto(SBUF(amt_out), SBUF(currency), 0, 999999999, float_set(0, 2), 0); // 4th parameter is OUT_OF_BOUNDS
        
       trace_num(SBUF("Testcase3: OUT_OF_BOUNDS:"), result);
       ASSERT(result == -1);
    }

    //Test case 4: OUT_OF_BOUNDS https://github.com/XRPL-Labs/xrpld-hooks/issues/9
    {
       uint8_t amt_out[48];
       int64_t result =  float_sto(SBUF(amt_out), 0, 999999999, SBUF(hook_acc_id), float_set(0, 2), 0); // 3rd parameter is OUT_OF_BOUNDS
          
       trace_num(SBUF("Testcase4: OUT_OF_BOUNDS:"), result);
       ASSERT(result == -1);
    } 

    //Test case 5: https://github.com/XRPL-Labs/xrpld-hooks/issues/10
    {
       
       uint8_t amt_out[48];      
       int64_t result =  float_sto(SBUF(amt_out), SBUF(currency), SBUF(hook_acc_id), float_set(0, 2), sfAmount); // Last parameter


       trace_num(SBUF("Testcase5: INVALID_ARGUMENT:"), result);
       ASSERT(result == -7);
    }

    //Test case 6: INVALID_ARGUMENT: -7
    {
       uint8_t amt_out[49];
       int64_t result =  float_sto(SBUF(amt_out), 0, 0, 0, 0, float_set(0, 2), sfAmount); // Last parameter
       
       trace_num(SBUF("Testcase6: INVALID_ARGUMENT:"), result);
       ASSERT(result == -7);
    }

    //Test case 7: TOO_SMALL: -4
    {
       // The API was unable to produce output to the write_ptr because the specified write_len was too small.
       uint8_t amt_out[4]; // Too small. It must be atleast uint8_t amt_out[48];
       int64_t result =  float_sto(SBUF(amt_out), SBUF(currency), SBUF(hook_acc_id), float_set(0, 2), 0);
       
       trace_num(SBUF("Testcase7: TOO_SMALL:"), result);
       ASSERT(result == -4);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}

