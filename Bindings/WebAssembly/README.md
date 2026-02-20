# Δoxa Binarization Framework - WebAssembly

## Introduction
This is an **experimental** project that exposes the ΔBF, written in C++, to JavaScript via WebAssembly.  It works both server side and client side.  For a simple example of how it works, checkout the [WebJS](../../Demo/WebJS) and [NodeJS](../../Demo/NodeJS) demos.

A Visual Studio Code [Notebook](./DoxaJs.nnb) was developed to easily test and document the API.  It uses the *Node.js Notebooks (REPL)* kernel.

## Building

DoxaJs is built using CMake with the Emscripten toolchain. You must have [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) installed and available in your path.

### Using npm (Recommended)

```bash
cd Bindings/WebAssembly
npm install

# Release build
npm run build

# Debug build (with source maps and exception debugging)
npm run build:dev

# Run tests
npm test
```

### Using CMake

```bash
# From project root
cmake --preset wasm
cmake --build build-wasm --config Release
npm install --prefix Bindings/WebAssembly
ctest --test-dir build-wasm -C Release
```

### Run the Web Demo

```bash
emrun --no_browser --port 8080 .
# Navigate to: http://localhost:8080/Demo/WebJS
```


## License
CC0 - Brandon M. Petty, 2023

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8