/**
 * Doxa WASM
 * A set of classes that further simplify the Doxa WASM interface.
 * This same wrapper can be run in NodeJS or directly in the web.
 * See Demo/WebJs and Demo/NodeJS for an example of how to use it.
 */

const Doxa = {

	Wasm: (typeof Module !== 'undefined') ? Module : require('./doxaWasm.js'),

	initialize: async function() {
		if (!Doxa.Wasm) throw new Error('Missing: Doxa WASM Module');

		// Extract enum values from an Emscripten enum object
		const extractEnums = function(enumObj) {
			const enums = {};
			for (const key in enumObj) {
				const entry = enumObj[key];
				if (entry?.value === undefined) continue;
				enums[key] = entry.value;
			}
			return enums;
		}

		const buildInstance = function() {
			const instance = {
				binarization: extractEnums(Doxa.Wasm.Binarization.Algorithms),
				grayscale: extractEnums(Doxa.Wasm.Grayscale.Algorithms),

				/**
				 * Convert raw pixel data to an 8-bit grayscale Doxa.Image.
				 * If the data is already single-channel, it is copied directly.
				 * @param {Uint8Array|Uint8ClampedArray} data - Raw pixel data (1, 3, or 4 channels)
				 * @param {number} width - Image width
				 * @param {number} height - Image height
				 * @param {number} channels - 1 for grayscale, 3 for RGB, 4 for RGBA
				 * @param {number} algorithm - Grayscale algorithm enum value (e.g. doxa.grayscale.MEAN). Defaults to MEAN.
				 * @returns {Doxa.Image} 8-bit grayscale image (caller must free)
				 */
				toGrayscale: function(data, width, height, channels, algorithm) {
					// Already grayscale — just copy directly
					if (channels === 1) {
						return new Doxa.Image(width, height, data);
					}

					// Allocate WASM heap for input
					const inputSize = width * height * channels;
					const inputPtr = Doxa.Wasm._malloc(inputSize);
					Doxa.Wasm.HEAPU8.set(data.subarray(0, inputSize), inputPtr);

					// Allocate output image
					const outputImage = new Doxa.Image(width, height);

					const algEnum = Doxa.Wasm.Grayscale.Algorithms.values[
						algorithm ?? instance.grayscale.MEAN
					];
					Doxa.Wasm.toGrayscale(outputImage.heapPtr, inputPtr, width, height, channels, algEnum);

					// Free input buffer
					Doxa.Wasm._free(inputPtr);

					return outputImage;
				},

				/**
				 * Convert an HTML5 Canvas ImageData to an 8-bit grayscale Doxa.Image.
				 * Convenience wrapper for browser usage.
				 * @param {ImageData} imageData - Canvas ImageData (32-bit RGBA)
				 * @param {number} algorithm - Grayscale algorithm enum value (e.g. doxa.grayscale.MEAN). Defaults to MEAN.
				 * @returns {Doxa.Image} 8-bit grayscale image (caller must free)
				 */
				fromImageData: function(imageData, algorithm) {
					return instance.toGrayscale(
						imageData.data, imageData.width, imageData.height, 4, algorithm
					);
				},

				/**
				 * Binarize a grayscale image using the specified algorithm.
				 * @param {number} algorithm - Binarization algorithm enum value (e.g. doxa.binarization.SAUVOLA)
				 * @param {Doxa.Image} imageIn - Input grayscale image
				 * @param {object} parameters - Algorithm parameters (e.g. { window: 75, k: 0.2 })
				 * @param {Doxa.Image} imageOut - Optional output image (allocated if not provided)
				 * @returns {Doxa.Image} Binary image (caller must free if newly allocated)
				 */
				toBinary: function(algorithm, imageIn, parameters, imageOut) {
					if (!imageOut) {
						imageOut = new Doxa.Image(imageIn.width, imageIn.height);
					}

					const algEnum = Doxa.Wasm.Binarization.Algorithms.values[algorithm];
					const paramString = JSON.stringify(parameters || {});
					const binarization = new Doxa.Wasm.Binarization(algEnum);

					binarization.initialize(imageIn.heapPtr, imageIn.width, imageIn.height);
					binarization.toBinary(imageOut.heapPtr, paramString);

					return imageOut;
				},

				/**
				 * Calculate performance metrics comparing a binary image against ground truth.
				 * If precision/recall weight texts are provided, pseudo metrics are included.
				 * @param {Doxa.Image} groundTruth - Ground truth binary image
				 * @param {Doxa.Image} binary - Binary image to evaluate
				 * @param {string} precisionWeightsText - Optional precision weights (enables pseudo metrics)
				 * @param {string} recallWeightsText - Optional recall weights (enables pseudo metrics)
				 * @returns {object} Performance metrics (accuracy, fm, precision, recall, mcc, psnr, nrm, drdm, and optionally pseudoFM, pseudoPrecision, pseudoRecall)
				 */
				calculatePerformance: function(groundTruth, binary, precisionWeightsText, recallWeightsText) {
					if (precisionWeightsText && recallWeightsText) {
						return Doxa.Wasm.calculatePseudoPerformance(
							groundTruth.heapPtr, binary.heapPtr,
							binary.width, binary.height,
							precisionWeightsText, recallWeightsText
						);
					}

					return Doxa.Wasm.calculatePerformance(
						groundTruth.heapPtr, binary.heapPtr,
						binary.width, binary.height
					);
				}
			};

			return instance;
		}

		return new Promise((resolve) => {
			// Ensure the library has not already been initialized
			if (typeof Doxa.Wasm.Binarization !== 'undefined') {
				return resolve(buildInstance());
			}

			Doxa.Wasm.onRuntimeInitialized = async _ => {
				resolve(buildInstance());
			};
		});
	},

	Image: class {

		bufferSize = 0;

		/**
		 * Initialize an Image object.  All Image objects allocate WASM memory.
		 * That memory should be freed, explicitly.  If 8-bit data is passed,
		 * it will be copied directly into WASM memory.
		 * Use doxa.fromImageData to convert from RGBA to grayscale.
		 * @param {number} width Image Width
		 * @param {number} height Image Height
		 * @param {Uint8Array} data 8-bit grayscale data.  Optional.
		 */
		constructor (width, height, data) {
			this.initialize(width || 0, height || 0);

			if (data) {
				Doxa.Wasm.HEAPU8.set(data.subarray(0, this.size), this.heapPtr);
			}
		}

		/**
		 * The number of pixels in the image.
		 */
		get size() {
			return this.width * this.height;
		}

		/**
		 * Draws the Image directly to an HTML5 Canvas.
		 * The Canvas should accept 32bit data, which is standard.
		 * @param {*} canvas HTML5 Canvas, or a node-canvas
		 */
		draw(canvas) {
			canvas.width = this.width;
			canvas.height = this.height;

			const ctx = canvas.getContext('2d');
			const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);

			this.toImageData(imageData);

			ctx.putImageData(imageData, 0, 0);
		}

		data() {
			return new Uint8ClampedArray(Doxa.Wasm.HEAPU8.buffer, this.heapPtr, this.size);
		}

		/**
		 * Frees the memory allocated by this object.
		 */
		free() {
			if (this.heapPtr != null) Doxa.Wasm._free(this.heapPtr);
		}

		initialize(width, height) {
			this.width = width;
			this.height = height;

			if (this.size > this.bufferSize) {
				this.free();
				this.bufferSize = this.size;
				this.heapPtr = Doxa.Wasm._malloc(this.bufferSize);
			}
		}

		/**
		 * Writes the 8-bit grayscale image data into a 32-bit RGBA ImageData object.
		 * @param {ImageData} imageData - Target ImageData to populate
		 */
		toImageData(imageData) {
			const buffer = this.data();
			const size32 = imageData.width * imageData.height * 4;

			for (var idx = 0; idx < size32; idx += 4) {
				const gsIdx = idx / 4;
				imageData.data[idx] = buffer[gsIdx];
				imageData.data[idx+1] = buffer[gsIdx];
				imageData.data[idx+2] = buffer[gsIdx];
				imageData.data[idx+3] = 255;
			}
		}
	}
}

// Only export if running in NodeJS
if (typeof module !== 'undefined') {
	module.exports = { Doxa };
}
