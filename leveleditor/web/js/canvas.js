function initCanvas() {
	// Initialize canvas
	Editor.canvas.canvas = document.querySelector('#canvas canvas');
	canvasOnResize();
 
	// Add event handlers
	window.addEventListener('resize', canvasOnResize);
	document.addEventListener('keydown', canvasOnKeyDown);
	Editor.canvas.canvas.addEventListener('mousewheel', canvasOnMouseWheel, { passive: false });
	Editor.canvas.canvas.addEventListener('mousedown', canvasOnMouseDown);
	Editor.canvas.canvas.addEventListener('mouseup', canvasOnMouseUp);
	Editor.canvas.canvas.addEventListener('mousemove', canvasOnMouseMove);

	// Disable context menu on canvas
	Editor.canvas.canvas.addEventListener('contextmenu', function (event) { event.preventDefault(); });

	// Set (update & render) loop
	setInterval(function () {
		canvasUpdate();
		canvasDraw();
	}, Editor.canvas.refreshTime * 1000);
}


function canvasOnMouseWheel(event) {
	if(inputKeyDown(KEY_ACTION)) {
		Editor.canvas.view.zoom *= Math.exp(event.wheelDelta / 10000.0);
	}
	else {
		Editor.canvas.view.position[0] -= event.wheelDeltaX / (5.0 * Editor.canvas.grid.width  * Editor.canvas.view.zoom);
		Editor.canvas.view.position[1] += event.wheelDeltaY / (5.0 * Editor.canvas.grid.height * Editor.canvas.view.zoom);
	}

	// Prevent leaving the site (e.g. goto previous page / history)
	event.preventDefault();
}

function canvasOnMouseDown(event) {
	for(let object of Editor.objects) {
		if(canvasIsHoveringObject(object)) {
			editorSelectObject(object);
			return;
		}
	}
	editorSelectObject(null);
}

function canvasOnMouseUp(event) {
	canvasDragObject(null);
	editorSelectObject(Editor.selectedObject); // Resulting in a refresh
}

function canvasOnMouseMove(event) {
	if(inputMouseDown(MOUSE_LEFT) && Editor.selectedObject != null && Editor.canvas.dragging.object != Editor.selectedObject)
		canvasDragObject(Editor.selectedObject);
}

function canvasOnKeyDown(event) {
	if(!canvasHasFocus())
		return;

	switch(event.keyCode) {
		case KEY_N: // New object
			let object = editorCreateObject('tile');
			canvasDragObject(object);
			break;

		case KEY_D: // Duplicate selected object
			if(Editor.selectedObject != null) {
				let object = Object.assign({}, Editor.selectedObject);
				object.position = '' + Editor.canvas.cursor[0] + ',' + Editor.canvas.cursor[1];
				canvasDragObject(object);
				Editor.objects.push(object);
			}
			break;

		case KEY_DELETE: // Delete selected object
			if(Editor.selectedObject != null)
				editorDeleteObject(Editor.selectedObject);
			break;
	}
}

function canvasOnResize() {
	Editor.canvas.canvas.width = Editor.canvas.canvas.clientWidth;
	Editor.canvas.canvas.height = Editor.canvas.canvas.clientHeight;
	Editor.canvas.context = Editor.canvas.canvas.getContext('2d');
	Editor.canvas.context.imageSmoothingEnabled = false;
}

function canvasHasFocus() {
	return !document.activeElement || (document.activeElement.tagName.toLowerCase() != 'input');
}

function canvasUpdate() {
	// Update cursor
	let rect = Editor.canvas.canvas.getBoundingClientRect();
	let mouse = inputMouse();
	let position = [ mouse[0] - rect.x, mouse[1] - rect.y ];
	canvasCoordinatesToPosition(position);
	Editor.canvas.cursor[0] = position[0];
	Editor.canvas.cursor[1] = position[1];

	// Update view
	canvasUpdateView();

	// Update selected object
	if(Editor.canvas.dragging.object != null) {
		let x = Editor.canvas.cursor[0] - Editor.canvas.dragging.offset[0];
		let y = Editor.canvas.cursor[1] - Editor.canvas.dragging.offset[1];
		if(!inputKeyDown(KEY_ALT)) {
			x = Math.floor(x + 0.5);
			y = Math.floor(y - 0.5) + 1.0;
		}
		Editor.canvas.dragging.object.position = '' + x + ',' + y;
	}
}

