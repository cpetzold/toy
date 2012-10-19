sdl = require 'sdl2'
Vector = require './vector'

module.exports = class Events
  
  constructor: (@game) ->
    @keysPressed = {}
    @keysReleased = {}
    @keysDown = {}

    @buttonsPressed = {}
    @buttonsReleased = {}
    @buttonsDown = {}

    @quit = false

    @mouse =
      pos: new Vector()

  poll: ->
    event = {}
    while sdl.pollEvent event
      switch event.type
        when sdl.KEYDOWN
          @_keyPressed event
        when sdl.KEYUP
          @_keyReleased event
        when sdl.MOUSEBUTTONDOWN
          @_mousePressed event
        when sdl.MOUSEBUTTONUP
          @_mouseReleased event
        when sdl.MOUSEMOTION
          @_mouseMove event
        when sdl.QUIT
          @quit = true

  clear: ->
    @keysPressed = {}
    @keysReleased = {}
    @buttonsPressed = {}
    @buttonsReleased = {}
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

  _mousePressed: (e) ->
    @buttonsPressed[e.button] = true
    @buttonsDown[e.button] = true
    @mouse.pos.x = e.x
    @mouse.pos.y = e.y

  _mouseReleased: (e) ->
    @buttonsReleased[e.button] = true
    @buttonsDown[e.button] = false
    @mouse.pos.x = e.x
    @mouse.pos.y = e.y

  _mouseMove: (e) ->
    @mouse.pos.x = e.x
    @mouse.pos.y = e.y

  mousePressed: (button) -> @buttonsPressed[button] or false
  mouseReleased: (button) -> @buttonsReleased[button] or false
  mouseDown: (button) -> @buttonsDown[button] or false

