/**
 * Doxa WASM
 * A set of classes that further simplify the Doxa WASM interface.
 * This same wrapper can be ran in NodeJS or directly in the web.
 * See Demo/WebJs and Demo/NodeJS for an example of how to use it.
 */

const Doxa = {

	Wasm: (typeof Module !== 'undefined') ? Module : require('./doxaWasm.js'),

	initialize: async function() {
		if (!Doxa.Wasm) throw new Error('Missing: Doxa WASM Module');

		// Return the list of algorithms compiled into the WASM
		const getAlgorithms = function() {
			const algorithms = {}
			for (const key in Doxa.Wasm.Binarization.Algorithms) {
				const alg = Doxa.Wasm.Binarization.Algorithms[key];
				if (alg.value === undefined) continue;

				algorithms[key] = alg.value;
			}
			return algorithms;
		}

		return new Promise((resolve) => {
			// Ensure the library has not already been initialized
			if (typeof Doxa.Wasm.Binarization !== 'undefined') {
				return resolve(getAlgorithms());
			}

			Doxa.Wasm.onRuntimeInitialized = async _ => {
				resolve(getAlgorithms());
			};
		});
	},

	Image: class {
		
		size = 0;

		/**
		 * Initialize an Image object.  All Image objects allocate WASM memory.
		 * That memory should be freed, explicitly.  If you pass in a raw data array,
		 * it will be converted to 8bit grayscale automatically.
		 * @param {*} width Image Width
		 * @param {*} height Image Height
		 * @param {*} data Raw 32bit RGBA.  Optional.
		 */
		constructor (width, height, data) {
			this.initialize(width, height);
			
			if (data) {
				this.to8BitImage(this.data(), { width, height, data } );	
			}
		}
			
		/**
		 * Draws the Image directly to an HTML5 Canvas.
		 * The Canvas should accept 32bit data, which is standard.
		 * @param {*} canvas HTML5 Canvas, or a node-canvas
		 */
		draw = function(canvas) {
			canvas.width = this.width;
			canvas.height = this.height;
			
			const ctx = canvas.getContext('2d');
			const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
						
			this.from8BitImage(imageData, this.data());
			
			ctx.putImageData(imageData, 0, 0);
		};
		
		data = function() {
			return new Uint8ClampedArray(Doxa.Wasm.HEAPU8.buffer, this.heapPtr, this.size);
		};
			
		/**
		 * Frees the memory allocated by this object.
		 */
		free = function() {
			if (this.heapPtr != null) Doxa.Wasm._free(this.heapPtr); 
		};
			
		initialize(width, height) {
			this.width = width;
			this.height = height;
			
			if (width * height > this.size) {
				this.free();
				this.size = width * height;
				this.heapPtr = Doxa.Wasm._malloc(this.size);
			}
		}
			
		to8BitImage(imageBuffer, imageData) {
			const size32 = imageData.width * imageData.height * 4;

			for (var idx = 0; idx < size32; idx += 4) {
				const red = imageData.data[idx];
				const green = imageData.data[idx+1];
				const blue = imageData.data[idx+2];

				imageBuffer[idx/4] = (red + green + blue) / 3;
			}
		}

		from8BitImage(imageData, imageBuffer) {
			const size32 = imageData.width * imageData.height * 4;
			
			for (var idx = 0; idx < size32; idx += 4) {
				const gsIdx = idx / 4;
				imageData.data[idx] = imageBuffer[gsIdx];
				imageData.data[idx+1] = imageBuffer[gsIdx];
				imageData.data[idx+2] = imageBuffer[gsIdx];
				imageData.data[idx+3] = 255;
			}
		}
	},


	Binarization: class {

		static toBinary = function(algorithm, imageIn, parameters, imageOut /* optional */) {
			
			// If no parameter is supplied, create an image object to return
			if (!imageOut) {
				imageOut = new Doxa.Image(imageIn.width, imageIn.height);
			}
			
			const algEnum = Doxa.Wasm.Binarization.Algorithms.values[algorithm];
			const paramString = JSON.stringify(parameters);
			const binarization = new Doxa.Wasm.Binarization(algEnum);
			
			binarization.initialize(imageIn.heapPtr, imageIn.width, imageIn.height);
			binarization.toBinary(imageOut.heapPtr, paramString);
			
			return imageOut;
		};
		
		static calculatePerformance = function(groundTruth, image) {
			return Doxa.Wasm.calculatePerformance(groundTruth.heapPtr, image.heapPtr, image.width, image.height);
		};
	}
}

// Only export if running in NodeJS
if (typeof module !== 'undefined') {
	module.exports = { Doxa };
}
