sdl = require 'sdl2'
Rect = require './rect'

exports.rect = (renderer, pos, dim, color) ->
  if pos.constructor.name is 'Rect'
    rect = pos
    color = dim
  else
    rect = new Rect pos, dim

  sdl.renderFillRect renderer, rect.sdlRect()
