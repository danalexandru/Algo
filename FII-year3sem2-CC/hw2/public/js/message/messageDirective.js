app.directive('message', function() { 
  return { 
    restrict: 'E',
    replace: true,
    templateUrl: 'js/message/messagePartial.html' 
  }; 
});