function canvasUpdateView() {
	// Camera movement
	if(canvasHasFocus()) {
		if(inputKeyDown(KEY_UP))    Editor.canvas.view.position[1] += 10.0 / Editor.canvas.view.zoom * Editor.canvas.refreshTime;
		if(inputKeyDown(KEY_DOWN))  Editor.canvas.view.position[1] -= 10.0 / Editor.canvas.view.zoom * Editor.canvas.refreshTime;
		if(inputKeyDown(KEY_LEFT))  Editor.canvas.view.position[0] -= 10.0 / Editor.canvas.view.zoom * Editor.canvas.refreshTime;
		if(inputKeyDown(KEY_RIGHT)) Editor.canvas.view.position[0] += 10.0 / Editor.canvas.view.zoom * Editor.canvas.refreshTime;
	}
};

function canvasDraw() {
	// Clear screen
	Editor.canvas.context.fillStyle = Editor.canvas.background;
	Editor.canvas.context.fillRect(0, 0, Editor.canvas.canvas.width, Editor.canvas.canvas.height);

	// Draw grid, objects, selection border & cursor coordinates
	canvasDrawGrid();
	canvasDrawObjects();
	canvasDrawCursorCoordinates();
};

function canvasDrawGrid() {
	// Get context
	var ctx = Editor.canvas.context;

	// Grid style
	ctx.strokeStyle = textColor(Editor.canvas.background);
	ctx.lineWidth = 1;

	// Determine origin
	var origin = [0, 0];
	canvasPositionToCoordinates(origin);

	// Draw vertical lines
	var dx = Editor.canvas.grid.width * Editor.canvas.view.zoom;
	while(dx < 16) dx *= 2;
	for(var x = origin[0] % dx;x < Editor.canvas.canvas.width;x += dx) {
		ctx.beginPath();
		ctx.moveTo(x - 0.5, 0);
		ctx.lineTo(x - 0.5, Editor.canvas.canvas.height);
		ctx.stroke();
	}

	// Draw horizontal lines
	var dy = Editor.canvas.grid.height * Editor.canvas.view.zoom;
	while(dy < 16) dy *= 2;
	for(var y = origin[1] % dy;y < Editor.canvas.canvas.height;y += dy) {
		ctx.beginPath();
		ctx.moveTo(0, y + 0.5);
		ctx.lineTo(Editor.canvas.canvas.width, y + 0.5);
		ctx.stroke();
	}
};

function canvasDrawObjects() {
	for(let object of Editor.objects)
		canvasDrawObject(object);
};

function canvasDrawObject(object) {
	// Requires position
	if(!('position' in object))
		return;

	let ctx = Editor.canvas.context;
	let box = canvasGetObjectBoundingBox(object);

	if(!('sprite' in object) || !(object.sprite in Editor.definitions.sprites)) {
		// If no size, simply draw a circle
		ctx.beginPath();
		ctx.arc(box[0] + 0.5 * box[2], box[1] + 0.5 * box[3], 8, 0, 2 * Math.PI, false);
		ctx.fillStyle = '#4d87c3';
		ctx.globalAlpha = ((object == Editor.canvas.dragging.object) ? 0.5 : 1.0);
		ctx.fill();
		ctx.globalAlpha = 1.0;

		if(Editor.selectedObject == object) {
			ctx.strokeStyle = '#c34d4d';
			ctx.lineWidth = 3;
			ctx.beginPath();
			ctx.arc(box[0] + 0.5 * box[2], box[1] + 0.5 * box[3], 16, 0, 2 * Math.PI, false);
			ctx.stroke();	
		}
	}
	else {
		let sprite = Editor.definitions.sprites[object.sprite];

		// Lookup texture
		let texture = textureGet(sprite.texture);
		if(texture != null) {
			ctx.globalAlpha = (object == Editor.canvas.dragging.object) ? 0.5 : 1.0;
			ctx.drawImage(
				texture,
				sprite.frame[0],
				sprite.frame[1],
				sprite.frame[2],
				sprite.frame[3],
				box[0],
				box[1],
				box[2],
				box[3]
			);
			ctx.globalAlpha = 1.0;
		}
		else {
			ctx.fillStyle = '#4d87c3';
			ctx.fillRect(box[0], box[1], box[2], box[3]);
		}

		if(Editor.selectedObject == object) {
			ctx.strokeStyle = '#c34d4d';
			ctx.lineWidth = 3;
			ctx.strokeRect(box[0], box[1], box[2], box[3]);
		}
	}
};

