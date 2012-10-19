toy = require '../../..'

module.exports = class Pong extends toy.Game
  constructor: ->
    super
      name: 'Pong'
      dim: new toy.Vector 800, 600
      bgcolor: new toy.Color()

  update: (dt) ->
    @quit() if @events.quit

    if @events.keyDown toy.sdl.K_SPACE
      console.log 'space!'

    console.log @events.mouse.pos

    super dt
