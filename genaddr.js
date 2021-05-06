const r = require('ripple-keypairs')
const a = require('ripple-address-codec')

const seed = r.generateSeed();
const raddr = r.deriveAddress(r.deriveKeypair(seed).publicKey)
//const accid = a.decodeAccountID(raddr).toString('hex').toUpperCase()

const accid = "0241A2A5716C2458306F708C85DF8D26974F7411F2EF627C1A23FAAD8F3EC8B7CB";

let ccode = 'uint8_t accid[] = {';

for (let i = 0; i < 35; ++i)
    ccode += '0x' + accid.slice(i*2, i*2 + 2) + 'U' + (i < 34 ? ',' : '');
ccode += '};'
console.log(raddr, ccode);

