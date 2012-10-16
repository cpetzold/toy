var assert = require('assert')
  , toy = require('../');

describe('Vec', function() {

  describe('#new()', function() {

    it('should create a Vec(0, 0) by default', function() {
      var v = new toy.Vec();
      assert.equal(0, v.x);
      assert.equal(0, v.y);
    });

  });

  describe('#mult', function() {

    it('should return a new vector with both x and y multiplied by a scalar', function() {
      var v = new toy.Vec(2, 2);
      var r = v.mult(2);
      assert.equal(4, r.x);
      assert.equal(4, r.y);
    });

    it('should return a new vector with both x and y multiplied by the other vector', function() {
      var v = new toy.Vec(2, 2)
        , v2 = new toy.Vec(2, 3);
      var r = v.mult(v2);
      assert.equal(4, r.x);
      assert.equal(6, r.y);
    });

  });

  describe('#multSelf', function() {

    it('should multiply x and y by a scalar', function() {
      var v = new toy.Vec(2, 2);
      v.multSelf(2);
      assert.equal(4, v.x);
      assert.equal(4, v.y);
    });

    it('should multiply by another vec', function() {
      var v = new toy.Vec(2, 2)
        , v2 = new toy.Vec(2, 3);
      v.multSelf(v2);
      assert.equal(4, v.x);
      assert.equal(6, v.y);
    });

  });

  describe('#add', function() {

    it('should add x and y by a scalar', function() {
      var v = new toy.Vec(2, 2);
      v.multSelf(2);
      assert.equal(4, v.x);
      assert.equal(4, v.y);
    });

    it('should multiply by another vec', function() {
      var v = new toy.Vec(2, 2)
        , v2 = new toy.Vec(2, 3);
      v.multSelf(v2);
      assert.equal(4, v.x);
      assert.equal(6, v.y);
    });

  });

});