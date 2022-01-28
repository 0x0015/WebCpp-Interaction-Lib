all:
	em++ main.cpp ../libDOMscripten.a -o main.js -std=c++17 -s WASM=1 -s EXPORTED_RUNTIME_METHODS=ccall,cwrap -s ASSERTIONS=1

clean:
	rm -f main.js
