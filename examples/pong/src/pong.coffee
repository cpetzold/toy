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

  render: (dt) ->
    rect =
      x: 50
      y: @events.mouse.pos.y - 50
      w: 20
      h: 100
    toy.sdl.renderFillRect @renderer, rect

    super dt