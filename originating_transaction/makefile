all: test_otxn_burden.wasm test_otxn_field.wasm test_otxn_field_txt.wasm test_otxn_generation.wasm test_otxn_id.wasm test_otxn_type.wasm test_otxn_slot.wasm
	
test_otxn_burden.wasm: test_otxn_burden.c ../testmacro.h
	wasmcc test_otxn_burden.c -o test_otxn_burden.wasm -O0 -Wl,--allow-undefined -I../

test_otxn_field.wasm: test_otxn_field.c ../testmacro.h
	wasmcc test_otxn_field.c -o test_otxn_field.wasm -O0 -Wl,--allow-undefined -I../

test_otxn_field_txt.wasm: test_otxn_field_txt.c ../testmacro.h
	wasmcc test_otxn_field_txt.c -o test_otxn_field_txt.wasm -O0 -Wl,--allow-undefined -I../

test_otxn_generation.wasm: test_otxn_generation.c ../testmacro.h
	wasmcc test_otxn_generation.c -o test_otxn_generation.wasm -O0 -Wl,--allow-undefined -I../

test_otxn_id.wasm: test_otxn_id.c ../testmacro.h
	wasmcc test_otxn_id.c -o test_otxn_id.wasm -O0 -Wl,--allow-undefined -I../

test_otxn_type.wasm: test_otxn_type.c ../testmacro.h
	wasmcc test_otxn_type.c -o test_otxn_type.wasm -O0 -Wl,--allow-undefined -I../

test_otxn_slot.wasm: test_otxn_slot.c ../testmacro.h
	wasmcc test_otxn_slot.c -o test_otxn_slot.wasm -O0 -Wl,--allow-undefined -I../
