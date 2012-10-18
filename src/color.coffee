sdl = require 'sdl2'

module.exports = class Color
  constructor: (@r = 0, @g = 0, @b = 0, @a = 255) ->

  hex: (n) ->
      (n < 16 ? '0' : '') + n.toString 16
  
  @parse: (str) ->
    if match = str.match Color.RGB
      console.log match
    else if match = str.match Color.RGBA
      console.log match
    else if match = str.match Color.HEX
      console.log match

  @RGB: /^rgb\((\d+)\s*,\s*(\d+)\s*,\s*(\d+)\)$/i

  @RGBA: /^rgba\((\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)$/i

  @HEX: /^#(([0-9a-f]{2})([0-9a-f]{2})([0-9a-f]{2})|([0-9a-f])([0-9a-f])([0-9a-f]))$/i
