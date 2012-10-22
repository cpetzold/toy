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
    else if x.constructor.name is 'Vector'
      @pos = x
      @dim = y
    else
      @pos = new Vector x, y
      @dim = new Vector w, h

  @property 'top',
    get: ->
      @pos.y
    set: (top) ->
      @pos.y = top

  @property 'bottom',
    get: ->
      @pos.y + @dim.y
    set: (bottom) ->
      @pos.y = bottom - @dim.y

  @property 'left',
    get: ->
      @pos.x
    set: (left) ->
      @pos.x = left

  @property 'right',
    get: ->
      @pos.x + @dim.x
    set: (right) ->
      @pos.x = right - @dim.x

  @property 'center',
    get: ->
      center = @pos.copy()
      offset = @dim.copy().divide 2
      center.add offset
    set: (center) ->
      @pos.set center
      offset = @dim.copy().divide 2
      @pos.set center.subtract(offset)

  array: -> [ @pos.x, @pos.y, @dim.x, @dim.y ]
  
  toString: ->
    'r[ ' + @pos[0] + ', ' + @pos[1] + ', ' + @dim[0] + ', ' + @dim[1] + ' ]'
