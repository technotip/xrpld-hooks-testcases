if (process.argv.length < 3)
{
    console.log("Usage: node accept <account family seed>")
    process.exit(1);
}
const RippleAPI = require('ripple-lib').RippleAPI;
const keypairs = require('ripple-keypairs');
const fs = require('fs');
const api = new RippleAPI({server: 'ws://localhost:6005'});

const secret  = process.argv[2];
const address = keypairs.deriveAddress(keypairs.deriveKeypair(secret).publicKey)

api.on('error', (errorCode, errorMessage) => {console.log(errorCode + ': ' + errorMessage);});
api.on('connected', () => {console.log('connected');});
api.on('disconnected', (code) => {console.log('disconnected, code:', code);});
api.connect().then(() => {
    j = {
        Account: address,
        TransactionType: "SetHook",
        CreateCode: '',
        HookOn: '0000000000000000'
    }
    api.prepareTransaction(j).then( (x)=> 
    {
        let s = api.sign(x.txJSON, secret)
        console.log(s)
        api.submit(s.signedTransaction).then( response => {
            console.log(response.resultCode, response.resultMessage);
	    j = {
		Account: address,
		TransactionType: "SetHook",
		CreateCode: '',
		HookOn: '0000000000000000'
	    }
	    api.prepareTransaction(j).then( (x)=> 
	    {
		let s = api.sign(x.txJSON, secret)
		console.log(s)
		api.submit(s.signedTransaction).then( response => {
		    console.log(response.resultCode, response.resultMessage);
		    process.exit(0);        
		}).catch ( e=> { console.log(e) });
	    });
        }).catch ( e=> { console.log(e) });
    });
}).then(() => {}).catch(console.error);
