# Δoxa Binarization Framework - WebAssembly

This is an **experimental** project that exposes the ΔBF, written in C++, to JavaScript via WebAssembly.

Known Issues:
* Not currently exposing the Gatos algorithm since it is only partially implemented.

Release Build
```
em++ -O3 -o ./dist/doxaWasm.js doxaWasm.cpp -std=c++1z -s WASM=1 -s NO_EXIT_RUNTIME=1 -s ALLOW_MEMORY_GROWTH=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['writeAsciiToMemory']"
```

Debug Build
```
em++ -O0 -o ./dist/doxaWasm.js doxaWasm.cpp -std=c++1z -s WASM=1 -s NO_EXIT_RUNTIME=1 -s ALLOW_MEMORY_GROWTH=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['writeAsciiToMemory']" -g4 --source-map-base http://localhost:8080/
```

Host the server from the root of this project
```
emrun --no_browser --port 8080 .
```