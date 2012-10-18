toy = require '../../..'

module.exports = class Pong extends toy.Game
  constructor: ->
    super
      name: 'Pong'
      dim: new toy.Vector 800, 600
      bgcolor: new toy.Color()

  update: (dt) ->
    @quit() if @events.quit

    super dt
