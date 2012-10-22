Vector = require './vector'
Rect = require './rect'

module.exports = class Entity
  constructor: (opts = {}) ->
    @pos = opts.pos ? new Vector
    @dim = opts.dim ? new Vector
    @_bounds = new Rect @pos, @dim

  @property 'bounds',
    get: ->
      @_bounds.pos = @pos
      @_bounds.dim = @dim
      @_bounds
    set: (bounds) ->
      @pos = bounds.pos
      @dim = bounds.dim