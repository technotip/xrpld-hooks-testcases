#include "../hookapi.h"
#include "testmacro.h"

/*
 int64_t util_keylet (
     uint32_t write_ptr,
     uint32_t write_len,
     uint32_t keylet_type,
     uint32_t a,
     uint32_t b,
     uint32_t c,
     uint32_t d,
     uint32_t e,
     uint32_t f
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
  
      // get the account the hook is running on and the account that created the txn
      uint8_t hook_accid[20];
      hook_account(SBUF(hook_accid));
 
      uint8_t otxn_accid[20];
      int32_t otxn_accid_len = otxn_field(SBUF(otxn_accid), sfAccount);
      if (otxn_accid_len < 20)
          rollback(SBUF("sfAccount field missing!!!"), 10);

      trace(SBUF("Hook a/c "), SBUF(otxn_accid), 1);
      trace(SBUF("A/c that created the transaction "), SBUF(hook_accid), 1);

/*
    // Test case 1:  KEYLET_LINE
    {
    	// check if a trustline exists between the sender and the hook account.
    	uint8_t keylet[34];
    	int64_t result = util_keylet(SBUF(keylet), KEYLET_LINE, SBUF(oracle_hi), SBUF(oracle_lo), SBUF(currency));

	if(result != 34)
		rollback(SBUF("Internal error, could not generate keylet"), 10);	

	trace(SBUF("Testcase1: KEYLET_LINE"), SBUF(keylet), 1);
	
	int64_t slot_no =  slot_set(SBUF(keylet), 0);
	trace_num(SBUF("Testcase1: slot_no"), slot_no);
        
	ASSERT( result == 34 ); // Expected: 34. 34 bytes written into butter referenced by keylet.
    }

    // Test case 2:  KEYLET_HOOK
    {
        uint8_t keylet[34];
        int64_t result = util_keylet(SBUF(keylet), KEYLET_HOOK, SBUF(hook_accid), 0, 0, 0, 0);

        if(result != 34)
                rollback(SBUF("Internal error, could not generate keylet"), 10);       

        trace(SBUF("Testcase2: KEYLET_HOOK"), SBUF(keylet), 1);

	int64_t slot_no = slot_set(SBUF(keylet), 0);
	trace_num(SBUF("Testcase2: slot_no"), slot_no);

        ASSERT( result == 34 ); // Expected: 34. 34 bytes written into butter referenced by keylet.
    }    

    // Test case 3:  KEYLET_HOOK_STATE
    {
	uint8_t key[32];
	uint8_t value[16];
	if (state(SBUF(value), SBUF(key)) == 16)
	        trace(SBUF("Testcase3: Hook State Present"), SBUF(value), 1);
	else
	{
		state_set(SBUF(hook_accid), SBUF(key));	
		state(SBUF(value), SBUF(key));
		trace(SBUF("Testcase3: Hook State Set"), SBUF(hook_accid), 1);
	}

        uint8_t keylet[34];
        int64_t result = util_keylet(SBUF(keylet), KEYLET_HOOK_STATE, SBUF(hook_accid), SBUF(key), 0, 0);

        if(result != 34)
                rollback(SBUF("Internal error, could not generate keylet"), 10);

        trace(SBUF("Testcase3: KEYLET_HOOK_STATE"), SBUF(keylet), 1);

	int64_t slot_no = slot_set(SBUF(keylet), 0);
	trace_num(SBUF("Testcase3: slot_no"), slot_no);
        ASSERT( result == 34 ); // Expected: 34. 34 bytes written into butter referenced by keylet.
    }

    // Test case 4:  KEYLET_ACCOUNT
    { 
        uint8_t keylet[34];
        int64_t result = util_keylet(SBUF(keylet), KEYLET_ACCOUNT, SBUF(otxn_accid), 0, 0, 0, 0);
	

        if(result != 34)
                rollback(SBUF("Internal error, could not generate keylet"), 10);

        trace(SBUF("Testcase4: KEYLET_ACCOUNT"), SBUF(keylet), 1);

	int64_t slot_no = slot_set(SBUF(keylet), 0);
	trace_num(SBUF("Testcase4: slot_no"), slot_no);
        ASSERT( result == 34 ); // Expected: 34. 34 bytes written into butter referenced by keylet.
    }

    // Test case 5:  KEYLET_AMENDMENTS
    { 
        uint8_t keylet[34];
        int64_t result = util_keylet(SBUF(keylet), KEYLET_AMENDMENTS, 0, 0, 0, 0, 0, 0);
        
   
        if(result != 34)
                rollback(SBUF("Testcase5: Internal error, could not generate keylet"), 10);

        trace(SBUF("Testcase5: KEYLET_AMENDMENTS"), SBUF(keylet), 1);

        ASSERT( result == 34 ); // Expected: 34. 34 bytes written into butter referenced by keylet.
    }    
*/

   // Test case 6: KEYLET_SKIP
   {
	uint8_t keylet[34];
	int64_t result = util_keylet(SBUF(keylet), KEYLET_SKIP, 0, 0, 0, 0, 0, 0);	

	trace(SBUF("Testcase6: KEYLET_SKIP"), SBUF(keylet), 1);

	ASSERT( result == 34 );
   }   

   // Test case 7: KEYLET_FEES
   {
	   uint8_t keylet[34];
	   int64_t result = util_keylet(SBUF(keylet), KEYLET_FEES, 0, 0, 0, 0, 0, 0);

	   trace(SBUF("Testcase7: KEYLET_FEES"), SBUF(keylet), 1);

	   ASSERT( result == 34 );
   }

