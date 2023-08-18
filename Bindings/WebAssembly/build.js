const fs = require('fs');
const path = require('path');
const { promisify } = require('util');
const exec = promisify(require('child_process').exec);

(async ()=> {

    console.log('DoxaJs - Doxa Binarization Framework WASM Build');

    const release = process.argv[2] !== '-d';
    console.log('Build: ' + (release ? 'Release' : 'Debug'));

    // Use their system compiler, if setup
    let compiler = 'em++'
    const version = await exec(`${compiler} -v`).then(()=>true).catch(()=>false);

    // If not, use our local instance
    if (version) {
        console.log('Using existing em++ compiler')
    }
    else {

        // Get build directory
        const buildDir = 'build';

        compiler = path.join(buildDir, 'emsdk', 'upstream', 'emscripten', 'em++');

        // If a local instance does not exist, get one.
        if (!fs.existsSync(buildDir)) { 

            fs.mkdirSync(buildDir);

            console.log('Cloning emscripten-core');
            await exec(`git -C ./${buildDir} clone https://github.com/emscripten-core/emsdk.git`);

            console.log('Installing latest')
            await exec(`cd ./${buildDir}/emsdk && .${path.sep}emsdk install latest`);

            console.log('Activating latest');
            await exec(`cd ./${buildDir}/emsdk && .${path.sep}emsdk activate latest`);
        }

        console.log('Using local em++ compiler');
    }

    // Compile DoxaJs Web Assembly
    const build = release ?
    // Release
    [
        `${compiler}`,
        '-O3',
        '-o ./dist/doxaWasm.js',
        'DoxaWasm.cpp',
        '-std=c++17',
        '-s WASM=1',
        '-s NO_EXIT_RUNTIME=1',
        '-s ALLOW_MEMORY_GROWTH=1',
        `-s EXPORTED_FUNCTIONS="['_malloc','_free']"`,
        '--bind'
    ]
    : // Debug
    [
        `${compiler}`,
        '-O0',
        '-o ./dist/doxaWasm.js',
        'DoxaWasm.cpp',
        '-std=c++17',
        '-s WASM=1',
        '-s NO_EXIT_RUNTIME=1',
        '-s ALLOW_MEMORY_GROWTH=1',
        `-s EXPORTED_FUNCTIONS="['_malloc','_free']"`,
        '--bind',
        '-g4 ',
        '--source-map-base http://localhost:8080/'
    ];

    console.log('Compiling');
    await exec(build.join(' '));

    // Copy JS Wrapper
    fs.copyFileSync('doxa.js', './dist/doxa.js');

    console.log('Output folder: ./dist');
})();