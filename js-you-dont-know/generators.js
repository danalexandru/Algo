

//version 1
/*
function makeIterator(array){
    var nextIndex = 0;
    
    return {
       next: function(){
           return nextIndex < array.length ?
               {value: array[nextIndex++], done: false} :
               {done: true};
       }
    }
}

var it = makeIterator(['yo', 'ya']);
console.log(it.next().value); // 'yo'
console.log(it.next().value); // 'ya'
console.log(it.next().done);  // true

*/


//version 2
/*
function* generat() {
	console.log("yo");
	yield;
	console.log("ya");
}

var it = generat();
it.next(); //gigi
it.next(); //becali
*/

//Generator with objects on yield
/*
function* main(){
	yield 1;
	yield 2;
	yield 3;
}

var it = main();

console.dir(it.next()); // { value: 1, done: false }
console.dir(it.next()); // { value: 2, done: false }
console.dir(it.next()); // { value: 3, done: false }

console.dir(it.next()); // { value: undefined, done: true }
*/

//Sum automata

function coroutine(g) {
	var it = g();
	return function(){
		return it.next.apply(it,arguments);
	};
}

var run = coroutine(function*(){
	var x = 1 + (yield);
	var y = 1 + (yield);
	yield (x + y);
});

run();
run(10);
console.log( "Sum is: " + run(30).value);


