#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t hook_account (
    uint32_t write_ptr,
    uint32_t write_len
 );
*/

int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: 
    {
	uint8_t hook_acc_id[20];
        int64_t result1 = hook_account(SBUF(hook_acc_id));
	
	if(result1 != 20)
		rollback(SBUF("Testcase1: Couldn't fetch the hook account."), 1);


	uint8_t accid_out[20];
	uint8_t raddr_in[] = "rJPZnJRABGgAwDG3ibWLdKpmZaPSfhDT5J";   // replace this with the r... address of hook account.

	int64_t result2 =   util_accid(SBUF(accid_out), SBUF(raddr_in));

	int equal = 0; BUFFER_EQUAL(equal, hook_acc_id, accid_out, 20);

	trace(SBUF("Testcase1: result1 "), SBUF(accid_out), 1);
	trace(SBUF("Testcase1: result2 "), SBUF(hook_acc_id), 1);

	trace_num(SBUF("Are they equal?"), equal);

	ASSERT(equal);


    }


    // Test case 2: OUT_OF_BOUNDS   https://github.com/XRPL-Labs/xrpld-hooks/issues/12
    {
        uint8_t hook_acc_id[20];
        int64_t result = hook_account(hook_acc_id, 999999999);
	trace_num(SBUF("Testcase2: no of bytes written "), result);

        if(result != 20)
                rollback(SBUF("Testcase2: Couldn't fetch the hook account."), 1);

        trace(SBUF("Testcase2: hook_acc_id "), SBUF(hook_acc_id), 1); 
         
    } 


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
