all: test_trace.wasm test_trace_slot.wasm test_trace_num.wasm test_trace_float.wasm
	
test_trace.wasm: test_trace.c ../testmacro.h
	wasmcc test_trace.c -o test_trace.wasm -O0 -Wl,--allow-undefined -I../

test_trace_slot.wasm: test_trace_slot.c ../testmacro.h
	wasmcc test_trace_slot.c -o test_trace_slot.wasm -O0 -Wl,--allow-undefined -I../

test_trace_num.wasm: test_trace_num.c ../testmacro.h
	wasmcc test_trace_num.c -o test_trace_num.wasm -O0 -Wl,--allow-undefined -I../

test_trace_float.wasm: test_trace_float.c ../testmacro.h
	wasmcc test_trace_float.c -o test_trace_float.wasm -O0 -Wl,--allow-undefined -I../
