sdl = require 'sdl2'
events = require 'events'

Vector = require './vector'
Events = require './events'

module.exports = class Game extends events.EventEmitter
  constructor: ({ @name, @dim, @fps, @iflags, @vflags, @wflags, @bgcolor } = {}) ->
    @name ?= 'Toy'
    @dim ?= new Vector 800, 600
    @fps ?= 60
    @paused = false

    @events = new Events @

    @entities = []

    @iflags ?= sdl.INIT_EVERYTHING
    @wflags ?= sdl.WINDOW_SHOWN
    @vflags ?= sdl.RENDERER_ACCELERATED

  _init: ->
    sdl.init @iflags

    c = sdl.WINDOWPOS_CENTERED
    @window = sdl.createWindow @name, c, c, @dim.x, @dim.y, @wflags

    @renderer = sdl.createRenderer @window, -1, @vflags

    @emit 'init'
    @init?()

  init: ->
    @on 'keydown', (e) =>
      @quit() if e.key is 'esc'

  run: ->
    @_init()

    dt = 1.0 / @fps
    currentTime = sdl.getPerformanceCounter()
    accumulator = 0.0

    while true
      newTime = sdl.getPerformanceCounter()
      frameTime = (newTime - currentTime) / sdl.getPerformanceFrequency()

      frametime = 0.1 if frameTime > 0.1
      accumulator += frameTime
      currentTime = newTime

      while accumulator >= dt
        @events.poll()

        if not @paused
          @_update dt

        @events.clear()
        accumulator -= dt

      @_render dt
      sdl.delay 1


  _update: (dt) ->
    @emit 'update', dt
    @update dt

  update: (dt) ->
    entity.update? dt for name, entity of @entities
    @

  _render: (dt) ->
    @emit 'render', dt
    @render dt

  render: (dt) ->
    @clear()

    entity.draw? @screen, dt for name, entity of @entities
    
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

