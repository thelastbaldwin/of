//set up knobs

//set up THREEJS Scene
//orthographic camera
//full-size quad
var scene,
	camera,
	renderer,
	video,
	videoTexture,
	clock = new THREE.Clock(),
	ASPECT_RATIO = 1280/720,
	video = document.getElementById('oc-video'),
	container = document.getElementById('container');

init();
function init(){
	scene = new THREE.Scene();
	var WIDTH = container.offsetWidth;
	var HEIGHT = WIDTH / ASPECT_RATIO;

	camera = new THREE.OrthographicCamera( WIDTH / - 2, WIDTH / 2, HEIGHT / 2, HEIGHT / - 2, -10000, 10000 );
	camera.position.z = 100;

	videoTexture = new THREE.Texture(video);
	videoTexture.minFilter = THREE.LinearFilter;

	var plane = new THREE.PlaneBufferGeometry( WIDTH, HEIGHT );
	var material = new THREE.ShaderMaterial({
		uniforms: {
			time: {
				type: 'f',
				value: clock.getElapsedTime() * 1000
			},
			videoTexture: {
				type: 't',
				value: videoTexture
			}
		},
		// map: videoTexture,
		vertexShader: document.getElementById('vertex-shader').innerHTML,
		fragmentShader: document.getElementById('fragment-shader').innerHTML
	});
	quad = new THREE.Mesh( plane, material );
	quad.position.z = -100;
	scene.add( quad );

	renderer = new THREE.WebGLRenderer();
	renderer.setSize(WIDTH, HEIGHT);

	$('#WebGL-output').append(renderer.domElement);
	renderScene();
}

function renderScene(){
	requestAnimationFrame(renderScene);
	if( video.readyState == video.HAVE_ENOUGH_DATA ){
		videoTexture.needsUpdate = true;
	}
	//update uniforms
	renderer.render(scene, camera);
}


window.onresize = function(){
	var WIDTH = container.offsetWidth;
	var HEIGHT = WIDTH / ASPECT_RATIO;
	// notify the renderer of the size change
	renderer.setSize( WIDTH, HEIGHT );
	// update the camera
	camera.aspect = WIDTH / HEIGHT;
	camera.updateProjectionMatrix();
};
