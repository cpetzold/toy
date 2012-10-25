utils = require './utils'

module.exports = class Vector
  constructor: (@x = 0, @y) ->
    @set @x, @y
    return
  
  get: (v) ->
    new @.constructor v

  copy: ->
    new @.constructor @x, @y

  set: (x, y) ->
    if x.constructor.name is 'Vector'
      @x = x.x
      @y = x.y
    else if typeof x is 'Array'
      @x = x[0]
      @y = x[1]
    else if not y?
      @y = @x = x
    @

  eq: (v) -> @x is v.x and @y is v.y
  gt: (v) -> @x > v.x and @y > v.y
  gte: (v) -> @x >= v.x and @y >= v.y
  lt: (v) -> @x < v.x and @y < v.y
  lte: (v) -> @x <= v.x and @y <= v.y
  
  add: (v) ->
    v = @get v
    @x += v.x
    @y += v.y
    @
    
  subtract: (v) ->
    v = @get v
    @x -= v.x
    @y -= v.y
    @
  
  multiply: (v) ->
    v = @get v
    @x *= v.x
    @y *= v.y
    @
    
  divide: (v) ->
    v = @get v
    @x /= v.x
    @y /= v.y
    @
    
  cross: (v) ->
    v = @get v
    @x * v.y - @y * v.x
    
  dot: (v) ->
    v = @get v
    @x * v.x + @y * v.y
    
  magnitude: ->
    Math.sqrt @x * @x + @y * @y
    
  normalize: ->
    m = @magnitude()
    @x /= m
    @y /= m
    @

  @randRange: (xrange, yrange) ->
    if typeof xrange is 'number' and typeof yrange is 'number'
      xrange = new @.constructor xrange, yrange
    x = utils.randRange xrange.x, xrange.y
    if not yrange?
      y = utils.randRange xrange.x, xrange.y
    else
      y = utils.randRange yrange.x, yrange.y
    new Vector x, y

  zero: ->
    @x = @y = 0
    @
  
  toString: ->
    'v[ ' + @x + ', ' + @y + ' ]'
