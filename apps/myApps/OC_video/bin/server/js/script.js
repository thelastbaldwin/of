//set up knobs

//set up THREEJS Scene
var scene,
	camera,
	renderer,
	video,
	videoTexture,
	videoMaterial,
	isButtonPressed = false,
	clock = new THREE.Clock(),
	ASPECT_RATIO = 1280/720,
	video = document.getElementById('oc-video'),
	container = document.getElementById('container');

function init(){
	scene = new THREE.Scene();
	var WIDTH = container.offsetWidth;
	var HEIGHT = WIDTH / ASPECT_RATIO;

	camera = new THREE.OrthographicCamera( WIDTH / - 2, WIDTH / 2, HEIGHT / 2, HEIGHT / - 2, -10000, 10000 );
	camera.position.z = 100;

	videoTexture = new THREE.Texture(video);
	videoTexture.minFilter = THREE.LinearFilter;
	// videoTexture.wrapS = THREE.RepeatWrapping;

	var plane = new THREE.PlaneBufferGeometry( WIDTH, HEIGHT );
	videoMaterial = new THREE.ShaderMaterial({
		uniforms: {
			time: {
				type: 'f',
				value: clock.getElapsedTime() * 1000
			},
			scanlineThickness: {
				type: 'f',
				value: 4.0
			},
			scanlineOpacity: {
				type: 'f',
				value: 0.4
			},
			height: {
				type: 'f',
				value: HEIGHT
			},
			width: {
				type: 'f',
				value: WIDTH
			},
			videoTexture: {
				type: 't',
				value: videoTexture
			},
			scrollSpeed: {
				type: 'f',
				value: parseFloat(document.getElementById('scrollSpeed').value)
			},
			wavelength: {
				type: 'f',
				value: 0.04
			},
			speed:{
				type: 'f',
				value: 0.007
			},
			amplitude: {
				type: 'f',
				value: 0.006
			}
		},
		// map: videoTexture,
		vertexShader: document.getElementById('vertex-shader').innerHTML,
		fragmentShader: document.getElementById('fragment-shader').innerHTML
	});
	quad = new THREE.Mesh( plane, videoMaterial );
	quad.position.z = -100;
	scene.add( quad );

	renderer = new THREE.WebGLRenderer();
	renderer.setSize(WIDTH, HEIGHT);

	document.getElementById('WebGL-output').appendChild(renderer.domElement);
	renderScene();
}

function renderScene(){
	requestAnimationFrame(renderScene);
	if( video.readyState == video.HAVE_ENOUGH_DATA ){
		videoTexture.needsUpdate = true;
	}
	//update uniforms
	videoMaterial.uniforms.time.value = clock.getElapsedTime() * 100;
	videoMaterial.uniforms.scrollSpeed.value = document.getElementById('scrollSpeed').value;

	if(isButtonPressed){
		videoMaterial.uniforms.wavelength.value = 0.3;
		videoMaterial.uniforms.amplitude.value = 0.09;
		videoMaterial.uniforms.speed.value = 0.01;
	}else{
		videoMaterial.uniforms.wavelength.value = 0.04;
		videoMaterial.uniforms.amplitude.value = 0.006;
		videoMaterial.uniforms.speed.value = 0.007;
	}
	renderer.render(scene, camera);
}

document.getElementById('wigout').onclick = function(){
	isButtonPressed = !isButtonPressed;
};

window.onresize = function(){
	var WIDTH = container.offsetWidth;
	var HEIGHT = WIDTH / ASPECT_RATIO;
	// notify the renderer of the size change
	renderer.setSize( WIDTH, HEIGHT );
	// update the camera
	camera.aspect = WIDTH / HEIGHT;
	camera.updateProjectionMatrix();

	videoMaterial.uniforms.height.value = HEIGHT;
	videoMaterial.uniforms.width.value = WIDTH;
};

init();
