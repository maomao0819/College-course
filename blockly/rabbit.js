var workspace = Blockly.inject('blocklyDiv',
	{toolbox: document.getElementById('toolbox'),
	grid:
		{spacing: 20,
		length: 20,
		colour: '#ccc',
		snap: true},
	trashcan: true,
	zoom:
		{controls: true,
		scaleSpeed: 1.2},
		wheel: true,
		startScale: 1.0,
		maxScale: 3,
		minScale: 0.3,
	}
);
var canvas = document.getElementById("rabbitCanvas");
var ctx = canvas.getContext("2d");
var img = new Image();
img.addEventListener('load', function () {
	ctx.fillStyle = "#FF0011";
	ctx.fillRect(0, 0, canvas.width, canvas.height);
	ctx.fillStyle = "green";
	ctx.fillRect(60, 50, canvas.width - 60 * 2, canvas.height - 50 * 2);
});
img.src="rabbit.png";

var frameWidth = 10;
var frameHeight = 40;
var frameNum = 22;
var speed = 5;
var distance = 20;
var x=y=0, ox=oy=0;
var pointer, counter = 0;
var state = 0;
var point = 0;
var lap = 0;
const STANDBY = 0, UP = 1, RIGHT = 2, DOWN = 3, LEFT = 4;
var direction;

function rabbitDraw(direction) {
	switch (direction) {
		case STANDBY: 
		rabbitStandBy();
			break;
		case UP:
		rabbit2up();
			break;
		case DOWN:
		rabbit2down();
			break;
		case LEFT: 
		rabbit2left();
			break;
		case RIGHT:
		rabbit2right();
			break;
	}
}
function showText()
{		
	ctx.fillStyle = "black";
	ctx.fillText(state ,100, 100);
}
function rabbit2up() {
	if(state == 0 || state == UP)
	{
		ctx.save();
		ctx.fillStyle = "#FF0011";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
		ctx.fillStyle = "green";
		ctx.fillRect(60, 50, canvas.width - 60 * 2, canvas.height - 50 * 2);
		//ctx.clearRect(ox, oy, frameWidth, frameHeight);
		pointer = Math.floor(((++counter) % (frameNum * speed)) / speed);
		ctx.drawImage(img, pointer * frameWidth, 0, frameWidth, frameHeight, x, y, frameWidth, frameHeight);
		showText();
		ctx.restore();
		state = UP;
		ox = x;
		oy = y;
		if(y > 0)
			y--;
		else {
			state = 0;
			return;
		}
	}
	requestAnimationFrame(rabbit2up);
}
function rabbit2down() {
	if(state == 0 || state == DOWN)
	{
		ctx.save();
		//ctx.scale(-1, 1);
		ctx.fillStyle = "#FF0011";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
		ctx.fillStyle = "green";
		ctx.fillRect(60, 50, canvas.width - 60 * 2, canvas.height - 50 * 2);
		//ctx.clearRect(ox, oy, 20, 10);
		pointer = Math.floor(((++counter) % (frameNum * speed)) / speed);
		ctx.drawImage(img, pointer*frameWidth, 0, frameWidth, frameHeight, x, y, frameWidth, frameHeight);
		//showText();
		ctx.restore();
		state = DOWN;
		ox = x;
		oy = y;
		if(y < canvas.height - frameHeight)
			y++;
		else {
			state = 0;
			return;
		}
	}
	requestAnimationFrame(rabbit2down);
}
function rabbit2left() {
	if(state == 0 || state == LEFT)
	{
		ctx.save();
		ctx.fillStyle = "#FF0011";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
		ctx.fillStyle = "green";
		ctx.fillRect(60, 50, canvas.width - 60 * 2, canvas.height - 50 * 2);
		//ctx.clearRect(ox, oy, frameWidth, frameHeight);
		pointer = Math.floor(((++counter) % (frameNum * speed)) / speed);
		ctx.drawImage(img, pointer * frameWidth, 0, frameWidth, frameHeight, x, y, frameWidth, frameHeight);
		//showText();
		ctx.restore();
		state = LEFT;
		ox = x;
		oy = y;
		if(x > 0)
			x--;
		else {
			state = 0;
			return;
		}
	}	
	requestAnimationFrame(rabbit2left);
}
function rabbit2right() {
	if(state == 0 || state == RIGHT)
	{
		ctx.save();
		ctx.fillStyle = "#FF0011";
		ctx.fillRect(0, 0, canvas.width, canvas.height);
		ctx.fillStyle = "green";
		ctx.fillRect(60, 50, canvas.width - 60 * 2, canvas.height - 50 * 2);
		//ctx.clearRect(ox, oy, frameWidth, frameHeight);
		pointer = Math.floor(((++counter) % (frameNum * speed)) / speed);
		ctx.drawImage(img, pointer * frameWidth, 0, frameWidth, frameHeight, x, y, frameWidth, frameHeight);
		//showText();
		ctx.restore();
		state = RIGHT;
		ox = x;
		oy = y;
		if(x < canvas.width-frameWidth)
			x++;
		else {
			state = 0;
			return;
		}
	}
	requestAnimationFrame(rabbit2right);
}

document.getElementById("run").addEventListener("click", runReading);
document.getElementById("save").addEventListener("click", saveWorkspace);
document.getElementById("restore").addEventListener("click", restoreWorkspace);


function runReading() {
	reseting();
	Blockly.JavaScript.addReservedWords('code');
	var code = Blockly.JavaScript.workspaceToCode(workspace);
	try {
		eval(code);
		} catch (e) {
		alert(e);
	}
}
function reseting() {
	frameWidth = 74;
	frameHeight = 40;
	frameNum = 22;
	speed = 5;
	x=y=0, ox=oy=0;
	pointer, counter = 0;
}
function saveWorkspace() {
	var xmlDom = Blockly.Xml.workspaceToDom(Blockly.mainWorkspace);
	var xmlText = Blockly.Xml.domToPrettyText(xmlDom);
	alert(xmlText);
	localStorage.setItem("blockly.xml", xmlText);
	
}
function restoreWorkspace() {
	var xmlText = localStorage.getItem("blockly.xml");
	if(xmlText) {
		Blockly.mainWorkspace.clear();
		xmlDom = Blockly.Xml.textToDom(xmlText);
		Blockly.Xml.domToWorkspace(Blockly.mainWorkspace, xmlDom);
	}
}
