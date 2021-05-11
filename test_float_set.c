#include "../hookapi.h"
#include "testmacro.h"


int64_t cbak(int64_t reserved) { 
    return 0;
}


int64_t hook(int64_t reserved ) {

    // Testcase 1: Successful transaction
    {

       int64_t result = float_set(10, 1);    
       trace_float(SBUF("Testcase1:"), result);
   
       ASSERT(result);
    }

    // Testcase 2: INVALID_FLOAT: EXPONENT_OVERSIZED
    {

       int64_t result = float_set(96, 1);
       trace_num(SBUF("Testcase2:"), result);
	
       ASSERT(result == -28); // Error code -28 represents EXPONENT_OVERSIZED.
    }

    // Testcase 3: INVALID_FLOAT: EXPONENT_UNDERSIZED
    {

       int64_t result = float_set(-97, 1000000000000000);
       trace_num(SBUF("Testcase3:"), result);
       ASSERT(result == -29); // Error code -29 represents EXPONENT_UNDERSIZED.
    }   


    // Testcase 4: Negative Mantissa
    { 
             
       int64_t result = float_set(-96, -1000000000000000);
       trace_num(SBUF("Testcase4:"), result);
          
       ASSERT(result == -10024);
    } 

    // Testcase 5: Canonical 0
    {

       int64_t result = float_set(0, 0);
       trace_num(SBUF("Testcase5:"), result);
          
       ASSERT(result == 0);
    }



    // Testcase 6: Value of +PI
    {   

       int64_t result = float_set(-15, 3141592653589793);
	
       trace_float(SBUF("Testcase6:"), result);
       ASSERT(result == 6092008288858500385);
    }

    // Testcase 7: 
    {

       int64_t result = float_set(0, 123456789123456789);

       trace_float(SBUF("Testcase7:"), result);
       ASSERT(result);
    }    

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;
}
