all: test_sto_subfield.wasm

test_sto_subfield.wasm: test_sto_subfield.c ../testmacro.h
	wasmcc test_sto_subfield.c -o test_sto_subfield.wasm -O0 -Wl,--allow-undefined -I../
