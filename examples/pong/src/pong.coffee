toy = require '../../..'

module.exports = class Pong extends toy.Game
  constructor: ->
    super
      name: 'Pong'
      dim: new toy.Vector 800, 600
      bgcolor: new toy.Color()

  init: (dt) ->
    super dt

    @player = new Paddle
      pos: new toy.Vector(50, (@dim.y / 2) - 50)
    @cpu = new Paddle
      pos: new toy.Vector(@dim.x - 50, (@dim.y / 2) - 50)

    @addEntity 'player', @player
    @addEntity 'cpu', @cpu

    @top = new Wall
      dim: new toy.Vector(@dim.x, 10)
    @bottom = new Wall
      dim: new toy.Vector(@dim.x, 10)
      pos: new toy.Vector(0, @dim.y - 10)

    @addEntity 'top', @top
    @addEntity 'bottom', @bottom


    # toy.sdl.showCursor 0

  update: (dt) ->
    @quit() if @events.quit

    halfy = @player.dim.y / 2

    @player.pos.y = @events.mouse.pos.y - halfy

    @player.collideWalls @top, @bottom
    # @cpu.collideWalls @top, @bottom

    super dt

  render: (dt) ->
    
    super dt


class Paddle extends toy.Dynamic
  constructor: (opts = {}) ->
    super
      pos: opts.pos
      dim: opts.dim ? new toy.Vector 20, 100

  collideWalls: (top, bottom) ->
    bounds = @bounds

  render: (renderer, dt) ->
    rect =
      x: @pos.x
      y: @pos.y
      w: @dim.x
      h: @dim.y
    toy.sdl.renderFillRect renderer, rect

class Wall extends toy.Entity
  render: (renderer, dt) ->
    rect =
      x: @pos.x
      y: @pos.y
      w: @dim.x
      h: @dim.y
    toy.sdl.renderFillRect renderer, rect