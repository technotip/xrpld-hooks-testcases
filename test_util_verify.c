#include "../hookapi.h"
#include "testmacro.h"

int64_t cbak(int64_t reserved) { 
    return 0;
}


uint8_t payload[]   = {0x58U,0x52U,0x50U,0x4CU,0x20U,0x4CU,0x41U,0x42U,0x53U}; // "5852504C204C414253"
uint8_t signature[] = {0x30U,0x45U,0x02U,0x21U,0x00U,0xBDU,0xD9U,0xF3U,0x3EU,0x69U,0xFBU,0x93U,0x8BU,0x78U,0x53U,0xF4U,0xDAU,0x6DU,0x55U,0x49U,0x45U,0xAEU,0x85U,0xE6U,0x34U,0x11U,0x29U,0x8FU,0x0CU,0xC9U,0xA5U,0x9AU,0x7BU,0x8DU,0xADU,0xECU,0xEAU,0x02U,0x20U,0x36U,0xA7U,0xCDU,0x78U,0x65U,0xF6U,0x4DU,0x99U,0x2EU,0x95U,0x5AU,0xF7U,0xB0U,0xB2U,0x63U,0xBDU,0x50U,0xB4U,0x3CU,0xC7U,0xBCU,0xEAU,0xD7U,0xD3U,0x2FU,0xFEU,0x36U,0x99U,0x96U,0xEBU,0xE3U,0x59U}; // "3045022100BDD9F33E69FB938B7853F4DA6D554945AE85E63411298F0CC9A59A7B8DADECEA022036A7CD7865F64D992E955AF7B0B263BD50B43CC7BCEAD7D32FFE369996EBE359";
uint8_t publickey[] = {0x02U,0x41U,0xA2U,0xA5U,0x71U,0x6CU,0x24U,0x58U,0x30U,0x6FU,0x70U,0x8CU,0x85U,0xDFU,0x8DU,0x26U,0x97U,0x4FU,0x74U,0x11U,0xF2U,0xEFU,0x62U,0x7CU,0x1AU,0x23U,0xFAU,0xADU,0x8FU,0x3EU,0xC8U,0xB7U,0xCBU}; // "0241A2A5716C2458306F708C85DF8D26974F7411F2EF627C1A23FAAD8F3EC8B7CB";   // family seed: shEXXNvTMxw2rWQ73GCcFRkDU7PV3


int64_t hook(int64_t reserved ) {


    // Testcase 1: Valid Signature        
    {
        int64_t flag =  util_verify(SBUF(payload), SBUF(signature), SBUF(publickey));
        if ( flag )
             trace_num(SBUF("Valid Signature"), flag);        
        else
        {
            trace_num(SBUF("Invalid Signature"), flag);
            rollback("Invalid Signature", 17, 60);
        }
    }


    // Testcase 2: Invalid Signature
    {    
        int64_t flag = util_verify(SBUF("XRPL LABS"), SBUF(signature), SBUF(publickey));
        if ( flag ) // Data/payload should be hashed and in hex formate
             trace_num(SBUF("Valid Signature"), flag);        
        else
        {
            trace_num(SBUF("Invalid Signature"), flag);
           // rollback("Invalid Signature", 17, 60);
        }
    }


    // Testcase 3: OUT_OF_BOUNDS
    {
        int64_t flag = util_verify(payload, 9999999, SBUF(signature), SBUF(publickey));    
        if ( flag == 1 )
             trace_num(SBUF("Valid Signature"), flag);
        else if(flag < 0)
             trace_num(SBUF("OUT_OF_BOUNDS"), flag);
        else
        {
            trace_num(SBUF("Invalid Signature"), flag);
//            rollback("Invalid Signature", 17, 60);
        }
    }


    accept (0,0,0); 

    _g(1,1);   // every hook needs to import guard function and use it at least once
    // unreachable
    return 0;
}
