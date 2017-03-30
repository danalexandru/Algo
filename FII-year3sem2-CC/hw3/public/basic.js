/*******Setup logic*******/
var container = document.querySelector("#content")
//clientHeight
//offsetHeight
console.log(container.clientHeight);
console.log(container.clientWidth);

while (container.firstChild) {
    container.removeChild(container.firstChild);
}


//var app = new PIXI.Application(800, 600, {backgroundColor : 0x1099bb});
var app = new PIXI.Application(container.clientWidth, container.clientHeight, {backgroundColor : 0x1099bb});

container.appendChild(app.view);
//container.innerHTML = app.view;
var boxWidth = container.clientWidth;
var boxHeight = container.clientHeight;

var moveSize = 10;
var bound = 40;



document.addEventListener('keydown', onKeyDown);


/******Pixi logic******/
// create a new Sprite from an image path
var bunny = PIXI.Sprite.fromImage('assets/bunny.png');

bunnyOriginalScale = [bunny.scale.x, bunny.scale.y];

// Opt-in to interactivity
bunny.interactive = true;

// Shows hand cursor
bunny.buttonMode = true;
bunny.on('pointerdown', onClick);

// center the sprite's anchor point
bunny.anchor.set(0.5);

// move the sprite to the center of the screen
//bunny.x = app.renderer.width / 2;
//bunny.y = app.renderer.height / 2;

bunny.x = Math.floor((Math.random() * (boxWidth - bound)) + bound); // [bound, boxWidth-bound]
bunny.y = Math.floor((Math.random() * (boxHeight - bound)) + bound); // similar

bunny.tint = Math.random() * 0xFFFFFF;

app.stage.addChild(bunny);


console.log('bunny: ');
console.dir(bunny);

// Listen for animate update
app.ticker.add(function(delta) {
    // just for fun, let's rotate mr rabbit a little
    // delta is 1 if running at 100% performance
    // creates frame-independent tranformation
    //bunny.rotation += 0.1 * delta;
});


function onClick () {
	//console.log(bunny.scale.x);
    bunny.scale.x *= 1.25;
    bunny.scale.y *= 1.25;
}

function onKeyDown(key) {
	//console.log(key.keyCode);
	
	//press R to reset scale
	if(key.keyCode == 82){
		bunny.scale.x = bunnyOriginalScale[0];
		bunny.scale.y = bunnyOriginalScale[1];
	}

	// W Key is 87
    // Up arrow is 87
    if (key.keyCode === 87 || key.keyCode === 38) {
        // If the W key or the Up arrow is pressed, move the player up.
        if (bunny.position.y >= 0 + bound) {
            // Don't move up if the player is at the top of the stage
            bunny.position.y -= moveSize;
        }
    }

    // S Key is 83
    // Down arrow is 40
    if (key.keyCode === 83 || key.keyCode === 40) {
        // If the S key or the Down arrow is pressed, move the player down.
        //if (bunny.position.y != renderer.height - boxHeight) {
        if (bunny.position.y <= boxHeight - bound) {
            // Don't move down if the player is at the bottom of the stage
            bunny.position.y += moveSize;
        }
    }

    // A Key is 65
    // Left arrow is 37
    if (key.keyCode === 65 || key.keyCode === 37) {
        // If the A key or the Left arrow is pressed, move the player to the left.
        if (bunny.position.x >= 0 + bound) {
            // Don't move to the left if the player is at the left side of the stage
            bunny.position.x -= moveSize;
        }
    }

    // D Key is 68
    // Right arrow is 39
    if (key.keyCode === 68 || key.keyCode === 39) {
        // If the D key or the Right arrow is pressed, move the player to the right.
        //if (bunny.position.x != renderer.width - boxWidth) {
        //console.log('D pressed, pos:', bunny.position.x);
        if (bunny.position.x <= boxWidth - bound) {
            // Don't move to the right if the player is at the right side of the stage
            bunny.position.x += moveSize;
        }
    }
}



var bunnyID = null;

$.get( '/id', function( data ) {
  console.log('id is');
  console.log(data);
  bunnyID = data;
}).then(function(){
  handleSocket();
});


function handleSocket(){
    var socket = io();
    //socket.emit('new player', JSON.stringify(bunny, null, 2));
    
    var newBunny = {};
    newBunny.x      = bunny.x;
    newBunny.y      = bunny.y;
    newBunny.tint   = bunny.tint;
    newBunny.scale  = {};
    newBunny.scale.x  = bunny.scale._x;
    newBunny.scale.y  = bunny.scale._y;
    newBunny.id       = bunnyID;

    console.log('newBunny');
    console.dir(newBunny);
    socket.emit('new player', JSON.stringify(newBunny, null, 2));

    socket.on('new player', function(otherBunny){
      //app.stage.addChild( JSON.parse(otherBunny) ); //circular reference: e = {}, e.parent = e ...
      
      otherBunny = JSON.parse(otherBunny);
      console.log('otherBunny');
      console.dir(otherBunny);

      if(otherBunny.id != bunnyID){
          var newBunny = PIXI.Sprite.fromImage('assets/bunny.png');
          newBunny.anchor.set(0.5);

          newBunny.x      = otherBunny.x;
          newBunny.y      = otherBunny.y;
          newBunny.tint   = otherBunny.tint;
          newBunny.scale  = otherBunny.scale;

          app.stage.addChild( newBunny );
      }
    });
}

