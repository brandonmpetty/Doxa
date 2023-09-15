const { loadImage, createCanvas } = require('canvas');
const { Doxa } = require('../dist/doxa.js');

// Note: I would love to give an example of sharp but it cannot live
// in the same project as canvas.  See the DEMO for an example.
//const sharp = require('sharp');


describe("Doxa Binarization Class Test Suite", function() {

    async function readImage(file) {

        const image = await loadImage(file);
        const canvas = createCanvas(image.width, image.height);
        const ctx = canvas.getContext('2d');

        ctx.drawImage(image, 0, 0);

        const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
        return new Doxa.Image(imageData.width, imageData.height, imageData.data);
    }

    beforeAll(async function() {

        // Initializing is required for setting up the WASM module.
        this.Algorithms = await Doxa.initialize();
    });

    it("Binarization toBinary runs successfully", async function() {

        const rgba = new Buffer.from([
            0,0,0,0,    255,255,255,0,  120,120,120,0,
            15,15,15,0, 230,230,230,0,  90,90,90,0,
            5,5,5,0,    245,245,245,0,  69,1100,77,0
        ]);
        const image = new Doxa.Image(3, 3, rgba);

        // Function under test
        const binImage = Doxa.Binarization.toBinary(this.Algorithms.OTSU, image);

        expect(Array.from(binImage.data())).toEqual([
            0, 255, 0,
            0, 255, 0,
            0, 255, 0
        ]);
    });

    it("Binarization calculatePerformance runs successfully", async function() {

        const groundTruthImage = await readImage('../../README/2JohnC1V3-GroundTruth.png');
        const binaryImage = await  readImage('../../README/2JohnC1V3-Sauvola.png');

        const metrics = Doxa.Binarization.calculatePerformance(groundTruthImage, binaryImage);

        expect(metrics.accuracy).toBeCloseTo(97.671, 3);
        expect(metrics.drdm).toBeCloseTo(2.209, 3);
        expect(metrics.fm).toBeCloseTo(93.204, 3);
        expect(metrics.mcc).toBeCloseTo(0.918, 3);
        expect(metrics.nrm).toBeCloseTo(0.048, 3);
        expect(metrics.psnr).toBeCloseTo(16.329, 3);
    });

    it("Algorithm defaults are applied", async function() {

        const image = await readImage('../../README/2JohnC1V3.png');

        const binImage1 = Doxa.Binarization.toBinary(this.Algorithms.SAUVOLA, image);
        const binImage2 = Doxa.Binarization.toBinary(this.Algorithms.SAUVOLA, image, { window: 75, k: 0.2 });
        const binImage3 = Doxa.Binarization.toBinary(this.Algorithms.SAUVOLA, image, { window: 25, k: 0.12 });
    
        expect(binImage1.data()).toEqual(binImage2.data());
        expect(binImage2.data()).not.toEqual(binImage3.data());
    });

});