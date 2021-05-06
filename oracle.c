#include <stdint.h>
#include "../hookapi.h"


// the oracle is the limit set on a trustline established between two special oracle accounts

uint8_t oracle_lo[20] = { // require('ripple-address-codec').decodeAccountID('rXUMMaPpZqPutoRszR29jtC8amWq3APkx')
    0x05U, 0xb5U, 0xf4U, 0x3aU, 0xf7U,
    0x17U, 0xb8U, 0x19U, 0x48U, 0x49U, 0x1fU, 0xb7U, 0x07U, 0x9eU, 0x4fU, 0x17U, 0x3fU, 0x4eU, 0xceU, 0xb3U};

uint8_t oracle_hi[20] = { // require('ripple-address-codec').decodeAccountID('r9PfV3sQpKLWxccdg3HL2FXKxGW2orAcLE')
    0x5bU, 0xefU, 0x92U, 0x1aU, 0x21U,
    0x7dU, 0x57U, 0xfdU, 0xa5U, 0xb5U, 0x6dU, 0x5bU, 0x40U, 0xbeU, 0xe4U, 0x0dU, 0x1aU, 0xc1U, 0x12U, 0x7fU};

int64_t cbak(int64_t reserved)
{   
    return 0;
}

int64_t hook(int64_t reserved)
{
    //    etxn_reserve(1);
    uint8_t currency[20] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 'C', 'S', 'C', 0,0,0,0,0};
    uint8_t keylet[34];

   // CLEARBUF(keylet);
    if (util_keylet(SBUF(keylet), KEYLET_LINE, SBUF(oracle_lo), SBUF(oracle_hi), SBUF(currency)) != 34)
        rollback(SBUF("Peggy: Internal error, could not generate keylet"), 10);

    int64_t slot_no = slot_set(SBUF(keylet), 0);
    TRACEVAR(slot_no);
    if (slot_no < 0)
        rollback(SBUF("Peggy: Could not find oracle trustline"), 10);

    int64_t lim_slot = slot_subfield(slot_no, sfLowLimit, 0);
    if (lim_slot < 0)
        rollback(SBUF("Peggy: Could not find sfLowLimit on oracle trustline"), 20);

    int64_t exchange_rate = slot_float(lim_slot);
    if (exchange_rate < 0)
        rollback(SBUF("Peggy: Could not get exchange rate float"), 20);

    //trace_num(SBUF("XRP Price in USD"), exchange_rate);

    // execution to here means we have retrieved the exchange rate from the oracle
    TRACEXFL(exchange_rate);

    // process the amount sent, which could be either xrp or pusd
    // to do this we 'slot' the originating txn, that is: we place it into a slot so we can use the slot api
    // to examine its internals
/*
    int64_t oslot = otxn_slot(0);
    if (oslot < 0)
        rollback(SBUF("Peggy: Could not slot originating txn."), 1);

    // specifically we're interested in the amount sent
    int64_t amt_slot = slot_subfield(oslot, sfAmount, 0);
    if (amt_slot < 0)
        rollback(SBUF("Peggy: Could not slot otxn.sfAmount"), 2);

    int64_t amt = slot_float(amt_slot);
    if (amt < 0)
        rollback(SBUF("Peggy: Could not parse amount."), 1);

    // the slot_type api allows determination of fields and subtypes of fields according to the doco
    // in this case we're examining an amount field to see if it's a native (xrp) amount or an iou amount
    // this means passing flag=1
    int64_t is_xrp = slot_type(amt_slot, 1);
    if (is_xrp < 0)
        rollback(SBUF("Peggy: Could not determine sent amount type"), 3);
    
    trace_num(SBUF("amount slot"), amt_slot);
*/
    trace(SBUF("Exchange rate"), SBUF(exchange_rate), 1);

    _g(1, 1);
    return 0;
}
