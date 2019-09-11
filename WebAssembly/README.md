# Δoxa Binarization Framework - WebAssembly

## Introduction
This is an **experimental** project that exposes the ΔBF, written in C++, to JavaScript via WebAssembly.

**Known Issues**
* Not currently exposing the Gatos algorithm since it is only partially implemented.

### Example
```javascript
// Get the 32-bit ImageData object from a Canvas
let canvas = document.getElementById(canvasId);
let ctx = canvas.getContext('2d');
let imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);

// Build 8-bit Doxa Image objects to use in our library
let srcImage = new Doxa.Image().loadFromCanvas(imageData);
let dstImage = new Doxa.Image(srcImage.width, srcImage.height);

// Convert to Binary
Doxa.initialize(Module.Binarization.Algorithms.WOLF, srcImage);
Doxa.toBinary(dstImage, { window: 20, k: 0.18 });

... // Skipping code for building gtImage

// Calculate all performance metrics
let performance = Doxa.calculatePerformance(gtImage, dstImage);
console.log(performance.accuracy.toFixed(4));
```

## Building with Emscripten
Release Build
```
em++ -O3 -o ./dist/doxaWasm.js doxaWasm.cpp -std=c++1z -s WASM=1 -s NO_EXIT_RUNTIME=1 -s ALLOW_MEMORY_GROWTH=1 --bind
```

Debug Build
```
em++ -O0 -o ./dist/doxaWasm.js doxaWasm.cpp <same as above> -g4 --source-map-base http://localhost:8080/
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