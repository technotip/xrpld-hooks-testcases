all: test_state_set.wasm test_state.wasm test_state_foreign.wasm

test_state_set.wasm: test_state_set.c ../testmacro.h
	wasmcc test_state_set.c -o test_state_set.wasm -O0 -Wl,--allow-undefined -I../

test_state.wasm: test_state.c ../testmacro.h
	wasmcc test_state.c -o test_state.wasm -O0 -Wl,--allow-undefined -I../

test_state_foreign.wasm: test_state_foreign.c ../testmacro.h
	wasmcc test_state_foreign.c -o test_state_foreign.wasm -O0 -Wl,--allow-undefined -I../
