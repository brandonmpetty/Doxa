# Δoxa Binarization Framework - WebAssembly

## Introduction
This is an **experimental** project that exposes the ΔBF, written in C++, to JavaScript via WebAssembly.  It works both server side and client side.  For a simple example of how it works, checkout the [WebJS](../../Demo/WebJS) and [NodeJS](../../Demo/NodeJS) demos.

A Visual Studio Code [Notebook](./DoxaJs.nnb) was developed to easily test and document the API.  It uses the *Node.js Notebooks (REPL)* kernel.

## Building with NPM
DoxaJs is built using EMScripten and a custom build system exposed through NPM.  If you already have EMScripten installed and configured in your path, it will use your existing em++ compiler.  If not, it will download EMScripten and install it locally in the *build* folder.  All output will be placed in the *dist* folder.  This is a cross platform build system supporting Windows, Linux and OSX.

Release Build
```
npm run build
```

Debug Build
```
npm run build:debug
```

Run Unit Tests
```
npm test
```

To run the Web Demo, run the command below and then navigate to: http://localhost:8080/Demo/WebJS 
```
emrun --no_browser --port 8080 .
```


## License
CC0 - Brandon M. Petty, 2023

To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.

[View Online](https://creativecommons.org/publicdomain/zero/1.0/legalcode)

"*Freely you have received; freely give.*" - Matt 10:8