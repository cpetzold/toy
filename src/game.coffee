sdl = require 'sdl2'
events = require 'events'
# sys = require 'sys'

Vector = require './vector'
Rect = require './rect'
Events = require './events'

module.exports = class Game extends events.EventEmitter
  constructor: ({ @name, @dim, @pos, @fps, @iflags, @vflags, @wflags, @bgcolor } = {}) ->
    @name ?= 'Toy'
    @dim ?= new Vector 800, 600
    @pos ?= new Vector sdl.WINDOWPOS_CENTERED, sdl.WINDOWPOS_CENTERED
    @_bounds ?= new Rect new Vector(), @dim
    @fps ?= 60
    @paused = false

    @events = new Events @

    @entities = []

    @iflags ?= sdl.INIT_EVERYTHING
    @wflags ?= sdl.WINDOW_SHOWN
    @vflags ?= sdl.RENDERER_ACCELERATED | sdl.RENDERER_PRESENTVSYNC

  _init: ->
    sdl.init @iflags

    c = sdl.WINDOWPOS_CENTERED
    @window = sdl.createWindow @name, @pos.x, @pos.y, @dim.x, @dim.y, @wflags

    @renderer = sdl.createRenderer @window, -1, @vflags

    @emit 'init'
    @init?()

  init: ->
    @quit() if @events.keyPressed sdl.K_ESCAPE

  run: ->
    @_init()

    dt = 1.0 / @fps
    currentTime = sdl.getPerformanceCounter()
    accumulator = 0.0

    while true
      newTime = sdl.getPerformanceCounter()
      frameTime = (newTime - currentTime) / sdl.getPerformanceFrequency()

      # frametime = 0.1 if frameTime > 0.1
      # accumulator += frameTime
      currentTime = newTime

      # while accumulator >= dt
      @events.poll()

      if not @paused
        @_update frameTime

      @events.clear()
        # accumulator -= dt

      @clear()
      @_render dt

      # sdl.delay 1


  _update: (dt) ->
    @emit 'update', dt
    @update dt

  update: (dt) ->
    entity.update? dt, @events for name, entity of @entities

    length = Object.keys(@entities).length
    for i in [0..length - 1]
      for j in [i..length - 1]
        @entities[i].checkCollision @entities[j]


    @

  _render: (dt) ->
    @emit 'render', dt
    @render dt

  render: (dt) ->
    entity.render? @renderer, dt for name, entity of @entities
    sdl.renderPresent @renderer

  clear: ->
    sdl.renderClear @renderer

  addEntity: (name, entity) ->
    if typeof name is 'string'
      entity.name = name
    else
      entity = name
    @entities.push entity

  quit: =>
    @emit 'quit'
    sdl.quit()
    process.exit 0

  @property 'bounds',
    get: ->
      @_bounds.dim = @dim
      @_bounds
    set: (bounds) ->
      @dim = bounds.dim