/*
  
   // Test case 8: KEYLET_NEGATIVE_UNL
   {
	   uint8_t keylet[34];
	   int64_t result = util_keylet(SBUF(keylet), KEYLET_NEGATIVE_UNL, 0, 0, 0, 0, 0, 0);

	   trace(SBUF("Testcase 8: KEYLET_NEGATIVE_UNL"), SBUF(keylet), 1);

	   ASSERT( result == 34 );
   }

   //Test case 9: KEYLET_OFFER  // Yet to test this case!
   {
	   uint8_t keylet[34];
	   uint32_t num = 555;
	   int64_t result = util_keylet(SBUF(keylet), KEYLET_OFFER, SBUF(otxn_accid), num, 0, 0, 0);

	   trace(SBUF("Testcase 9: KEYLET_OFFER"), SBUF(keylet), 1);

	   ASSERT( result == 34 );
   }

   //Test case 10: KEYLET_QUALITY // Yet to test this case!
   {     
           uint8_t keylet[34];
           
           int64_t result = util_keylet(SBUF(keylet), KEYLET_QUALITY, SBUF(keylet7), 32_bits_hi, 32_bits_lo, 0, 0);
      
           trace(SBUF("Testcase 10: KEYLET_QUALITY"), SBUF(keylet), 1);

           ASSERT( result == 34 );
   }   
   
   //Test case 11: KEYLET_EMITTED_DIR
   {
	   uint8_t keylet[34];
	   int64_t result = util_keylet(SBUF(keylet), KEYLET_EMITTED_DIR, 0, 0, 0, 0, 0, 0);

	   trace(SBUF("Testcase 11: KEYLET_EMITTED_DIR"), SBUF(keylet), 1);

	   ASSERT( result == 34);
   }
*/   
   //Test case 12: KEYLET_SIGNERS 
   {    
           uint8_t keylet[34];
           int64_t result = util_keylet(SBUF(keylet), KEYLET_SIGNERS, SBUF(otxn_accid), 0, 0, 0, 0);
      
           trace(SBUF("Testcase 12: KEYLET_SIGNERS"), SBUF(keylet), 1);

           ASSERT( result == 34); 
   }

   //Test case 13: KEYLET_OWNER_DIR
   {
	   uint8_t keylet[34];
           int64_t result = util_keylet(SBUF(keylet), KEYLET_OWNER_DIR, SBUF(otxn_accid), 0, 0, 0, 0);
	   trace( SBUF("Testcase 13: KEYLET_OWNER_DIR"), SBUF(keylet), 1);

	   trace_num(SBUF("Testcase 13: result"), result);

	   ASSERT( result == 34 );
   }   

   //Test case 14: KEYLET_OWNER_DIR: OUT_OF_BOUNDS
   {
           uint8_t keylet[34];
           int64_t result = util_keylet(SBUF(keylet), KEYLET_OWNER_DIR, (otxn_accid), 99999, 0, 0, 0, 0);
           trace( SBUF("Testcase 14: KEYLET_OWNER_DIR"), SBUF(keylet), 1);

           trace_num(SBUF("Testcase 14: result"), result);

           ASSERT( result ==  -1 ); //OUT_OF_BOUNDS
   }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;
}
