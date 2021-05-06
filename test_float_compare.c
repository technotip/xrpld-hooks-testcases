/**
 * This hook just accepts any transaction coming through it
 */
#include "../hookapi.h"
#include "testmacro.h"

/*
    int64_t float_compare (
        int64_t float1,
        int64_t float2,
        uint32_t mode
    );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: 1 COMPARE_EQUAL 1. TRUE.
    {
        if(float_compare(float_one(), float_one(), COMPARE_EQUAL) == 1)    // 1 represents True.
        {
            trace_num(SBUF("Testcase1: True"), 1);
            ASSERT(1);
        } 
        else
        {
            trace_num(SBUF("Testcase1: False"), 0);
            ASSERT(0);
        }
        
    }

    // Test case 2: 1 COMPARE_EQUAL 1. If TRUE, then execute code in else block.
    {
        if(float_compare(float_one(), float_one(), COMPARE_EQUAL) == 0)    // 0 represents False.
        {
            trace_num(SBUF("Testcase2: True"), 1);
            ASSERT(1);
        } 
        else
        {
            trace_num(SBUF("Testcase2: False"), 0);
            ASSERT(1); // If we pass 0 to ASSERT, the hook execution will be terminated. ROLLBACK.
        }
        
    }

    // Test case 3: INVALID_FLOAT
    {
        int64_t result = float_compare(1, 1.000, COMPARE_EQUAL);
        trace_num(SBUF("Testcase3: "), result);
        ASSERT(result == -10024);
    }

    // Test case 4: float(2, 3) is equal to 6127895493223874560. So float_compare() must return TRUE or 1.
    {
        int64_t result = float_compare(float_set(2, 3), 6127895493223874560, COMPARE_EQUAL);
        trace_num(SBUF("Testcase4: "), result);
        ASSERT(result == 1);
    }

    // Test case 5: INVALID_ARGUMENT. Expected return value is -7.
    {
        // It can't satisfy all the supplied comparison flags COMPARE_GREATER, COMPARE_LESS, COMPATE_EQUAL.
        int64_t result = float_compare(float_set(2, 3), 6127895493223874560, COMPARE_GREATER | COMPARE_LESS | COMPARE_EQUAL); 
        trace_num(SBUF("Testcase5: "), result);
        ASSERT(result == -7);
    }

    // Test case 6: COMPARE_GREATER | COMPARE_LESS. It means, NOT EQUAL TO.
    {
        // 1 != 3. So it'll return TRUE/1.
        int64_t result = float_compare(float_set(0, 3), float_one(), COMPARE_GREATER | COMPARE_LESS); 
        trace_num(SBUF("Testcase6: "), result);
        ASSERT(result == 1);
    }

    // Test case 7: Same as testcase 6, but we are checking for COMPARE_EQUAL - which should return FALSE/0.
    {
        // 1 != 3. So it'll return TRUE/1.
        int64_t result = float_compare(float_set(0, 3), float_one(), COMPARE_EQUAL);
        trace_num(SBUF("Testcase7: "), result);
        ASSERT(result == 0);
    }


    // Test case 8: Greater than or Equal to.
    {
        // 3 >= 1. It'll return TRUE/1.
        int64_t result = float_compare(float_set(0, 3), float_one(), COMPARE_GREATER |  COMPARE_EQUAL);
        trace_num(SBUF("Testcase8: "), result);
        ASSERT(result == 1);
    }

    // Test case 9: Less than or Equal to.
    {
        // 3 <= 1. It'll return FALSE/0.
        int64_t result = float_compare(float_set(0, 3), float_one(), COMPARE_LESS |  COMPARE_EQUAL);
        trace_num(SBUF("Testcase9: "), result);
        ASSERT(result == 0);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
