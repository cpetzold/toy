module.exports = class Vector
  constructor: (@x = 0, @y) ->
    if @x.constructor.name is 'Vector'
      return @x
    else if typeof @x is 'Array'
      return new @.constructor @x[0], @x[1]
    else if not @y?
      @y = @x
  
  get: (v) ->
    new @.constructor v

  copy: ->
    new @.constructor @x, @y

  set: (x, y) ->
    if typeof x is 'object'
      y = x.y
      x = x.x
    @x = x
    @y = y if y?
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
