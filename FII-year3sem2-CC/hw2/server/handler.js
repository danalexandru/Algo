exports.createHandler = function (callback) {
  return new Handler(callback);
}

Handler = function(callback) {
  this.process = function(req, res) {
    params = null;
    return callback.apply(this, [req, res, params]);
  }
}