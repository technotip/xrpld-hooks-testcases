/**
 * This hook just accepts any transaction coming through it
 */
#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_negate (
        int64_t float1
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: Negative One or Nagate the one and give -1.
    {
        int64_t negative_one = float_negate(float_one());   
        trace_float(SBUF("negative one"), negative_one);
     
        ASSERT(negative_one); // -1 
    }

    // Test case 2: Negative 5.
    {
        int64_t negative_five = float_negate(float_set(0, 5));
        trace_float(SBUF("Testcase2: negative five"), negative_five);

        ASSERT(negative_five); // -5 
    }

    // Test case 3: Negative of -5 is 5.
    {
        int64_t negative_five = float_negate(float_set(0, 5));
        trace_float(SBUF("Testcase3: Negative five"), negative_five);
        int64_t positive_five = float_negate(negative_five);
        trace_float(SBUF("Testcase3: Positive five"), positive_five);

        ASSERT(positive_five == float_set(0, 5)); // -(-5) =  5.
    }

    // Test case 4: INVALID_FLOAT. Expected return value -10024
    {
        int64_t result = float_negate(2);

        ASSERT(result == -10024); // -1 
    }

    // Test case 5: NEGATIVE ZERO!. Expected return value 0
    {
        int64_t result = float_negate(float_set(0, 0)); // or directly pass 0 to float_negate(0).
        
        trace_num(SBUF("Testcase5: result"), result);
        ASSERT(result == 0); // There is no negative 0. 
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
