Vector = require './vector'

module.exports = class Entity
  constructor: (opts = {}) ->
    @pos = opts.pos ? new Vector
    
  update: ->
  draw: ->