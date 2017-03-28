module.exports = function(grunt){
	grunt.initConfig({
		pkg: grunt.file.readJSON('package.json'),
		
		bowercopy: {
			dist: {
				options: {
					destPrefix: 'public/vendor'
				},
				files: {
					'material-design-lite/': 'material-design-lite/',
					'pixi.js/': 'pixi.js/'
				}
			}
		},

		watch: {
		  livereload: {
		    options: { livereload: true },
		    files: ['public/**/*']
		  }
		}
	
	});
	
	grunt.registerTask('default', ['bowercopy', 'watch']);

	grunt.loadNpmTasks('grunt-contrib-watch');
	grunt.loadNpmTasks('grunt-bowercopy');

};