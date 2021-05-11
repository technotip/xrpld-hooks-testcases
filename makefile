all: test_util_raddr.wasm test_util_accid.wasm test_util_verify.wasm test_util_sha512h.wasm test_float_set.wasm test_float_multiply.wasm test_float_mulratio.wasm test_float_negate.wasm test_float_compare.wasm test_float_sum.wasm test_float_sto.wasm test_float_sto_set.wasm test_float_invert.wasm test_float_divide.wasm test_float_one.wasm test_float_exponent.wasm test_float_mantissa.wasm test_float_sign.wasm test_float_exponent_set.wasm test_float_mantissa_set.wasm test_float_sign_set.wasm test_float_int.wasm

test_util_raddr.wasm: test_util_raddr.c testmacro.h
	wasmcc test_util_raddr.c -o test_util_raddr.wasm -O0 -Wl,--allow-undefined -I../

test_util_accid.wasm: test_util_accid.c testmacro.h
	wasmcc test_util_accid.c -o test_util_accid.wasm -O0 -Wl,--allow-undefined -I../

test_util_verify.wasm: test_util_verify.c testmacro.h
	 wasmcc test_util_verify.c -o test_util_verify.wasm -O0 -Wl,--allow-undefined -I../

test_util_sha512h.wasm: test_util_sha512h.c testmacro.h
	wasmcc test_util_sha512h.c -o test_util_sha512h.wasm -O0 -Wl,--allow-undefined -I../

test_float_set.wasm: test_float_set.c testmacro.h
	wasmcc test_float_set.c -o test_float_set.wasm -O0 -Wl,--allow-undefined -I../

test_float_multiply.wasm: test_float_multiply.c testmacro.h
	wasmcc test_float_multiply.c -o test_float_multiply.wasm -O0 -Wl,--allow-undefined -I../

test_float_mulratio.wasm: test_float_mulratio.c testmacro.h
	wasmcc test_float_mulratio.c -o test_float_mulratio.wasm -O0 -Wl,--allow-undefined -I../

test_float_negate.wasm: test_float_negate.c testmacro.h
	wasmcc test_float_negate.c -o test_float_negate.wasm -O0 -Wl,--allow-undefined -I../

test_float_compare.wasm: test_float_compare.c testmacro.h
	wasmcc test_float_compare.c -o test_float_compare.wasm -O0 -Wl,--allow-undefined -I../

test_float_sum.wasm: test_float_sum.c testmacro.h
	wasmcc test_float_sum.c -o test_float_sum.wasm -O0 -Wl,--allow-undefined -I../

test_float_sto.wasm: test_float_sto.c testmacro.h
	wasmcc test_float_sto.c -o test_float_sto.wasm -O0 -Wl,--allow-undefined -I../

test_float_sto_set.wasm: test_float_sto_set.c testmacro.h
	 wasmcc test_float_sto_set.c -o test_float_sto_set.wasm -O0 -Wl,--allow-undefined -I../

test_float_invert.wasm: test_float_invert.c testmacro.h
	wasmcc test_float_invert.c -o test_float_invert.wasm -O0 -Wl,--allow-undefined -I../

test_float_divide.wasm: test_float_divide.c testmacro.h
	wasmcc test_float_divide.c -o test_float_divide.wasm -O0 -Wl,--allow-undefined -I../

test_float_one.wasm: test_float_one.c testmacro.h
	wasmcc test_float_one.c -o test_float_one.wasm -O0 -Wl,--allow-undefined -I../

test_float_exponent.wasm: test_float_exponent.c testmacro.h
	wasmcc test_float_exponent.c -o test_float_exponent.wasm -O0 -Wl,--allow-undefined -I../

test_float_mantissa.wasm: test_float_mantissa.c testmacro.h
	wasmcc test_float_mantissa.c -o test_float_mantissa.wasm -O0 -Wl,--allow-undefined -I../

test_float_sign.wasm: test_float_sign.c testmacro.h
	wasmcc test_float_sign.c -o test_float_sign.wasm -O0 -Wl,--allow-undefined -I../

test_float_exponent_set.wasm: test_float_exponent_set.c testmacro.h
	wasmcc test_float_exponent_set.c -o test_float_exponent_set.wasm -O0 -Wl,--allow-undefined -I../

test_float_mantissa_set.wasm: test_float_mantissa_set.c testmacro.h
	wasmcc test_float_mantissa_set.c -o test_float_mantissa_set.wasm -O0 -Wl,--allow-undefined -I../

test_float_sign_set.wasm: test_float_sign_set.c testmacro.h
	wasmcc test_float_sign_set.c -o test_float_sign_set.wasm -O0 -Wl,--allow-undefined -I../

test_float_int.wasm: test_float_int.c testmacro.h
	wasmcc test_float_int.c -o test_float_int.wasm -O0 -Wl,--allow-undefined -I../
