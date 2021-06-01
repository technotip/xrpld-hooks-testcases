if (process.argv.length < 4)
{
    console.log("Usage: node test_util_raddr <account family seed> <test case>")
    process.exit(1);
}
const RippleAPI = require('ripple-lib').RippleAPI;
const keypairs = require('ripple-keypairs');
const fs = require('fs');
const api = new RippleAPI({server: 'ws://localhost:6005'});

const secret  = process.argv[2];
const address = keypairs.deriveAddress(keypairs.deriveKeypair(secret).publicKey)

const testcase = process.argv[3];

api.on('error', (errorCode, errorMessage) => {console.log(errorCode + ': ' + errorMessage);});
api.on('connected', () => {console.log('connected');});
api.on('disconnected', (code) => {console.log('disconnected, code:', code);});
api.connect().then(() => {
    binary = fs.readFileSync('test_'+testcase+'.wasm').toString('hex').toUpperCase();
    j = {
        Account: address,
        TransactionType: "SetHook",
        CreateCode: binary,
        HookOn: '0000000000000000'
    }
    api.prepareTransaction(j).then( (x)=>
    {
        let s = api.sign(x.txJSON, secret)
        console.log(s)
        api.submit(s.signedTransaction).then( response => {

        if (response.resultCode != 'tesSUCCESS')
            process.exit(2);

		console.log(response.resultCode, response.resultMessage);
		const amount = 2000000n;
		const dest = "rDADDYfnLvVY9FBnS8zFXhwYFHPuU5q2Sk";
		const hook_account = dest;

		const RippleAPI = require('ripple-lib').RippleAPI;
		const fs = require('fs');
		const api = new RippleAPI({server: 'ws://localhost:6005'});
		api.on('error', (errorCode, errorMessage) => {console.log(errorCode + ': ' + errorMessage);});
		api.on('connected', () => {console.log('connected');});
		api.on('disconnected', (code) => {console.log('disconnected, code:', code);});
		api.connect().then(() => {
		    let j = {
			Account: address,
			TransactionType: "Payment",
			Amount: "" + amount,
			Destination: dest,
			Fee: "10000",
  		        Memos: [
    {
        Memo: {
        MemoData: "F09F94A520546563686E6F7469702E636F6D"
      }
    }
  ]
		    }
		    api.prepareTransaction(j).then((x)=>
		    {
			s = api.sign(x.txJSON, secret)
			console.log(s)
			api.submit(s.signedTransaction).then( response => {
			    console.log(response.resultCode); //, response.resultMessage);
			    
                if (response.resultCode == 'tesSUCCESS')
                    process.exit(0); // success
                process.exit(1);
                /*let countdown = (x)=>{
				if (x <= 0)
				    return console.log("")
				process.stdout.write(x + "... ");
				setTimeout(((x)=>{ return ()=>{countdown(x);} })(x-1), 1000);
			    };
			    countdown(10);
			    setTimeout(
			    ((txnhash)=>{
				return ()=>{
				    api.getTransaction(txnhash, {includeRawTransaction: true}).then(
					x=>{
					    execs = JSON.parse(x.rawTransaction).meta.HookExecutions;
					    for (y in execs)
					    {
						exec = execs[y].HookExecution;
						if (exec.HookAccount == hook_account)
						{
						    console.log("Hook Returned: ",
							Buffer.from(exec.HookReturnString, 'hex').toString('utf-8'));
						    process.exit(0);
						}
					    }
					    console.log("Could not find return from hook");
					    process.exit(1);
					});
				}
			    })(s.id), 10000); */
			}).catch (e=> { console.log(e) });
		    });
		}).then(() => {}).catch(console.error);
        }).catch ( e=> { console.log(e) });
    });
}).then(() => {}).catch(console.error);
