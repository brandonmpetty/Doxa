# Δoxa Binarization Framework - WebAssembly

This is an **experimental** project that exposes the ΔBF, written in C++, to JavaScript via WebAssembly.

Known Issues:
* Due to the way WASM reallocates memory as it expands, we are forced to set the memory limit at compile time.
* Not currently exposing the Gatos algorithm since it is only partially implemented.

Release Build
```
em++ -O3 -o ./dist/doxaWasm.js doxaWasm.cpp -std=c++1z -s WASM=1 -s NO_EXIT_RUNTIME=1 -s TOTAL_MEMORY=512MB -s "EXTRA_EXPORTED_RUNTIME_METHODS=['writeAsciiToMemory']"
```

Debug Build
```
em++ -O0 -o ./dist/doxaWasm.js doxaWasm.cpp -std=c++1z -s WASM=1 -s NO_EXIT_RUNTIME=1 -s TOTAL_MEMORY=512MB -s "EXTRA_EXPORTED_RUNTIME_METHODS=['writeAsciiToMemory']" -g4 --source-map-base http://localhost:8080/
```

Host the server from the root of this project
```
emrun --no_browser --port 8080 .
```