/**
 * Doxa NodeJS Demo
 * This demo uses the WASM bindings and helper classes to seemlessly call into Doxa's binarization routines.
 * The code below gives an example of how to read an image, convert it to binary, and get performance stats.
 * We are using the image processing library Sharp to show how to read and write images in NodeJS.
 */
const { Doxa } = require('../../Bindings/WebAssembly/dist/doxa.js');
const sharp = require('sharp');

/**
 * An example image reader wrapper around Sharp.
 * @param {object} doxa Initialized Doxa instance
 * @param {*} file Input file location.  Should be 8b grayscale, 24b RGB, or 32b RGBA.
 * @param {number} algorithm Grayscale algorithm enum value (e.g. doxa.grayscale.MEAN). Defaults to MEAN.
 */
async function readImage(doxa, file, algorithm) {
	return sharp(file)
		.raw()
		.toBuffer({ resolveWithObject: true })
		.then(content => {
			return doxa.toGrayscale(
				content.data, content.info.width, content.info.height, content.info.channels, algorithm);
		});
}

/**
 * An example image writer wrapper around Sharp.
 * @param {*} image A binary Doxa Image object
 * @param {*} file Output file location.  This can be any supported format.
 */
async function writeImage(image, file) {
	return sharp(Buffer.from(image.data()), {
		raw: {
			width: image.width,
			height: image.height,
			channels: 1 // b&w
		}
	}).toFile(file);
}

async function demo() {

	// Initialize the Doxa framework
	const doxa = await Doxa.initialize();

	// Read in the Ground Truth - 8bit
	const gtImage = await readImage(doxa, '../../README/2JohnC1V3-GroundTruth.png');

	// Read in the target image - 8b, 24b, 32b.  If color, convert to grayscale.
	const image = await readImage(doxa, '../../README/2JohnC1V3.png', doxa.grayscale.MEAN);

	// Generate a binary image
	const binImage = doxa.toBinary(doxa.binarization.SAUVOLA, image, { window: 27, k: 0.10 });

	// Get performance information
	const perf = doxa.calculatePerformance(gtImage, binImage);
	console.dir(perf);

	// Write file
	await writeImage(binImage, 'binary.png');

	// Remember to free the memory of your WASM based images
	gtImage.free();
	image.free();
	binImage.free();
}

// Run our demo
demo();
