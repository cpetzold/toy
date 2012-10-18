sdl = require 'sdl2'

module.exports = class Events
  
  constructor: (@game) ->
    @keysPressed = {}
    @keysReleased = {}
    @keysDown = {}
    @quit = false

  poll: ->
    event = {}
    while sdl.pollEvent event
      switch event.type
        when sdl.KEYDOWN
          @_keyPressed event
        when sdl.KEYUP
          @_keyReleased event
        # when sdl.MOUSEBUTTONDOWN
        #   @_mouseDown event
        # when sdl.MOUSEBUTTONUP
        #   @_mouseUp event
        # when sdl.MOUSEMOTION
        #   @_mouseMove event
        when sdl.QUIT
          @quit = true

  clear: ->
    @keysPressed = {}
    @keysReleased = {}
    @quit = false

  _keyPressed: (e) =>
    @keysPressed[e.sym] = true
    @keysDown[e.sym] = true

  _keyReleased: (e) =>
    @keysReleased[e.sym] = true
    @keysDown[e.sym] = false

  keyPressed: (key) -> @keysPressed[key] or false
  keyReleased: (key) -> @keysReleased[key] or false
  keyDown: (key) -> @keysDown[key] or false

