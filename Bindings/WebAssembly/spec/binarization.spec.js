const fs = require('fs');
const path = require('path');
const { loadImage, createCanvas } = require('canvas');
const { Doxa } = require('../dist/doxa.js');

// Note: I would love to give an example of sharp but it cannot live
// in the same project as canvas.  See the DEMO for an example.
//const sharp = require('sharp');


describe("Doxa Binarization Class Test Suite", function() {

    let doxa;

    async function readImage(file) {

        const image = await loadImage(file);
        const canvas = createCanvas(image.width, image.height);
        const ctx = canvas.getContext('2d');

        ctx.drawImage(image, 0, 0);

        const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
        return doxa.fromImageData(imageData);
    }

    beforeAll(async function() {

        // Initializing is required for setting up the WASM module.
        doxa = await Doxa.initialize();
    });

    it("Binarization toBinary runs successfully", async function() {

        const rgba = new Buffer.from([
            0,0,0,0,    255,255,255,0,  120,120,120,0,
            15,15,15,0, 230,230,230,0,  90,90,90,0,
            5,5,5,0,    245,245,245,0,  69,1100,77,0
        ]);
        const image = doxa.toGrayscale(rgba, 3, 3, 4);

        // Function under test
        const binImage = doxa.toBinary(doxa.binarization.OTSU, image);

        expect(Array.from(binImage.data())).toEqual([
            0, 255, 0,
            0, 255, 0,
            0, 255, 0
        ]);
    });

    it("Binarization calculatePerformance runs successfully", async function() {

        const groundTruthImage = await readImage('../../README/2JohnC1V3-GroundTruth.png');
        const binaryImage = await  readImage('../../README/2JohnC1V3-Sauvola.png');

        const metrics = doxa.calculatePerformance(groundTruthImage, binaryImage);

        expect(metrics.accuracy).toBeCloseTo(97.671, 3);
        // NOTE: This PNG is slightly different than the PBM used by other tests
        //console.log(4122975586 / (2112 * 1000000)); // DIBCO Metrics
        //console.log(4122922964 / (2112 * 1000000)); // This algorithm.
        // Possible rounding error due to the weighted matrix?
        expect(metrics.drdm).toBeCloseTo(1.9522, 3); // TODO: Change to 4!
        expect(metrics.fm).toBeCloseTo(93.204, 3);
        expect(metrics.recall).toBeCloseTo(91.3811, 2);
        expect(metrics.precision).toBeCloseTo(95.1025, 2);
        expect(metrics.mcc).toBeCloseTo(0.918, 3);
        expect(metrics.nrm).toBeCloseTo(0.048, 3);
        expect(metrics.psnr).toBeCloseTo(16.329, 3);
    });

    it("Binarization calculatePerformance with pseudo metrics runs successfully", async function() {

        const groundTruthImage = await readImage('../../README/2JohnC1V3-GroundTruth.png');
        const binaryImage = await readImage('../../README/2JohnC1V3-Sauvola.png');

        const pWeightsText = fs.readFileSync(path.resolve(__dirname, '../../../Doxa.Test/Resources/2JohnC1V3-GroundTruth_PWeights.dat'), 'utf8');
        const rWeightsText = fs.readFileSync(path.resolve(__dirname, '../../../Doxa.Test/Resources/2JohnC1V3-GroundTruth_RWeights.dat'), 'utf8');

        const metrics = doxa.calculatePerformance(groundTruthImage, binaryImage, pWeightsText, rWeightsText);

        expect(metrics.pseudoFM).toBeCloseTo(93.393, 2);
        expect(metrics.pseudoRecall).toBeCloseTo(92.7954, 2);
        expect(metrics.pseudoPrecision).toBeCloseTo(93.9983, 2);
    });

    it("Algorithm defaults are applied", async function() {

        const image = await readImage('../../README/2JohnC1V3.png');

        const binImage1 = doxa.toBinary(doxa.binarization.SAUVOLA, image);
        const binImage2 = doxa.toBinary(doxa.binarization.SAUVOLA, image, { window: 75, k: 0.2 });
        const binImage3 = doxa.toBinary(doxa.binarization.SAUVOLA, image, { window: 25, k: 0.12 });

        expect(binImage1.data()).toEqual(binImage2.data());
        expect(binImage2.data()).not.toEqual(binImage3.data());
    });

});
