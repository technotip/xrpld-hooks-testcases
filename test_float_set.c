#include "../hookapi.h"
#include "testmacro.h"


int64_t cbak(int64_t reserved) { 
    return 0;
}


int64_t hook(int64_t reserved ) {

    // Testcase 1: Successful transaction
    {

       int64_t small_amount = float_set(10, 1);    
       trace_num(SBUF("1. small amount"), small_amount);
   
       ASSERT(small_amount);
    }

    // Testcase 2: INVALID_FLOAT: Overflow condition
    {

       int64_t small_amount = float_set(81, 1);
       trace_num(SBUF("2. small amount"), small_amount);

       ASSERT(small_amount);
    }

    // Testcase 3: INVALID_FLOAT: Underflow condition
    {

       int64_t small_amount = float_set(-97, 1);
       trace_num(SBUF("3. small amount"), small_amount);
          
       ASSERT(small_amount == -10024);
    }   


    // Testcase 4: Negative Mantissa
    { 
             
       int64_t small_amount = float_set(-96, -1);
       trace_num(SBUF("4. small amount"), small_amount);
          
       ASSERT(small_amount == -10024);
    } 

    // Testcase 5: Canonical 0
    {

       int64_t small_amount = float_set(0, 0);
       trace_num(SBUF("5. small amount"), small_amount);
          
       ASSERT(small_amount == 0);
    }



    // Testcase 6: Value of +PI: expected 6092008288858500385
    {   

       int64_t small_amount = float_set(-15, 3141592653589793);
       trace_num(SBUF("6. small amount"), small_amount);

       ASSERT(small_amount == 6092008288858500385);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;
}
