
var app = angular.module('messageBoard', []);
app.controller('messageCtrl', function($scope) {
    $scope.msgList = [{msgText:'Welcome to the message board !', done:false}];

    $scope.msgAdd = function() {
    	if($scope.msgInput){
	        $scope.msgList.push({msgText:$scope.msgInput, done:false});
	        $scope.msgInput = "";

	        var container = document.getElementById("msgContainer");
	        container.scrollTop = container.scrollHeight;
        }
    };

    $scope.msgRemove = function() {
        /*
        var oldList = $scope.msgList;
        $scope.msgList = [];
        angular.forEach(oldList, function(x) {
            if (!x.done) $scope.msgList.push(x);
        });
        */
        var count = 0;
        angular.forEach($scope.msgList, function(x) {
            if (x.done) {
            	$scope.msgList.splice(count, 1);
            }
            count++;
        });
    };

    $scope.msgRemoveAll = function() {
        var oldList = $scope.msgList;
        $scope.msgList = [];
    };
});