function canvasDrawCursorCoordinates() {
	// Only draw if hovering canvas
	if(!canvasIsHovering())
		return;

	// Get cursor coordinates
	let x = Editor.canvas.cursor[0];
	let y = Editor.canvas.cursor[1];

	// Possibly round coordinates
	if(!inputKeyDown(KEY_ALT)) {
		x = Math.round(x);
		y = Math.round(y);
	}
	
	// Transform coordinates
	let position = [x, y];
	canvasPositionToCoordinates(position);

	// Draw coordinates
	let ctx = Editor.canvas.context;
	ctx.font = '10px museosans';
	ctx.textAlign = 'center';
	ctx.textBaseline = 'middle';
	let str = '(' + (Math.round(x * 100) / 100) + ', ' + (Math.round(y * 100) / 100) + ')';
	let w = ctx.measureText(str).width + 8;
	ctx.fillStyle = 'black';
	ctx.globalAlpha = 0.5;
	ctx.fillRect(position[0] - w / 2, position[1] - 12, w, 24);
	ctx.globalAlpha = 1.0;
	ctx.fillStyle = 'white';
	ctx.fillText(str, position[0], position[1]);
};

// Transformation functions
function canvasPositionToCoordinates(v) {
	v[0] = Editor.canvas.canvas.width / 2 + (v[0] - Editor.canvas.view.position[0]) * Editor.canvas.grid.width * Editor.canvas.view.zoom;
	v[1] = Editor.canvas.canvas.height / 2 - (v[1] - Editor.canvas.view.position[1]) * Editor.canvas.grid.height * Editor.canvas.view.zoom;
}

function canvasCoordinatesToPosition(v) {
	v[0] = (v[0] - Editor.canvas.canvas.width / 2) / (Editor.canvas.grid.width * Editor.canvas.view.zoom) + Editor.canvas.view.position[0];
	v[1] = - (v[1] - Editor.canvas.canvas.height / 2) / (Editor.canvas.grid.height * Editor.canvas.view.zoom) + Editor.canvas.view.position[1];
}

function canvasSizeToCanvasSize(s) {
	s[0] = s[0] * Editor.canvas.grid.width * Editor.canvas.view.zoom;
	s[1] = s[1] * Editor.canvas.grid.height * Editor.canvas.view.zoom;
}

function canvasCanvasSizeToSize(s) {
	s[0] = s[0] / (Editor.canvas.grid.width * Editor.canvas.view.zoom);
	s[1] = s[1] / (Editor.canvas.grid.height * Editor.canvas.view.zoom);
}

function canvasIsHoveringObject(object) {
	// Requires position
	if(!('position' in object))
		return false;

	let box = canvasGetObjectBoundingBox(object);
	let mouse = [ Editor.canvas.cursor[0], Editor.canvas.cursor[1] ];
	canvasPositionToCoordinates(mouse);

	return mouse[0] > box[0] && mouse[1] > box[1] && mouse[0] < box[0] + box[2] && mouse[1] < box[1] + box[3];
}

function canvasGetObjectBoundingBox(object) {
	// Determine position
	let position = object.position.split(',').map((s) => parseFloat(s));
	canvasPositionToCoordinates(position);

	// If there is no sprite, use a box of 8px around object position
	let size = [ 16, 16 ];
	let center = [ 8, 8 ];

	if('sprite' in object && object.sprite in Editor.definitions.sprites) {
		let sprite = Editor.definitions.sprites[object.sprite];

		// Scale factor
		let scale = [ 1, 1 ];
		if('scale' in object) {
			let s = parse(object.scale);
			if(typeof s === 'number')
				scale = [ s, s ];
			
			if(Array.isArray(s) && s.length >= 2 && typeof s[0] == 'number' && typeof s[1] == 'number')
				scale = [ s[0], s[1] ];
		}

		// Compute size & center
		size = [ sprite.frame[2] / Editor.canvas.grid.width * scale[0],
		         sprite.frame[3] / Editor.canvas.grid.height * scale[1] ];
		canvasSizeToCanvasSize(size);

		// Sprite center
		center = [ 0, 0 ];
		if('center' in sprite)
			center = [ sprite.center[0] / sprite.frame[2] * size[0] ,
	    	           sprite.center[1] / sprite.frame[3] * size[1] ];
	}
	
	return [ position[0] - center[0], position[1] - center[1], size[0], size[1] ];
}

function canvasIsHovering() {
	let mouse = inputMouse();
	let rect = Editor.canvas.canvas.getBoundingClientRect();
	return mouse[0] > rect.left && mouse[0] < rect.right && mouse[1] > rect.top && mouse[1] < rect.bottom;
};

function canvasDragObject(object) {
	// If null, reset dragging object
	if(object == null) {
		Editor.canvas.dragging.object = null;
		return;
	}

	// Requires position
	if(!('position' in object))
		return;

	let position = object.position.split(',').map((x) => parseFloat(x));

	// Set dragging object
	Editor.canvas.dragging.object = object;

	// Set dragging offset
	Editor.canvas.dragging.offset[0] = Editor.canvas.cursor[0] - position[0];
	Editor.canvas.dragging.offset[1] = Editor.canvas.cursor[1] - position[1];
};
