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

  zero: ->
    @x = @y = 0
    @
  
  toString: ->
    'v[ ' + @x + ', ' + @y + ' ]'
