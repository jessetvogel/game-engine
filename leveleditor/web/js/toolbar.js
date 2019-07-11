function initToolbar() {
	// Add event listeners
	document.getElementById('button-save').addEventListener('click', save);
	document.getElementById('input-file').addEventListener('change', load);
	document.getElementById('select-object-type').addEventListener('change', function () { Editor.selectedType = this.value; });
	document.title = Editor.filename;

	document.getElementById('button-create-object').addEventListener('click', function () { canvasDragObject(editorCreateObject(Editor.selectedType)); });
	document.getElementById('button-delete-object').addEventListener('click', function () { editorDeleteObject(Editor.selectedObject); });
	document.getElementById('button-duplicate-object').addEventListener('click', function () {
		if(Editor.selectedObject != null) {
			let object = Object.assign({}, Editor.selectedObject);
			object.position = '' + Editor.canvas.cursor[0] + ',' + Editor.canvas.cursor[1];
			canvasDragObject(object);
			Editor.objects.push(object);
		}
	});

	document.addEventListener('keydown', toolbarOnKeyDown);
}

function toolbarOnKeyDown(event) {
	if(!canvasHasFocus())
		return;

	switch(event.keyCode) {
		case KEY_N:
			document.getElementById('button-create-object').click();
			break;
	
		case KEY_DELETE:
			document.getElementById('button-delete-object').click();
			break;

		case KEY_D:
			document.getElementById('button-duplicate-object').click();
			break;
	}
}

// Saves the current level as a file
function save() {
	download(Editor.filename, JSON.stringify(Editor.objects));
}

// Loads 
function load(event) {
	// Clear list of objects
	Editor.objects = [];

	// Set filename & document title
	let file = event.target.files[0];
	Editor.filename = file.name;
	document.title = Editor.filename;

	let fileReader = new FileReader();
	fileReader.onload = function(e) {
		try {
			Editor.objects = JSON.parse(fileReader.result);
		}
		catch(e) {
			alert('Failed to parse file! (' + e + ')');
		}
	}
	fileReader.readAsText(file);
}

// Downloads data as file (thanks to people on the internet!)
function download(filename, data) {
	var element = document.createElement('a');
	element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(data));
	element.setAttribute('download', filename);
	element.style.display = 'none';
	document.body.appendChild(element);
	element.click();
	document.body.removeChild(element);
}
