/**
 * Doxa NodeJS Demo
 * This demo uses the WASM bindings and helper classes to seemlessly call into Doxa's binarization routines.
 * The code below gives an example of how to read an image, convert it to binary, and get performance stats.
 * We are using the image processing library Sharp to show how to read and write images in NodeJS.
 */
const { Image, Doxa } = require('./doxaNode.js');
const sharp = require('sharp');

/**
 * An example image reader wrapper around Sharp.
 * @param {*} file Input file location.  Should be 32b RGBA.
 */
async function ReadImage(file) {
	return sharp(file)
		.raw()
		.toBuffer({ resolveWithObject: true })
		.then(content => {
			return new Image(content.info.width, content.info.height, content.data);
		});
}

/**
 * An example image writer wrapper around Sharp.
 * @param {*} image A binary Doxa Image object
 * @param {*} file Output file location.  This can be any supported format.
 */
async function WriteImage(image, file) {
	return sharp(Buffer.from(image.data()), { 
		raw: { 
			width: image.width, 
			height: image.height, 
			channels: 1 // b&w
		}
	}).toFile(file);
}

async function Demo() {

	// Initialize the Doxa framework
	const Algorithms = await Doxa.initialize();

	// Read local image files to process
	const gtImage = await ReadImage('../../README/2JohnC1V3-GroundTruth.png');
	const image = await ReadImage('../../README/2JohnC1V3.png');

	// Generate a binary image
	const binImage = Doxa.toBinary(Algorithms.SAUVOLA, image, { window: 26, k: 0.10 });

	// Get performance information
	const perf = Doxa.calculatePerformance(gtImage, binImage);
	console.dir(perf);

	// Write file
	await WriteImage(binImage, './binary.png');

	// Remember to free the memory of your WASM based images
	gtImage.free();
	image.free();
	binImage.free();
}

// Run our demo
Demo();