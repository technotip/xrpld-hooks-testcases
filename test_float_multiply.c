#include "../hookapi.h"
#include "testmacro.h"

/*
int64_t float_multiply (
    int64_t float1,
    int64_t float2
);
*/

int64_t cbak(int64_t reserved) {
    return 0;
}

int64_t hook(int64_t reserved ) {

       // Test case 1: Expected result 6092008288858500385
       {
        int64_t float1 =  float_set(-15, 3141592653589793); // +PI: 6092008288858500385
        int64_t float2 =  float_set(-15, 1000000000000000); // 5820650718562680832
        // PI * 1 = PI; 
        int64_t result = float_multiply(float1, float2); // 6092008288858500385

        trace_num(SBUF("testcase1 result"), result); 

        ASSERT(result);  
       }

       // Test case 2: OVERFLOW: -30
       {
        int64_t float1 =  float_set(80, 9999999999999999); 
        int64_t float2 =  float_set(80, 9999999999999999); 
        // The result of the multiplication was too large to store in an XFL.
        int64_t result = float_multiply(float1, float2);

        trace_num(SBUF("testcase2 result"), result); 
          
        ASSERT(result == -30);  
       }

       // Test case 3: INVALID_FLOAT: INVALID XFL
       {
        int64_t float1 =  float_set(100, 99999999999999); // invalid exponent
        int64_t float2 =  float_set(80, 9999999999999999);
  
        int64_t result = float_multiply(float1, float2);
    
        trace_num(SBUF("testcase3 result"), result);  
          
        ASSERT(result == -10024);  
       }    

      accept(0, 0, 0);
      _g(1, 1);
      return 0;
   
    
}
