
var app = angular.module('messageBoard', ['ui.router']);

app.config(function($httpProvider) {
  //$httpProvider.defaults.headers.delete = { 'Content-Type' : 'application/json' };
});

app.controller('messageCtrl', ['$scope', '$http', function($scope, $http) {
    $scope.msgList = [{msgText:'Welcome to the message board !', done:false}];
    $scope.msgMongoList = [];

    //Create
    $scope.msgAdd = function() {
    	if($scope.msgInput){
                $scope.msgList.push({msgText:$scope.msgInput, done:false});

                //console.log($scope.msgList);

                var copy = $scope.msgInput;
                $scope.msgInput = "";

                var container = document.getElementById("msgContainer");
                container.scrollTop = container.scrollHeight;

                copy = JSON.stringify({ content: copy });
                console.log('posting: ', copy);

                $http.post('/api/messages', copy)
                    .success(function(data) {
                        console.log("posted successfully");
                    }).error(function(data) {
                        console.error("error in posting");
                    });

                var container = document.getElementById("msgContainer");
                container.scrollTop = container.scrollHeight;
        }
    };

    //Read
    $scope.msgRetrieve = function() {
        $scope.msgList = [{content:'Welcome to the message board !', done:false}];

        $scope.loading = true;

        var data;
        var promise = $http.get('/api/messages').
                success(function(data) {
                    console.log("get successfully");
                    //console.log(angular.fromJson(data));

                }).error(function(data) {
                    console.error("error in get");
                }).then(function(dat){
                    data = dat.data;
                    //console.log(data);

                    if(data){
                        $scope.msgMongoList = angular.fromJson(data);

                        angular.forEach($scope.msgMongoList, function(value, key) {
                            //console.log(key + ': ' + value);
                            var i = 0;

                            // console.log('old');
                            // console.log($scope.msgList);
                            var id, content, timestamp;
                            $scope.msgList.push(value);
                            console.log('new');
                            console.log($scope.msgList);

                            $scope.loading = false;
                            //console.dir(value);
                            var container = document.getElementById("msgContainer");
                            container.scrollTop = container.scrollHeight;
                        });
                        //$scope.$apply();
                    }
                });
    };
    $scope.msgRetrieve(); //should run on window.onload

    //Update

    //Delete
    $scope.msgRemove = function() {
        var count = 0;
        angular.forEach($scope.msgList, function(x) {
            if (x.done) {
                $scope.msgList.splice(count, 1);

                if(x._id){
                    // $http.delete('/api/messages', x._id)
                    //     .success(function(data) {
                    //         console.log("delete successfully");
                    //     }).error(function(data) {
                    //         console.error("error in deleting");
                    //     });
                    var req = {
                     method: 'DELETE',
                     url: '/api/messages',
                     headers: {
                       'Content-Type': 'text/plain',
                       'Content-Length': 0 //otherwise diregarded by server (since http 0.11)
                     },
                     data: x._id
                    };
                    $http(req)
                        .success(function(data) {
                            console.log("delete successfully");
                        }).error(function(data) {
                            console.error("error in deleting");
                        });
                }
            }
            count++;
        });
    };

    $scope.msgRemoveAll = function() {
        // var oldList = $scope.msgList;
        // $scope.msgList = [];
        console.log('check');
        console.log($scope.msgList);
        var count = 0;
        angular.forEach($scope.msgList, function(x) {
            //$scope.msgList.splice(count, 1);

            console.log(x);
            if(x._id){
                var req = {
                 method: 'DELETE',
                 url: '/api/messages',
                 headers: {
                   'Content-Type': 'text/plain',
                   'Content-Length': 0 //otherwise diregarded by server (since http 0.11)
                 },
                 data: x._id
                };
                $http(req)
                    .success(function(data) {
                        console.log("delete successfully");
                    }).error(function(data) {
                        console.error("error in deleting");
                    });
            }
            count++;
        });
    };
}]);

app.directive('message', function() { 
  return { 
    restrict: 'E',
    replace: true,
    scope: { 
      info: '=' 
    }, 
    templateUrl: 'messagePartial.html' 
  }; 
});
