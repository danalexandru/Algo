//Let scoping
var content = 'sth'
for(var i = 1; i<4; i++)
  console.log(i)

console.log(content)
console.log('outside:', i) //change var to let, and this won't work (also, it will block further execution)


//Constants
const PI = Math.PI  //usecase: loading libraries with require() into const
console.log(PI)

// PI = PI * 2 // this won't work


//Multiline variable assignation
let numbers = `
25
20
`
console.log(numbers)


//Variable interpolation
let welcome = 'hello to you, '
let name = 'Dan'
console.log('And ${welcome} ${Dan}') //interpolation ?


//Changing variable namespace (?)

let coffee = { type: 'cappuccino', count: 2}
console.log(coffee)
let { type, count } = coffee
console.log(type, count)


//Function parameters
function pourCoffee (type='expresso'){ //Default argument
  console.log('Servs you ' + type)
}
pourCoffee()
pourCoffee('latte')

function getCookies (...types){ //Multiple arguments
  if(types.length > 0){
    console.log('I got some cookies for you, look: ' + types)
  }
}
getCookies('raspberry', 'chocolate')
getCookies()
