all: test_etxn_burden.wasm

test_etxn_burden.wasm: test_etxn_burden.c ../testmacro.h
	wasmcc test_etxn_burden.c -o test_etxn_burden.wasm -O0 -Wl,--allow-undefined -I../
