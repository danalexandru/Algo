//accomodate for padding
function drawImageProp(canvas, img, x, y, w, h, offsetX, offsetY) {
	if (arguments.length === 2) {
		x = y = 0;
		w = canvas.width;
		h = canvas.height;
	}

	// default offset is center
	offsetX = typeof offsetX === "number" ? offsetX : 0.5;
	offsetY = typeof offsetY === "number" ? offsetY : 0.5;

	// keep bounds [0.0, 1.0]
	if (offsetX < 0) offsetX = 0;
	if (offsetY < 0) offsetY = 0;
	if (offsetX > 1) offsetX = 1;
	if (offsetY > 1) offsetY = 1;

	var iw = img.width,
		ih = img.height,
		r = Math.min(w / iw, h / ih),
		nw = iw * r,   // new prop. width
		nh = ih * r,   // new prop. height
		cx, cy, cw, ch, ar = 1;

	// decide which gap to fill    
	if (nw < w) ar = w / nw;                             
	if (Math.abs(ar - 1) < 1e-14 && nh < h) ar = h / nh;  // updated
	nw *= ar;
	nh *= ar;

	// calc source rectangle
	cw = iw / (nw / w);
	ch = ih / (nh / h);

	cx = (iw - cw) * offsetX;
	cy = (ih - ch) * offsetY;

	// make sure source rectangle is valid
	if (cx < 0) cx = 0;
	if (cy < 0) cy = 0;
	if (cw > iw) cw = iw;
	if (ch > ih) ch = ih;

	// fill image in dest. rectangle
	canvas.getContext("2d").drawImage(img, cx, cy, cw, ch,  x, y, w, h);
}

function setImage(canvas, video){
	// var hRatio = canvas.width  / video.width    ;
	// var vRatio =  canvas.height / video.height  ;
	// var ratio  = Math.min ( hRatio, vRatio );

	// var centerShift_x = ( canvas.width - video.width*ratio ) / 2;
	// var centerShift_y = ( canvas.height - video.height*ratio ) / 2;

	// //canvas.clearRect(0,0,canvas.width, canvas.height);
	// canvas.getContext("2d").drawImage(video, 0,0, video.width, video.height,
	// 	centerShift_x, centerShift_y, video.width*ratio, video.height*ratio);  
	
	
	canvas.height = video.height;
	canvas.width = video.width;
	canvas.getContext("2d").drawImage(video, 0, 0, canvas.width, canvas.height);

	//long format
	// canvas.getContext("2d").drawImage(video, 0, 0, video.width, video.height,
	// 										 0, 0, canvas.width, canvas.height);

	return canvas;
	// canvas.height = video.height;
	// canvas.width = video.width;
	// drawImageProp(canvas, video, 0, 0, canvas.width, canvas.height); //300 or video...

	// video.onload = function() ??
}