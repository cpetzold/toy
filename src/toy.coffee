sdl = require 'sdl2'

Function::property = (prop, desc) ->
  Object.defineProperty @prototype, prop, desc

module.exports =
  sdl: sdl

  draw: require './draw'
  utils: require './utils'
  
  Game: require './game'
  Entity: require './entity'
  Dynamic: require './dynamic'
  Vector: require './vector'
  Color: require './color'

  extends: (child, parent) ->
    for key in parent
      child[key] = parent[key] if parent.hasOwnProperty key
    ctor = -> @constructor = child; @
    ctor.prototype = parent.prototype
    child.prototype = new ctor
    child.super = parent.prototype
    child