if (process.argv.length < 3)
{
    console.log("Usage: node peggy <family seed>")
    process.exit(1)
}
const keypairs = require('ripple-keypairs');
const secret  = process.argv[2];
const address = keypairs.deriveAddress(keypairs.deriveKeypair(secret).publicKey)


const RippleAPI = require('ripple-lib').RippleAPI;
const fs = require('fs');
const api = new RippleAPI({server: 'ws://localhost:6005'});
api.on('error', (errorCode, errorMessage) => {
  console.log(errorCode + ': ' + errorMessage);
});
api.on('connected', () => {
  console.log('connected');
});
api.on('disconnected', (code) => {
  console.log('disconnected, code:', code);
});
api.connect().then(() => {

    binary = fs.readFileSync('oracle.wasm').toString('hex').toUpperCase();
    

j = {
    "TransactionType": "OfferCreate",
    "Account": "r4muunLGg8RCcKvKWxN4aw3aJfVz54LgNo",
    "Fee": "12",
 //   "Flags": 0,
 //   "LastLedgerSequence": 7108682,
 //   "Sequence": 8,
    "TakerGets": "6000000",
    "TakerPays": {
      "currency": "XRP",
      "issuer": "rrrrrrrrrrrrrrrrrrrrrhoLvTp",
      "value": "2"
    }
}	

    api.prepareTransaction(j).then((x)=>
    {
        s = api.sign(x.txJSON, secret)
        console.log(s)
        api.submit(s.signedTransaction).then( response => {
            console.log(response.resultCode, response.resultMessage);
            console.log("Done!")
            process.exit()
        }).catch ( e=> { console.log(e) });
    });

}).then(() => {}).catch(console.error);


