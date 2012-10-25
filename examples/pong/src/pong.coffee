toy = require '../../..'

module.exports = class Pong extends toy.Game
  constructor: ->
    super
      name: 'Pong'
      dim: new toy.Vector 800, 600
      bgcolor: new toy.Color()

    @winScore = 5
    @debug = false

  init: (dt) ->
    super dt

    # toy.sdl.showCursor 0

    @player = new Paddle
      pos: new toy.Vector(0, (@dim.y / 2) - 50)
    @cpu = new Paddle
      pos: new toy.Vector(@dim.x - 20, (@dim.y / 2) - 50)
      speed: 1500

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
    @ball.move 1000

    @addEntity 'ball', @ball

  update: (dt) ->
    @showTitle dt

    halfy = @player.dim.y / 2

    # @player.pos.y = @events.mouse.pos.y - halfy
    if @events.keyDown toy.sdl.K_UP
      @player.acc.y = -@player.speed
    if @events.keyDown toy.sdl.K_DOWN
      @player.acc.y = @player.speed

    bb = @ball.bounds
    cb = @cpu.bounds
    wb = @bounds

    # CPU ai
    # if bb.center.x > wb.center.x
    if bb.center.y < cb.center.y
      @cpu.acc.y = -@cpu.speed
    else
      @cpu.acc.y = @cpu.speed

    # Ball out of bounds
    if bb.left > wb.right
      @player.points++
      @win @player if @player.points is @winScore
      @ball.reset()
      @ball.move 1000
    else if bb.right < wb.left
      @cpu.points++
      @win @cpu if @cpu.points is @winScore
      @ball.reset()
      @ball.move 1000

    super dt

  showTitle: (dt) ->
    fps = Math.round(1 / dt)
    title = "Score: #{@player.points} - #{@cpu.points}"
    if @debug
       title += "FPS: #{fps}"
    toy.sdl.setWindowTitle @window, title

  reset: ->
    @player.reset()
    @cpu.reset()
    @ball.reset()

  win: (player) ->
    pp = @player.points
    cp = @cpu.points
    @reset()
    @pause()
    n = 5
    title = "#{player.name} wins #{pp} - #{cp}! Game restarting in #{n--} seconds"
    toy.sdl.setWindowTitle @window, title
    interval = setInterval =>
      title = "#{player.name} wins #{pp} - #{cp}! Game restarting in #{n--} seconds"
      toy.sdl.setWindowTitle @window, title
      if n < 0
        clearInterval interval
        @unpause()
        @ball.move()
    , 1000

  render: (dt) ->
    
    super dt


class Paddle extends toy.Dynamic
  constructor: (opts = {}) ->
    super
      pos: opts.pos
      dim: opts.dim ? new toy.Vector 20, 100
      damp: opts.damp ? new toy.Vector 1, 0.95

    @speed = opts.speed ? 2000
    @points = 0

  reset: ->
    super()
    @points = 0

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
      vel: opts.vel

  move: (timeout) ->
    range = new toy.Vector -600, 600
    vel = toy.Vector.randRange range
    while Math.abs(vel.x) < 300 or Math.abs(vel.y) < 300
      vel = toy.Vector.randRange range

    clearTimeout @moveTimeout
    @moveTimeout = setTimeout =>
      @vel = vel.copy()
      clearTimeout @moveTimeout
    , timeout or 0

  update: (dt, events) ->
    if events.keyPressed toy.sdl.K_r
      @reset()
      @move()

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

