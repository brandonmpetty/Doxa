const { createCanvas, createImageData } = require('canvas');
const { Doxa } = require('../dist/doxa.js');


describe("Doxa Image Class Test Suite", function() {

    beforeAll(async function() {

        // Initializing is required for setting up the WASM module.
        this.Algorithms = await Doxa.initialize();
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

    it("Constructor with Data", function() {

        const rgba = [
            255,255,255,0,   0,0,0,0,      128,128,128,0,
            255,0,0,0,       0,255,0,0,    0,0,255,0,
            70,80,90,0,      90,80,70,0,   80,90,70,0
        ];

        const image = new Doxa.Image(3, 3, rgba);

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
        expect(image.size).toBe(6); // Initialize Size

        image.initialize(3,3);

        expect(image.width).toBe(3);
        expect(image.height).toBe(3);
        expect(image.size).toBe(9); // Buffer Increased

        image.initialize(2,1);

        expect(image.width).toBe(2);
        expect(image.height).toBe(1);
        expect(image.size).toBe(9); // Buffer Retained

        image.free();
    });

    it("to8BitImage", async function() {

        const rgba = new createImageData(new Uint8ClampedArray([
            255,255,255,0,   0,0,0,0,      128,128,128,0,
            255,0,0,0,       0,255,0,0,    0,0,255,0,
            70,80,90,0,      90,80,70,0,   80,90,70,0
        ]), 3, 3);

        const gray = [];

        const image = new Doxa.Image();
        image.to8BitImage(gray, rgba);

        expect(gray).toEqual([
            255, 0, 128,
            85, 85, 85,
            80, 80, 80
        ]);
    });

    it("from8BitImage", function() {

        const _8bit = [
            255, 0, 128,
            85, 85, 85,
            70, 70, 70
        ];

        const _32bit = new createImageData(3, 3);

        const image = new Doxa.Image();
        image.from8BitImage(_32bit, _8bit);

        expect(Array.from(_32bit.data)).toEqual([
            255,255,255,255,   0,0,0,255,      128,128,128,255,
            85,85,85,255,      85,85,85,255,   85,85,85,255,
            70,70,70,255,      70,70,70,255,   70,70,70,255
        ]);
    });

    it("draw", function() {

        const canvas = createCanvas(3, 3);

        const rgba = [
            255,255,255,0,   0,0,0,0,         128,128,128,0,
            255,0,0,0,       0,255,0,0,       0,0,255,0,
            0,0,0,0,         255,255,255,0,   0,0,0,0,
        ];

        // Create an Image object that will be converted to Grayscale
        // Doxa only processes 8bit images
        const image = new Doxa.Image(3, 3, rgba);

        // Draw image onto our canvas
        image.draw(canvas);

        // Pull data out of the canvas and compare
        const result = canvas.getContext('2d').getImageData(0, 0, image.width, image.height);
        expect(Array.from(result.data)).toEqual([
            255,255,255,255,   0,0,0,255,         128,128,128,255,
            85,85,85,255,      85,85,85,255,      85,85,85,255,
            0,0,0,255,         255,255,255,255,   0,0,0,255
        ]);
    });
});