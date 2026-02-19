/**
 * Speed Tests for DoxaJs
 *
 * Measures execution time for:
 * - Sauvola binarization
 * - WAN binarization
 * - GlobalThresholding (Otsu) binarization
 * - Full Performance calculation (ClassifiedPerformance + DRDM)
 *
 * Run with: npx jasmine spec/speed.spec.js
 */

const { loadImage, createCanvas } = require('canvas');
const { Doxa } = require('../dist/doxa.js');

// Number of iterations for timing
const WARMUP_ITERATIONS = 3;
const TIMING_ITERATIONS = 10;

let doxa;

/**
 * Read an image file and convert to Doxa.Image
 */
async function readImage(file) {
    const image = await loadImage(file);
    const canvas = createCanvas(image.width, image.height);
    const ctx = canvas.getContext('2d');

    ctx.drawImage(image, 0, 0);

    const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
    return doxa.fromImageData(imageData);
}

/**
 * Measure execution time of a function.
 * If the function returns a Doxa.Image, it will be freed AFTER timing measurement.
 */
function measureTime(func, warmup = WARMUP_ITERATIONS, iterations = TIMING_ITERATIONS) {
    // Warmup runs (free any returned images)
    for (let i = 0; i < warmup; i++) {
        const result = func();
        if (result && typeof result.free === 'function') {
            result.free();
        }
    }

    // Timed runs
    const times = [];
    for (let i = 0; i < iterations; i++) {
        const start = performance.now();
        const result = func();
        const end = performance.now();
        times.push(end - start);

        // Free after timing measurement
        if (result && typeof result.free === 'function') {
            result.free();
        }
    }

    times.sort((a, b) => a - b);

    return {
        min: times[0],
        max: times[times.length - 1],
        avg: times.reduce((a, b) => a + b, 0) / times.length,
        median: times[Math.floor(times.length / 2)]
    };
}

/**
 * Format timing results for display
 */
function formatResults(name, results, width, height) {
    const pixels = width * height;
    const mpixels = pixels / 1_000_000;
    const throughput = mpixels / (results.avg / 1000);

    return `
${name}
  Image size: ${width}x${height} (${mpixels.toFixed(2)} MP)
  Min:    ${results.min.toFixed(3)} ms
  Max:    ${results.max.toFixed(3)} ms
  Avg:    ${results.avg.toFixed(3)} ms
  Median: ${results.median.toFixed(3)} ms
  Throughput: ${throughput.toFixed(2)} MP/s`;
}

describe("Doxa Speed Test Suite", function() {
    let grayscaleImage;
    let groundTruthImage;
    let binaryImage;
    let imageWidth;
    let imageHeight;

    beforeAll(async function() {
        console.log('\n' + '='.repeat(60));
        console.log('DoxaJs Speed Tests');
        console.log('='.repeat(60));
        console.log(`\nWarmup iterations: ${WARMUP_ITERATIONS}`);
        console.log(`Timing iterations: ${TIMING_ITERATIONS}`);

        // Initialize WASM module
        doxa = await Doxa.initialize();

        // Load test images
        console.log('\nLoading test images...');
        grayscaleImage = await readImage('../../README/2JohnC1V3.png');
        binaryImage = await readImage('../../README/2JohnC1V3-Sauvola.png');
        groundTruthImage = await readImage('../../README/2JohnC1V3-GroundTruth.png');

        imageWidth = grayscaleImage.width;
        imageHeight = grayscaleImage.height;

        console.log(`Image: ${imageWidth}x${imageHeight}`);
        console.log('\n' + '-'.repeat(60));
        console.log('BINARIZATION ALGORITHMS');
        console.log('-'.repeat(60));
    });

    afterAll(function() {
        // Clean up WASM memory
        if (grayscaleImage) grayscaleImage.free();
        if (groundTruthImage) groundTruthImage.free();
        if (binaryImage) binaryImage.free();

        console.log('\n' + '='.repeat(60));
        console.log('Speed tests completed');
        console.log('='.repeat(60));
    });

    it("Sauvola binarization performance", function() {
        const params = { window: 75, k: 0.2 };

        const results = measureTime(() => {
            return doxa.toBinary(doxa.binarization.SAUVOLA, grayscaleImage, params);
        });

        console.log(formatResults('Sauvola', results, imageWidth, imageHeight));
        expect(results.avg).toBeGreaterThan(0);
    });

    it("WAN binarization performance", function() {
        const params = { window: 75, k: 0.2 };

        const results = measureTime(() => {
            return doxa.toBinary(doxa.binarization.WAN, grayscaleImage, params);
        });

        console.log(formatResults('WAN', results, imageWidth, imageHeight));
        expect(results.avg).toBeGreaterThan(0);
    });

    it("Otsu (GlobalThresholding) binarization performance", function() {
        const results = measureTime(() => {
            return doxa.toBinary(doxa.binarization.OTSU, grayscaleImage, {});
        });

        console.log(formatResults('Otsu (GlobalThresholding)', results, imageWidth, imageHeight));
        expect(results.avg).toBeGreaterThan(0);
    });

    it("Full Performance (ClassifiedPerformance + DRDM) calculation", function() {
        console.log('\n' + '-'.repeat(60));
        console.log('PERFORMANCE METRICS');
        console.log('-'.repeat(60));

        // Note: The WebAssembly binding calculates ClassifiedPerformance and DRDM together.
        // Use Python binding's calculate_performance_ex for isolated measurements.
        const results = measureTime(() => {
            return doxa.calculatePerformance(groundTruthImage, binaryImage);
        });

        console.log(formatResults('Full Performance (ClassifiedPerformance + DRDM)', results, imageWidth, imageHeight));
        expect(results.avg).toBeGreaterThan(0);
    });
});
