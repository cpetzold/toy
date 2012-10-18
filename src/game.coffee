sdl = require 'sdl2'
events = require 'events'

Vector = require './vector'
Events = require './events'

module.exports = class Game extends events.EventEmitter
  constructor: ({ @name, @dim, @fps, @iflags, @vflags, @wflags, @bgcolor } = {}) ->
    @name ?= 'Toy'
    @dim ?= new Vector 800, 600
    @fps ?= 60

    @events = new Events @

    @entities = []

    @iflags ?= sdl.INIT_EVERYTHING
    @wflags ?= sdl.WINDOW_SHOWN
    @vflags ?= sdl.RENDER_ACCELERATED

    @_init()

  _init: ->
    sdl.init @iflags

    @window = sdl.createWindow sdl.WINDOWPOS_CENTERED, sdl.WINDOWPOS_CENTERED, @dim.x, @dim.y, @wflags

    # sdl.events.on 'QUIT', @quit
    @init?()

  init: ->
    @on 'keydown', (e) =>
      @quit() if e.key is 'esc'

  run: ->
    dt = 1.0 / @fps
    currentTime = sdl.getPerformanceCounter()
    accumulator = 0.0

    while true222
      newTime = sdl.getPerformanceCounter()
      frameTime = (newTime - currentTime) / sdl.getPerformanceFrequency()

      frametime = 0.1 if frameTime > 0.1
      accumulator += frameTime
      currentTime = newTime

      while accumulator >= dt
        @events.poll()

        accumulator -= dt

        @events.clear()

      @loop dt


  _update: (dt) ->
    @emit 'update', dt
    @update dt

  update: (dt) ->
    console.log 'game update'
    entity.update? dt for name, entity of @entities
    @

  _draw: (dt) ->
    @emit 'draw', dt
    @draw dt

  draw: (dt) ->
    @clear()

    console.log 'game draw'
    entity.draw? @screen, dt for name, entity of @entities
    
    sdl.flip @screen

  clear: ->
    sdl.fillRect @screen, [ 0, 0, @dim.x, @dim.y ], 0x000

  addEntity: (name, entity) ->
    if typeof name is 'string'
      entity.name = name
    else
      entity = name
    @entities.push entity

  quit: =>
    @emit 'quit'
    process.exit 0