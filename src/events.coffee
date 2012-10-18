sdl = require 'sdl2'

module.exports = class Events
  
  constructor: (@game) ->
    @mouse =
      x: 0
      y: 0
    @mouse[button] = false for button in Events.BUTTONS

    @keys =
      esc: false
      del: false
    @keys[key] = false for key in Events.KEYS

    console.log @mouse, @keys

  key: (c) ->
    switch c
      when 27 then 'esc'
      when 177 then 'del'
      else String.fromCharCode c

  keyEvent: (e) ->
    code: e.sym
    modCode: e.mod || false
    key: @key e.sym
    mod: if e.mod then String.fromCharCode e.mod else false

  keyPressed: (e) =>
    event = @keyEvent e
    if @keys.hasOwnProperty event.key
      @keys[event.key] = true

    @game.emit 'keydown', event

  keyReleased: (e) =>
    event = @keyEvent e
    if @keys.hasOwnProperty event.key
      @keys[event.key] = false

    @game.emit 'keyup', event

  keyDown: (key) -> @keys[key] or false

  mouseEvent: (e) ->
    event = 
      x: e.x
      y: e.y
    if e.button
      event.button = Events.BUTTONS[e.button - 1] || e.button
    if e.xrel and e.yrel
      event.dx = e.xrel
      event.dy = e.yrel
    @mouse.x = event.x
    @mouse.y = event.y
    event

  mouseDown: (e) =>
    event = @mouseEvent e
    if @mouse.hasOwnProperty event.button
      @mouse[event.button] = true

    @game.emit 'mousedown', event

  mouseUp: (e) =>
    event = @mouseEvent e
    if @mouse.hasOwnProperty event.button
      @mouse[event.button] = false

    @game.emit 'mouseup', @mouseEvent e

  mouseMove: (e) =>
    @game.emit 'mousemove', @mouseEvent e


  @BUTTONS = [ 'left', 'middle', 'right', 'scrollup', 'scrolldown', 'side1', 'side2' ]

  @KEYS = '!"#$%&\'()*+,-./0123456789:;<=>?@[\\]^_`abcdefghijklmnopqrstuvwxyz'.split ''