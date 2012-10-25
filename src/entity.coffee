Vector = require './vector'
Rect = require './rect'

module.exports = class Entity
  constructor: (opts = {}) ->
    @pos = opts.pos ? new Vector
    @dim = opts.dim ? new Vector
    @_bounds = new Rect @pos, @dim
    @collisionLayer = opts.collisionLayer ? 0

    @original = {}
    @original.pos = @pos.copy()

  reset: ->
    @pos = @original.pos.copy()

  @property 'bounds',
    get: ->
      @_bounds.pos = @pos
      @_bounds.dim = @dim
      @_bounds
    set: (bounds) ->
      @pos = bounds.pos
      @dim = bounds.dim

  checkCollision: (entity) ->
    if @ is entity or @collisionLayer isnt entity.collisionLayer
      return

    intersection = @bounds.intersection entity.bounds
    if intersection
      @handleCollision? entity, intersection
      entity.handleCollision? @, intersection