sdl = require 'sdl2'

exports.rect = (surface, pos, dim, color) ->
  if pos.constructor.name is 'Rect'
    rect = pos.array()
    color = dim
  else
    rect = [ pos.x, pos.y, dim.x, dim.y ]

  sdl.fillRect surface, rect, color
