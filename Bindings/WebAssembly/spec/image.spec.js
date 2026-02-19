const { createCanvas, createImageData } = require('canvas');
const { Doxa } = require('../dist/doxa.js');


describe("Doxa Image Class Test Suite", function() {

    let doxa;

    beforeAll(async function() {

        // Initializing is required for setting up the WASM module.
        doxa = await Doxa.initialize();
    });

    it("Constructor no arguments", function() {

        const image = new Doxa.Image();

        expect(image.width).toBe(0);
        expect(image.height).toBe(0);
        expect(image.size).toBe(0);

        expect(Array.from(image.data())).toEqual([]);

        image.free();
    });

    it("Constructor no Data", function() {

        const image = new Doxa.Image(2, 3);

        expect(image.width).toBe(2);
        expect(image.height).toBe(3);
        expect(image.size).toBe(6);

        // Some compilers might zero out image.data, others will not.

        image.free();
    });

    it("Constructor with 8-bit Data", function() {

        const gray = new Uint8Array([
            255, 0, 128,
            85, 85, 85,
            80, 80, 80
        ]);

        const image = new Doxa.Image(3, 3, gray);

        expect(image.width).toBe(3);
        expect(image.height).toBe(3);
        expect(image.size).toBe(9);

        expect(Array.from(image.data())).toEqual([
            255, 0, 128,
            85, 85, 85,
            80, 80, 80
        ]);

        image.free();
    });

    it("Image Resize", function() {

        const image = new Doxa.Image(2, 3);

        expect(image.width).toBe(2);
        expect(image.height).toBe(3);
        expect(image.size).toBe(6);
        expect(image.bufferSize).toBe(6);

        image.initialize(3,3);

        expect(image.width).toBe(3);
        expect(image.height).toBe(3);
        expect(image.size).toBe(9);
        expect(image.bufferSize).toBe(9); // Buffer grew

        image.initialize(2,1);

        expect(image.width).toBe(2);
        expect(image.height).toBe(1);
        expect(image.size).toBe(2);       // Reflects actual image
        expect(image.bufferSize).toBe(9); // Buffer retained

        image.free();
    });

    it("Grayscale fromImageData", function() {

        const rgba = new createImageData(new Uint8ClampedArray([
            255,255,255,0,   0,0,0,0,      128,128,128,0,
            255,0,0,0,       0,255,0,0,    0,0,255,0,
            70,80,90,0,      90,80,70,0,   80,90,70,0
        ]), 3, 3);

        const image = doxa.fromImageData(rgba);

        // MEAN grayscale: (r+g+b)/3
        expect(Array.from(image.data())).toEqual([
            255, 0, 128,
            85, 85, 85,
            80, 80, 80
        ]);

        image.free();
    });

    it("toImageData", function() {

        const gray = new Uint8Array([
            255, 0, 128,
            85, 85, 85,
            70, 70, 70
        ]);

        const image = new Doxa.Image(3, 3, gray);
        const imageData = new createImageData(3, 3);
        image.toImageData(imageData);

        expect(Array.from(imageData.data)).toEqual([
            255,255,255,255,   0,0,0,255,      128,128,128,255,
            85,85,85,255,      85,85,85,255,   85,85,85,255,
            70,70,70,255,      70,70,70,255,   70,70,70,255
        ]);

        image.free();
    });

    it("draw", function() {

        const canvas = createCanvas(3, 3);

        const rgba = new createImageData(new Uint8ClampedArray([
            255,255,255,0,   0,0,0,0,         128,128,128,0,
            255,0,0,0,       0,255,0,0,       0,0,255,0,
            0,0,0,0,         255,255,255,0,   0,0,0,0,
        ]), 3, 3);

        // Create an Image via Grayscale conversion
        const image = doxa.fromImageData(rgba);

        // Draw image onto our canvas
        image.draw(canvas);

        // Pull data out of the canvas and compare
        const result = canvas.getContext('2d').getImageData(0, 0, image.width, image.height);
        expect(Array.from(result.data)).toEqual([
            255,255,255,255,   0,0,0,255,         128,128,128,255,
            85,85,85,255,      85,85,85,255,      85,85,85,255,
            0,0,0,255,         255,255,255,255,   0,0,0,255
        ]);

        image.free();
    });
});
