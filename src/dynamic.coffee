Vector = require './vector'
Entity = require './entity'

module.exports = class Dynamic extends Entity
  constructor: (opts = {}) ->
    super opts

    @vel = opts.vel ? new Vector
    @acc = opts.acc ? new Vector
    @damp = opts.damp ? new Vector 1

    @original.vel = @vel.copy()
    @original.acc = @acc.copy()
    @original.damp = @damp.copy()

  reset: ->
    super()
    @vel = @original.vel.copy()
    @acc = @original.acc.copy()
    @damp = @original.damp.copy()

  update: (dt) ->
    acc = @acc.copy()

    @vel.add acc.multiply dt
    @vel.multiply @damp

    @pos.add @vel.copy().multiply dt

    @acc.zero()
