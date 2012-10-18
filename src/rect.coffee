Vector = require './vector'

module.exports = class Rect
  constructor: (x, y, w, h) ->
    if typeof x is 'array'
      if x.length is 4
        @pos = new Vector x[0], x[1]
        @dim = new Vector x[2], x[3]
      else
        @pos = new Vector x[0], x[1]
        @dim = new Vector y[0], y[1]
    else if typeof x.constructor.name is 'Vector'
      @pos = x
      @dim = y
    else
      @pos = new Vector x, y
      @dim = new Vector w, h

  array: -> [ @pos.x, @pos.y, @dim.x, @dim.y ]
  
  toString: ->
    'r[ ' + @pos[0] + ', ' + @pos[1] + ', ' + @dim[0] + ', ' + @dim[1] + ' ]'
