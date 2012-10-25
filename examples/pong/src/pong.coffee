toy = require '../../..'

module.exports = class Pong extends toy.Game
  constructor: ->
    super
      name: 'Pong'
      dim: new toy.Vector 800, 600
      bgcolor: new toy.Color()

  init: (dt) ->
    super dt

    # toy.sdl.showCursor 0

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

    @ball = new Ball

    @addEntity 'ball', @ball

    @reset()

  reset: ->
    @ball.pos = @bounds.center.copy()

  update: (dt) ->
    @quit() if @events.quit

    halfy = @player.dim.y / 2

    # @player.pos.y = @events.mouse.pos.y - halfy
    if @events.keyDown toy.sdl.K_UP
      @player.acc.y = -@player.speed
    if @events.keyDown toy.sdl.K_DOWN
      @player.acc.y = @player.speed

    @cpu.vel.y = @ball.vel.y

    super dt

  render: (dt) ->
    
    super dt


class Paddle extends toy.Dynamic
  constructor: (opts = {}) ->
    super
      pos: opts.pos
      dim: opts.dim ? new toy.Vector 20, 100
      damp: opts.damp ? new toy.Vector 1, 0.95

    @speed = 2000

  handleCollision: (entity, intersection) ->
    if entity.constructor.name is 'Wall'
      if @vel.y > 0
        @pos.y -= intersection.dim.y
      else
        @pos.y += intersection.dim.y
      @vel.y = 0

  render: (renderer, dt) ->
    rect =
      x: Math.round @pos.x
      y: Math.round @pos.y
      w: Math.round @dim.x
      h: Math.round @dim.y
    toy.sdl.renderFillRect renderer, rect

class Ball extends toy.Dynamic
  constructor: (opts = {}) ->
    super
      pos: opts.pos
      dim: opts.dim ? new toy.Vector 8, 8
      vel: opts.vel ? new toy.Vector 200, 200

  handleCollision: (entity, intersection) ->
    if entity.constructor.name is 'Wall'
      @vel.multiply 1.2
      if @vel.y > 0
        @pos.y -= intersection.dim.y
      else if @vel.y < 0
        @pos.y += intersection.dim.y
      @vel.y *= -1
    else
      if @vel.x > 0
        @pos.x -= intersection.dim.x
      else if @vel.x < 0
        @pos.x += intersection.dim.x
      @vel.x *= -1

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