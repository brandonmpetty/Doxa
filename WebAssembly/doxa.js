(function (Doxa, Wasm) {
	
	var binarization;
	
	Doxa.getAlgorithms = function() {
		let algorithms = new Array(10);
		algorithms[Wasm.Binarization.Algorithms.OTSU.value] = { 
			name: 'Otsu', 		params: {}, enum: Wasm.Binarization.Algorithms.OTSU,
			date: 1979, title: 'A threshold selection method from gray-level histograms', authors: 'Nobuyuki Otsu'};
		algorithms[Wasm.Binarization.Algorithms.BERNSEN.value] = { 
			name: 'Bernsen', 	params: { window: 75, threshold: 100, 'contrast-limit': 25 }, enum: Wasm.Binarization.Algorithms.BERNSEN,
			date: 1986, title: 'Dynamic thresholding of gray-level images', authors: 'John Bernsen'};
		algorithms[Wasm.Binarization.Algorithms.NIBLACK.value] =	{
			name: 'Niblack', 	params: { window: 223, k: -0.61 }, enum: Wasm.Binarization.Algorithms.NIBLACK,
			date: 1986, title: 'An Introduction to Digital Image Processing', authors: 'Wayne Niblack'};
		algorithms[Wasm.Binarization.Algorithms.SAUVOLA.value] =	{
			name: 'Sauvola', 	params: { window: 26, k: 0.10 }, enum: Wasm.Binarization.Algorithms.SAUVOLA,
			date: 1999, title: 'Adaptive document image binarization', authors: 'J. Sauvola, M. Pietikäinen'};
		algorithms[Wasm.Binarization.Algorithms.WOLF.value] =	{
			name: 'Wolf', 		params: { window: 20, k: 0.18 }, enum: Wasm.Binarization.Algorithms.WOLF,
			date: 2003, title: 'Extraction and Recognition of Artificial Text in Multimedia Documents', authors: 'Christian Wolf, Jean-Michel Jolion'};
		algorithms[Wasm.Binarization.Algorithms.NICK.value] =	{
			name: 'N.I.C.K.', 	params: { window: 44, k:-0.10 }, enum: Wasm.Binarization.Algorithms.NICK,
			date: 2009, title: 'Comparison of Niblack inspired Binarization methods for ancient documents', authors: 'Khurram Khurshid, Imran Siddiqi, Claudie Faure, Nicole Vincent'};
		algorithms[Wasm.Binarization.Algorithms.SU.value] =	{
			name: 'Su', 		params: { window: 26, k: 0.10 }, enum: Wasm.Binarization.Algorithms.SU,
			date: 2010, title: 'Binarization of Historical Document Images Using the Local Maximum and Minimum', authors: 'Bolan Su, Shijian Lu, and Chew Lim Tan'};
		algorithms[Wasm.Binarization.Algorithms.TRSINGH.value] =	{
			name: 'T.R. Singh', params: { window: 75, k: 0.20 }, enum: Wasm.Binarization.Algorithms.TRSINGH,
			date: 2011, title: 'A New local Adaptive Thresholding Technique in Binarization', authors: 'T. Romen Singh, Sudipta Roy, O. Imocha Singh, Tejmani Sinam, Kh. Manglem Singh'};
		algorithms[Wasm.Binarization.Algorithms.BATAINEH.value] =	{
			name: 'Bataineh', params: { }, enum: Wasm.Binarization.Algorithms.BATAINEH,
			date: 2011, title: 'An adaptive local binarization method for document images based on a novel thresholding method and dynamic windows', authors: 'Bilal Bataineh, Siti Norul Huda Sheikh Abdullah, Khairuddin Omar'};
		algorithms[Wasm.Binarization.Algorithms.ISAUVOLA.value] =	{
			name: 'ISauvola', 	params: { window: 15, k: 0.01 }, enum: Wasm.Binarization.Algorithms.ISAUVOLA,
			date: 2016, title: 'ISauvola: Improved Sauvola’s Algorithm for Document Image Binarization', authors: 'Zineb Hadjadj, Abdelkrimo Meziane, Yazid Cherfa, Mohamed Cheriet, Insaf Setitra'};
		algorithms[Wasm.Binarization.Algorithms.WAN.value] =	{
			name: 'Wan', 		params: { window: 75, k: 0.20 }, enum: Wasm.Binarization.Algorithms.WAN,
			date: 2018, title: 'Binarization of Document Image Using Optimum Threshold Modification', authors: 'Wan Azani Mustafa, Mohamed Mydin M. Abdul Kader'};
		
		return algorithms;
	}
	
	Doxa.Image = function(width, height) {
		"use strict";
		let that = this;
		this.width = 0;
		this.height = 0;
		this.size = 0;
		
		// Loads this Image object with an 8bit representation of an ImageData object
		this.loadFromCanvas = function(imageData) {
			initialize(imageData.width, imageData.height);
			
			var data = new Uint8ClampedArray(Wasm.HEAPU8.buffer, this.heapPtr, this.size);
			to8BitImage(data, imageData);
			
			return this;
		};
		
		// Draws this Image directly to an HTML5 Canvas
		this.draw = function(canvasId) {
			var canvas = document.getElementById(canvasId);
			canvas.width = this.width;
			canvas.height = this.height;
			
            var ctx = canvas.getContext('2d');
			var imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
						
			var data = new Uint8ClampedArray(Wasm.HEAPU8.buffer, this.heapPtr, this.size);
			from8BitImage(imageData, data);
			
			ctx.putImageData(imageData, 0, 0);
		};
		
		// Frees the memory allocated by this object.
		this.free = function() {
			if (this.heapPtr != null) Wasm._free(this.heapPtr); 
		};
		
		// (re-)allocate memory for our image
		function initialize(width, height) {
			that.width = width;
			that.height = height;
			
			if (width * height > that.size) {
				that.free();
				that.size = width * height;
				that.heapPtr = Wasm._malloc(that.size);
			}
		}
		
		function to8BitImage(imageBuffer, imageData) {
			const size32 = imageData.width * imageData.height * 4;

			for (var idx = 0; idx < size32; idx += 4) {
				const red = imageData.data[idx];
				const green = imageData.data[idx+1];
				const blue = imageData.data[idx+2];

				// TODO: Offer more grayscale options
				imageBuffer[idx/4] = (red + green + blue) / 3;
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
		
		initialize(width, height);
	};

	Doxa.initialize = function(algorithm, image) {
		if (binarization) binarization.delete();
		
		binarization = new Wasm.Binarization(algorithm);
		binarization.initialize(image.heapPtr, image.width, image.height);
	};
	
	Doxa.toBinary = function(image, parameters) {
		let paramString = JSON.stringify(parameters);

		binarization.toBinary(image.heapPtr, paramString);
	};
	
	Doxa.calculatePerformance = function(groundTruth, image) {
		return Wasm.calculatePerformance(groundTruth.heapPtr, image.heapPtr, image.width, image.height);
	};
}(window.Doxa = window.Doxa || {}, Module));