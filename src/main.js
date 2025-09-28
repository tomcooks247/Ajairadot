import * as THREE from 'three';
import { FBXLoader } from 'three/examples/jsm/loaders/FBXLoader.js';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';

//scenes
const scene = new THREE.Scene();

//cameras
const camera = new THREE.PerspectiveCamera(
	75,
	window.innerWidth / window.innerHeight,
	0.1,
	1000
);
camera.position.z = 5;

//renderers
const renderer = new THREE.WebGLRenderer({ antialias: true });
renderer.setSize (window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

//win resizer
window.addEventListener('resize', () => {
	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();
	renderer.setSize(window.innerWidth, window.innerHeight);
});

//lights
const hemiLight = new THREE.HemisphereLight('white', 'white', 1);
hemiLight.position.set(0, 20, 0);
scene.add(hemiLight);

const dirLight = new THREE.DirectionalLight('white', 1);
dirLight.position.set(-5, -7.5, -5);

const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;

//model and animation loaders
let mixer;
const loader = new FBXLoader();
loader.load(
	'/models/mc.fbx',
	(object) => {
		object.scale.set(0.01, 0.01, 0.01);
		scene.add(object);
		console.log(object.animations);

	if (object.animations && object.animations.length) {
		mixer = new THREE.AnimationMixer(object);
		const action = mixer.clipAction(object.animations[0]);
		action.play();
		action.loop = THREE.LoopRepeat;
	}
});

//ani loop updater
const clock = new THREE.Clock();

function animate() {
	requestAnimationFrame(animate);

	const delta = clock.getDelta();
	if (mixer) mixer.update(delta);

	controls.update();
	renderer.render(scene, camera);
	
}

animate();

