var Editor = {
	definitions: {},
	textures: {},
	
	objects: [],
	selectedObject: null,

	filename: 'Untitled.json',

	canvas: {
		canvas: null,
		context: null,

		grid: {
			width: 16,
			height: 16
		},

		background: '#ffffff',

		view: {
			position: [0, 0],
			zoom: 2.0
		},

		cursor: [0, 0],

		dragging: {
			object: null,
			offset: [0, 0]
		},

		refreshTime: 1.0 / 40.0
	},

	input: {
		keyState: [],
		mouseWheel: 0,
		mouseState: [],
		mousePosition: [ 0, 0 ]
	}
};





function editorCreateObject(type) {
	// Check if object type is defined
	if(!(type in Editor.definitions.objects))
		return null;

	// Construct object, and set parameters
	var object = { type: type, id: '' };
	for(let key of Editor.definitions.objects[type].parameters)
		object[key] = '';

	// Set some default values
	if('position' in object)
		object.position = '' + Editor.canvas.cursor[0] + ',' + Editor.canvas.cursor[1];
	editorSetDefaultBlanks(object);

	// Add object to list & return
	Editor.objects.push(object);
	return object;
}

function editorSetDefaultBlanks(object) {
	if('scale' in object)
		object.scale = '1';	
}

function editorDeleteObject(object) {
  // Remove object from list
  Editor.objects = Editor.objects.filter(function (obj) { return obj !== object; });

  // If it was the selected or dragging object, that to null
  if(object == Editor.selectedObject) editorSelectObject(null);
  if(object == Editor.canvas.dragging.object) canvasSetDragObject(null);
};

function editorSelectObject(object) {
  Editor.selectedObject = object;
  menuSelectObject(object);
}



