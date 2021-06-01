all: test_hook_account.wasm test_hook_hash.wasm test_fee_base.wasm test_ledger_seq.wasm test_ledger_last_hash.wasm test_nonce.wasm
	
test_hook_account.wasm: test_hook_account.c ../testmacro.h
	wasmcc test_hook_account.c -o test_hook_account.wasm -O0 -Wl,--allow-undefined -I../

test_hook_hash.wasm: test_hook_hash.c ../testmacro.h
	wasmcc test_hook_hash.c -o test_hook_hash.wasm -O0 -Wl,--allow-undefined -I../

test_fee_base.wasm: test_fee_base.c ../testmacro.h
	wasmcc test_fee_base.c -o test_fee_base.wasm -O0 -Wl,--allow-undefined -I../

test_ledger_seq.wasm: test_ledger_seq.c ../testmacro.h
	wasmcc test_ledger_seq.c -o test_ledger_seq.wasm -O0 -Wl,--allow-undefined -I../

test_ledger_last_hash.wasm: test_ledger_last_hash.c ../testmacro.h
	wasmcc test_ledger_last_hash.c -o test_ledger_last_hash.wasm -O0 -Wl,--allow-undefined -I../

test_nonce.wasm: test_nonce.c ../testmacro.h
	wasmcc test_nonce.c -o test_nonce.wasm -O0 -Wl,--allow-undefined -I../
