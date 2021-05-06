#include "../hookapi.h"
#include "testmacro.h"

#define NUMERATOR   6
#define DENOMINATOR 2

/*
int64_t float_multiply (
    int64_t float1,
    uint32_t round_up,
    uint32_t numerator,
    uint32_t denominator
);
*/

int64_t cbak(int64_t reserved) {
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Testcase 1: Expected result: 6 in XFL format
    {
        int64_t amount      = float_set(0, 2); // amount = 2 (in XFL format)
        int64_t result      = float_mulratio(amount, 0, NUMERATOR, DENOMINATOR); // This should give 2 x 3 = 6 (in XFL format)

        trace_float(SBUF("Testcase1: amount"), amount); // amount = 2 
        trace_float(SBUF("Testcase1: result"), result); // result = 6


        ASSERT(result == float_set(0, 6)); // They are both equal in XFL format!
    }

   // Testcase 2: INVALID_FLOAT. Expected return value is -10024
   {
        int64_t result      = float_mulratio(2, 0, NUMERATOR, DENOMINATOR); // First parameter is not in XFL number format
        trace_num(SBUF("Testcase2: result"), result);

        ASSERT(result == -10024);           // Since -24 falls within the exponent range of -97 and 80, we've added -10024 as the error code!
        
   } 

   // Testcase 3: OVERFLOW Condition. Expected return value is -30
   {
        int64_t result      = float_mulratio(float_set(80, 9999999999999999), 0, NUMERATOR, DENOMINATOR); // First parameter has very large floating point no.
        trace_num(SBUF("Testcase3: result"), result);

        ASSERT(result == -30);

   }

   // Testcase 4: DIVISION_BY_ZERO. Expected return value is -25
   {
        int64_t result      = float_mulratio(float_set(0, 2), 0, NUMERATOR, 0); // First parameter is not in XFL number format
        trace_num(SBUF("Testcase4: result"), result);

        ASSERT(result == -25);   
   }


    _g(1, 1);
    accept(0, 0, 0);
    return 0;
}
