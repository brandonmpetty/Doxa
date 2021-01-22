# Δoxa Binarization Framework - WebAssembly

## Introduction
This is an **experimental** project that exposes the ΔBF, written in C++, to JavaScript via WebAssembly.  It works both server side and client side.  For a simple example of how it works, checkout the [WebJS](../Demo/WebJS) and [NodeJS](../Demo/NodeJS) demos.


## Building with Emscripten
Release Build
```
em++ -O3 -o ./dist/doxaWasm.js DoxaWasm.cpp -std=c++1z -s WASM=1 -s NO_EXIT_RUNTIME=1 -s ALLOW_MEMORY_GROWTH=1 --bind
```

Debug Build
```
em++ -O0 -o ./dist/doxaWasm.js DoxaWasm.cpp <same as above> -g4 --source-map-base http://localhost:8080/
```

Host the server from the root of this project
```
emrun --no_browser --port 8080 .
```

## License
CC0 - Brandon M. Petty, 2019

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8