(function (Doxa, Wasm) {
	Doxa.Algorithm = [
		{ enum: 0, name: 'Otsu', 		params: {},
			date: 1979, title: 'A threshold selection method from gray-level histograms', authors: 'Nobuyuki Otsu'},
		{ enum: 1, name: 'Bernsen', 	params: { window: 75, threshold: 100, 'contrast-limit': 25 },
			date: 1986, title: 'Dynamic thresholding of gray-level images', authors: 'John Bernsen'},
		{ enum: 2, name: 'Niblack', 	params: { window: 223, k: -0.61 },
			date: 1986, title: 'An Introduction to Digital Image Processing', authors: 'Wayne Niblack'},
		{ enum: 3, name: 'Sauvola', 	params: { window: 26, k: 0.10 },
			date: 1999, title: 'Adaptive document image binarization', authors: 'J. Sauvola, M. Pietikäinen'},
		{ enum: 4, name: 'Wolf', 		params: { window: 20, k: 0.18 },
			date: 2003, title: 'Extraction and Recognition of Artificial Text in Multimedia Documents', authors: 'Christian Wolf, Jean-Michel Jolion'},
		{ enum: 5, name: 'N.I.C.K.', 	params: { window: 44, k:-0.10 },
			date: 2009, title: 'Comparison of Niblack inspired Binarization methods for ancient documents', authors: 'Khurram Khurshid, Imran Siddiqi, Claudie Faure, Nicole Vincent'},
		{ enum: 6, name: 'Su', 			params: { window: 26, k: 0.10 },
			date: 2010, title: 'Binarization of Historical Document Images Using the Local Maximum and Minimum', authors: 'Bolan Su, Shijian Lu, and Chew Lim Tan'},
		{ enum: 7, name: 'T.R. Singh', 	params: { window: 75, k: 0.20 },
			date: 2011, title: 'A New local Adaptive Thresholding Technique in Binarization', authors: 'T. Romen Singh, Sudipta Roy, O. Imocha Singh, Tejmani Sinam, Kh. Manglem Singh'},
		{ enum: 8, name: 'ISauvola', 	params: { window: 15, k: 0.01 },
			date: 2016, title: 'ISauvola: Improved Sauvola’s Algorithm for Document Image Binarization', authors: 'Zineb Hadjadj, Abdelkrimo Meziane, Yazid Cherfa, Mohamed Cheriet, Insaf Setitra'},
		{ enum: 9, name: 'Wan', 		params: { window: 75, k: 0.20 },
			date: 2018, title: 'Binarization of Document Image Using Optimum Threshold Modification', authors: 'Wan Azani Mustafa, Mohamed Mydin M. Abdul Kader'},
	];
	
	function to8BitImage(imageBuffer, imageData) {
		const size32 = imageData.width * imageData.height * 4;

		for (var idx = 0; idx < size32; idx += 4) {
			const red = imageData.data[idx];
			const green = imageData.data[idx+1];
			const blue = imageData.data[idx+2];

			//imageBuffer[idx/4] = (red + green + blue) / 3;
			if (red !== blue || red != green) {
				imageBuffer[idx/4] = (red * 11 + green * 16 + blue * 5) / 32;
			}
		}
	}

	function from8BitImage(imageData, imageBuffer) {
		const size32 = imageData.width * imageData.height * 4;
		
		for (var idx = 0; idx < size32; idx += 4) {
			const gsIdx = idx / 4;
			imageData.data[idx] = imageBuffer[gsIdx];
			imageData.data[idx+1] = imageBuffer[gsIdx];
			imageData.data[idx+2] = imageBuffer[gsIdx];
			imageData.data[idx+3] = 255;
		}
	}
	
	Doxa.Image = function(width, height) {
		this.width = width;
		this.height = height;
		this.size = width * height;
		this.heapPtr = Wasm._malloc(this.size);
		this.data = new Uint8ClampedArray(Wasm.HEAPU8.buffer, this.heapPtr, this.size);
		
		// Loads this Image object with an 8bit representation of an ImageData object
		this.load = function(imageData) {
			to8BitImage(this.data, imageData);
			return this;
		};
		// Draws this Image directly to an HTML5 Canvas
		this.draw = function(canvasId) {
			var canvas = document.getElementById(canvasId);
			canvas.width = this.width;
			canvas.height = this.height;
			
            var ctx = canvas.getContext('2d');
			var imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
						
			from8BitImage(imageData, this.data);
			
			ctx.putImageData(imageData, 0, 0);
		};
		// Frees the memory allocated by this object.
		this.free = function() {
			if (this.heapPtr != null) Wasm._free(this.heapPtr); 
		};
	};

	Doxa.initialize = function(algorithm, image) {			
		Wasm._Initialize(algorithm, image.data.byteOffset, image.width, image.height);
	};
	
	Doxa.toBinary = function(image, parameters) {
		// Convert JSON object into a WASM string pointer
		var paramString = JSON.stringify(parameters);
		var paramPtr = Wasm._malloc(paramString.length);
		Wasm.writeAsciiToMemory(paramString, paramPtr);
		
		// Convert to binary
		Wasm._ToBinary(image.data.byteOffset, paramPtr);
		
		// Free param memory
		Module._free(paramPtr);
	};
}(window.Doxa = window.Doxa || {}, Module));