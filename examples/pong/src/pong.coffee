toy = require '../../..'

module.exports = class Pong extends toy.Game
  constructor: (name, w, h) ->
    super name, w, h

  init: ->
    console.log 'init'
    super()

  run: ->
    console.log 'run'
    super()