// require('./lib');

var toy = require('../..')
  , util = require('util');

var Pong = function(name, w, h) {
  console.log('in Pong constructor');
  toy.Game.call(this);
};

util.inherits(Pong, toy.Game);

console.log(Pong.super_, toy.Game);

var test = new Pong('Pong', 800, 600);

test.run();