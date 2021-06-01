/*
 * otxn_field_txt
 * Output a field from the originating transaction as a human readable string.
*/

#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t otxn_field_txt (
    uint32_t write_ptr,
    uint32_t write_len,
    uint32_t field_id
 );
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: fetching sfAccount field value in human readable string.
    {
	uint8_t output[50];
	int64_t result_len = otxn_field_txt(SBUF(output), sfAccount);

	if(result_len != 50)
		rollback(SBUF("Testcase1: we screwed up!"), 100);

	trace(SBUF("Testcase1: account field"), SBUF(output), 1);
	trace_num(SBUF("Testcase1: result_len"), result_len);
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
