all: test_util_sha512h.wasm test_util_keylet.wasm

test_util_sha512h.wasm: test_util_sha512h.c ../testmacro.h
	wasmcc test_util_sha512h.c -o test_util_sha512h.wasm -O0 -Wl,--allow-undefined -I../

test_util_keylet.wasm: test_util_keylet.c ../testmacro.h
	wasmcc test_util_keylet.c -o test_util_keylet.wasm -O0 -Wl,--allow-undefined -I../

