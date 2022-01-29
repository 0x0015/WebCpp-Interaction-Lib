all:
	em++ main.cpp ../libDOMscripten.a -o main.js -std=c++17 -s WASM=1 -s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s ASSERTIONS=1 -s NO_DISABLE_EXCEPTION_CATCHING -fexceptions -s EXCEPTION_DEBUG

clean:
	rm -f main.js main.wasm
