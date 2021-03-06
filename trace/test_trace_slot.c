/*
 * trace
 * Write the contents of a buffer to the XRPLD trace log.
*/

#include "../hookapi.h"
#include "../testmacro.h"

/*
 int64_t trace (
    uint32_t mread_ptr,
    uint32_t mread_len,
    uint32_t dread_ptr,
    uint32_t dread_len,
    uint32_t as_hex
 );
*/


int64_t cbak(int64_t reserved) { 
    return 0;
}

int64_t hook(int64_t reserved ) {

// the oracle is the limit set on a trustline established between two special oracle accounts

uint8_t oracle_lo[20] = { // require('ripple-address-codec').decodeAccountID('rXUMMaPpZqPutoRszR29jtC8amWq3APkx')
    0x05U, 0xb5U, 0xf4U, 0x3aU, 0xf7U,
    0x17U, 0xb8U, 0x19U, 0x48U, 0x49U, 0x1fU, 0xb7U, 0x07U, 0x9eU, 0x4fU, 0x17U, 0x3fU, 0x4eU, 0xceU, 0xb3U};

uint8_t oracle_hi[20] = { // require('ripple-address-codec').decodeAccountID('r9PfV3sQpKLWxccdg3HL2FXKxGW2orAcLE')
    0x5bU, 0xefU, 0x92U, 0x1aU, 0x21U,
    0x7dU, 0x57U, 0xfdU, 0xa5U, 0xb5U, 0x6dU, 0x5bU, 0x40U, 0xbeU, 0xe4U, 0x0dU, 0x1aU, 0xc1U, 0x12U, 0x7fU};

      uint8_t currency[20] = {0,0,0,0, 0,0,0,0, 0,0,0,0,  'U', 'S', 'D',  0,0,0,0,0};
/*
      // get the account the hook is running on and the account that created the txn
      uint8_t hook_accid[20];
      hook_account(SBUF(hook_accid));

      uint8_t otxn_accid[20];
      int32_t otxn_accid_len = otxn_field(SBUF(otxn_accid), sfAccount);
      if (otxn_accid_len < 20)
          rollback(SBUF("sfAccount field missing!!!"), 10);

      trace(SBUF("Hook a/c "), SBUF(otxn_accid), 1);
      trace(SBUF("A/c that created the transaction "), SBUF(hook_accid), 1);
*/

    // Test case 1:  KEYLET_LINE
    {
        // check if a trustline exists between the sender and the hook account.
        uint8_t keylet[34];
        int64_t result = util_keylet(SBUF(keylet), KEYLET_LINE, SBUF(oracle_hi), SBUF(oracle_lo), SBUF(currency));

        if(result != 34)
                rollback(SBUF("Internal error, could not generate keylet"), 10);

        trace(SBUF("Testcase1: keylet"), SBUF(keylet), 1);

        int64_t slot_no =  slot_set(SBUF(keylet), 0);
        trace_num(SBUF("Testcase1: slot_no"), slot_no);

	trace_slot(SBUF("Testcase1: trace_slot"), 1);	

        ASSERT( result == 34 ); // Expected: 34. 34 bytes written into butter referenced by keylet.
    }


    // Test case 2:  OUT_OF_BOUNDS
    {
        int64_t result =  trace_slot("Testcase2: trace_slot", 999999999, 1);
	trace_num(SBUF("Testcase2: "), result);

        ASSERT( result == -1 );
    }    

    // Test case 3:  DOESNT_EXIST
    { 
        int64_t result =  trace_slot(SBUF("Testcase3: trace_slot"), 2);
        trace_num(SBUF("Testcase3: "), result);
    
        ASSERT( result == -5 );
    }     


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;

}
