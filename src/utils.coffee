module.exports =
  
  randRange: (min, max, precision) ->
    result = min + Math.random() * (max - min)
    if precision?
      result.toFixed precision
    else
      Math.round result