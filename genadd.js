const r = require('ripple-keypairs')
const a = require('ripple-address-codec')

const seed = r.generateSeed();
const raddr = r.deriveAddress(r.deriveKeypair(seed).publicKey)
//const accid = a.decodeAccountID(raddr).toString('hex').toUpperCase()

const accid = "DBB01A1D4FCB598EB0A4EB719CF8D6E474985C6D";

let ccode = 'uint8_t accid[] = {';

for (let i = 0; i < 35; ++i)
    ccode += '0x' + accid.slice(i*2, i*2 + 2) + 'U' + (i < 34 ? ',' : '');
ccode += '};'
console.log(raddr, ccode);
