var i = 0;

function timedCount() {
	i = i + 1;
	postMessage(i);

	//a worker runs in different context, so you can't access the DOM
	//document.getElementById("status").innerHTML = 'smth';
	setTimeout("timedCount()",500);
}

timedCount();