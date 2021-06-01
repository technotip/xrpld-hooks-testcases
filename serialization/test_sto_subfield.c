/* 
 * sto_subfield
 * Index into a xrpld serialized object and return the location and length of a subfield.
*/

#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t sto_subfield (
    uint32_t read_ptr,
    uint32_t read_len,
    uint32_t field_id
 );
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {
/*
    int64_t hook_acc_id[20];
    hook_account(SBUF(hook_acc_id));
    uint8_t currency[20] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 'U', 'S', 'D', 0,0,0,0,0};

    // Test case 1: PARSE_ERROR: Invalidly serialized object. 
    {
       uint8_t amt_out[48];
       if( float_sto(SBUF(amt_out), SBUF(currency), SBUF(hook_acc_id), float_set(9, 5), 0) < 0)
            rollback(SBUF("Testcase1"), 1);
    
       trace(SBUF("Testcase1: Serialized: "), SBUF(amt_out), 1);

	int64_t test_lookup = sto_subfield(SBUF(amt_out), sfAmount);

	trace(SBUF("What's the amount?"), SBUF(amt_out), 1);

	trace_num(SBUF("testcase1: lookup for sfAmount"), test_lookup);

	ASSERT( -18 == test_lookup );

    }

    //Test case 2: INVALID_FLOAT
    {
       uint8_t amt_out[48];
       int64_t result =  float_sto(SBUF(amt_out), SBUF(currency), SBUF(hook_acc_id), 2, 0); // 4th parameter is INVALID_FLOAT
      
       trace_num(SBUF("Testcase2: INVALID_FLOAT:"), result);
       ASSERT(result == -10024);
    }


    //Test case 3: INVALID_ARGUMENT: -7
    {
       uint8_t amt_out[49];
       int64_t result =  float_sto(SBUF(amt_out), 0, 0, 0, 0, float_set(0, 2), sfAmount); // Last parameter
       
       trace_num(SBUF("Testcase6: INVALID_ARGUMENT:"), result);
       ASSERT(result == -7);
    }

    //Test case 4: TOO_SMALL: -4
    {
       // The API was unable to produce output to the write_ptr because the specified write_len was too small.
       uint8_t amt_out[4]; // Too small. It must be atleast uint8_t amt_out[48];
       int64_t result =  float_sto(SBUF(amt_out), SBUF(currency), SBUF(hook_acc_id), float_set(0, 2), 0);
       
       trace_num(SBUF("Testcase7: TOO_SMALL:"), result);
       ASSERT(result == -4);
    }
*/
    // Test case 5: PARSE_ERROR: Invalidly serialized object. 
    {
   uint8_t memos[] = {  0xEAU, 0x7DU, 0x12U, 0xF0U, 0x9FU, 0x94U, 0xA5U, 0x20U, 0x54U, 0x65U, 0x63U, 0x68U, 0x6EU, 0x6FU, 0x74U, 0x69U, 0x70U, 0x2EU, 0x63U, 0x6FU, 0x6DU, 0xE1U  };

     // check for the presence of a memo
    // uint8_t memos[22];
    // int64_t memos_len = otxn_field(SBUF(memos), sfMemos);	    
     int64_t test_lookup = sto_subfield(SBUF(memos), sfMemo);

       trace(SBUF("Test_lookup for sfMemo"), SBUF(memos), 1);
       trace_num(SBUF("Test_lookup bytes"), test_lookup);

	if (test_lookup < 0)
            trace_num(SBUF("Testcase5: sfAccount not found in the STObject pointed at by result"), test_lookup);
	else
	{
    		// sfMemo was found and its location is as follows:
      		uint8_t  result  = SUB_OFFSET(test_lookup) + result;
      		int64_t  res_len = SUB_LENGTH(test_lookup);

		trace(SBUF("Testcase5: offset"), SBUF(result), 1);
		trace_num(SBUF("Testcase5: Length"), res_len);
	}


       // ASSERT( -18 == test_lookup );

    }    


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}

