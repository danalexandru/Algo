var blessed = require('blessed');

var screen = blessed.screen({
  cursor: {
    artificial: true,
    shape: 'block',
    blink: true,
    color: null // null for default
  }
});

var list = blessed.list({  
  parent: screen,
  width: '50%',
  height: '50%',
  top: 'center',
  left: 'center',
  align: 'center',
  fg: 'blue',
  border: {
    type: 'line'
  },
  selectedBg: 'green',

  // Allow mouse support
  mouse: true,

  // Allow key support (arrow keys + enter)
  keys: true,

  // Use vi built-in keys
  vi: true
});

list.setItems([  
  'one',
  'two',
  'three',
  'four',
  'five',
  'six',
  'seven',
  'eight',
  'nine',
  'ten'
]);

list.prepend(new blessed.Text({  
  left: 2,
  content: ' My list '
}));

//Allow scrolling with the mousewheel (manually).
list.on('wheeldown', function() {
  list.down();
});

list.on('wheelup', function() {
  list.up();
});

// Select the first item.
list.select(0);

// Quit on Escape, q, or Control-C.
screen.key(['escape', 'q', 'C-c'], function(ch, key) {
  return process.exit(0);
});


screen.render();  