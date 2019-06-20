function initComparisons() {
  var y, x, i;
  /*find all elements with an "overlay" class:*/
  x = document.getElementsByClassName("img-comp-overlay");
  /*set width and height of our container correctly*/
  y = document.getElementsByClassName('img-comp-container')[0];
  y.style.height = x[0].children[0].height + "px";
  y.style.width = x[0].children[0].width + "px";
  compareImages(x[0]);

  function compareImages(img) {
	var slider, img, w, h;
	/*get the width and height of the img element*/
	w = img.offsetWidth;
	h = img.offsetHeight;
	/*set the width of the img element to 50%:*/
	img.style.width = (w / 2) + "px";
	/*create slider:*/
	slider = document.createElement("DIV");
	slider.setAttribute("class", "img-comp-slider");
	/*insert slider*/
	img.parentElement.insertBefore(slider, img);
	/*position the slider in the middle:*/
	slider.style.top = (h / 2) - (slider.offsetHeight / 2) + "px";
	slider.style.left = (w / 2) - (slider.offsetWidth / 2) + "px";
	/*execute a function when the mouse button is pressed:*/
	slider.addEventListener("mousedown", slideReady);
	/*and another function when the mouse button is released:*/
	window.addEventListener("mouseup", slideFinish);
	/*or touched (for touch screens:*/
	slider.addEventListener("touchstart", slideReady);
	/*and released (for touch screens:*/
	window.addEventListener("touchend", slideFinish);
	function slideReady(e) {
	  /*prevent any other actions that may occur when moving over the image:*/
	  e.preventDefault();

	  /*execute a function when the slider is moved:*/
	  window.addEventListener("mousemove", slideMove);
	  window.addEventListener("touchmove", slideMove);
	}
	function slideFinish() {
	  /*the slider is no longer clicked:*/
	  window.removeEventListener("mousemove", slideMove);
	  window.removeEventListener("touchmove", slideMove);
	}
	function slideMove(e) {
	  /*get the cursor's x position:*/
	  var pos = getCursorPos(e)
	  /*prevent the slider from being positioned outside the image:*/
	  if (pos < 0) pos = 0;
	  if (pos > w) pos = w;
	  /*execute a function that will resize the overlay image according to the cursor:*/
	  slide(pos);
	}
	function getCursorPos(e) {
	  var a, x = 0;
	  e = e || window.event;
	  /*get the x positions of the image:*/
	  a = img.getBoundingClientRect();
	  /*calculate the cursor's x coordinate, relative to the image:*/
	  x = pointerEventToXY(e).x - a.left;
	  /*consider any page scrolling:*/
	  x = x - window.pageXOffset;
	  return x;
	}
	function pointerEventToXY(e) {
      /*fix touch eventing in original code*/
      var out = {x:0, y:0};
      if(e.type == 'touchstart' || e.type == 'touchmove' || e.type == 'touchend' || e.type == 'touchcancel'){
        var touch = e.touches[0] || e.changedTouches[0];
        out.x = touch.pageX;
        out.y = touch.pageY;
      } else if (e.type == 'mousedown' || e.type == 'mouseup' || e.type == 'mousemove' || e.type == 'mouseover'|| e.type=='mouseout' || e.type=='mouseenter' || e.type=='mouseleave') {
        out.x = e.pageX;
        out.y = e.pageY;
      }
      return out;
    }
	function slide(x) {
	  /*resize the image:*/
	  img.style.width = x + "px";
	  /*position the slider:*/
	  slider.style.left = img.offsetWidth - (slider.offsetWidth / 2) + "px";
	}
  }
}