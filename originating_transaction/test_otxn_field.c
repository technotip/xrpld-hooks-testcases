/*
 * otxn_field
 * Serialize and output a field from the originating transaction.
*/

#include "../hookapi.h"
#include "../testmacro.h"

/*
 int64_t otxn_burden (
     void
 );
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

    // Test case 1: fetching sfAccount field value.
    {
	uint8_t account_field[20];

	int64_t result = otxn_field(SBUF(account_field), sfAccount);
	if(result != 20)
		rollback(SBUF("Tescase1: we screwed up!"), 100);

	trace(SBUF("Testcase1: account field"), SBUF(account_field), 1);
    }

    // Test case 2: OUT_OF_BOUNDS.
    {
        uint8_t account_field[20];

        int64_t result = otxn_field(account_field, 9999999, sfAmount);

        trace(SBUF("Testcase2: it must be empty "), SBUF(account_field), 1);
	trace_num(SBUF("Testcase2: result"), result);

	ASSERT(result == -1); // OUT_OF_BOUNDS == -1. account_field: 0000000000000000000000000000000000000000
    }    

    // Test case 3: TOO_SMALL.
    {
        uint8_t account_field[10];

        int64_t result = otxn_field(SBUF(account_field), sfAccount);
        
	trace(SBUF("Testcase3: empty "), SBUF(account_field), 1);
	trace_num(SBUF("Testcase3: result"), result);

	ASSERT(result == -4); // TOO_SMALL
    }    

    // Test case 4: INVALID_FIELD.
    {
        uint8_t account_field[20];

        int64_t result = otxn_field(SBUF(account_field), 1);  // 2nd parameter is Invalid.

        trace(SBUF("Testcase4: empty "), SBUF(account_field), 1);
        trace_num(SBUF("Testcase4: result"), result);

        ASSERT(result == -17); // TOO_SMALL
    }    


    // Test case 5: DOESNT_EXIST.
    {
        uint8_t account_field[20];

        int64_t result = otxn_field(SBUF(account_field), sfMetadata);  // 2nd parameter: When sfMetadata doesn't exist with the transaction.

        trace(SBUF("Testcase5: empty "), SBUF(account_field), 1);
        trace_num(SBUF("Testcase5: result"), result);

        ASSERT(result == -5); // DOESNT_EXIST
    }

    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
