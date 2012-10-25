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
      pos: new toy.Vector(0, (@dim.y / 2) - 50)
    @cpu = new Paddle
      pos: new toy.Vector(@dim.x - 20, (@dim.y / 2) - 50)

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
      pos: @bounds.center.copy()

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

    fps = Math.round(1 / dt)
    toy.sdl.setWindowTitle @window, "Score: FPS: #{fps}"

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
    toy.draw.rect renderer, @bounds

class Ball extends toy.Dynamic
  constructor: (opts = {}) ->
    super
      pos: opts.pos
      dim: opts.dim ? new toy.Vector 8, 8
      vel: opts.vel ? new toy.Vector 200, 200

    @mid = opts.pos

  reset: ->
    @pos = @mid.copy()
    range = new toy.Vector -200, 200
    vel = toy.Vector.randRange range
    while Math.abs(vel.x) < 50 or Math.abs(vel.y) < 50
      vel = toy.Vector.randRange range
    @vel = vel.copy()


  update: (dt, events) ->

    if events.keyPressed toy.sdl.K_r
      @reset()

    super dt


  handleCollision: (entity, intersection) ->
    if entity.constructor.name is 'Wall'
      @vel.multiply 1.01
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
    toy.draw.rect renderer, @bounds

class Wall extends toy.Entity
  render: (renderer, dt) ->
    toy.draw.rect renderer, @bounds

