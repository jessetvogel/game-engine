function initMenu() {
	// Toggle submenus when clicking on them
	for(let title of document.querySelectorAll('.submenu .title')) {
		title.addEventListener('click', function () {
			if(this.parentElement.classList.contains('closed'))
				this.parentElement.classList.remove('closed');
			else
				this.parentElement.classList.add('closed');
		});
	}

	// Settings
	linkInput(document.getElementById('input-grid-width'), Editor.canvas.grid, 'width');
	linkInput(document.getElementById('input-grid-height'), Editor.canvas.grid, 'height');
	linkInput(document.getElementById('input-canvas-background'), Editor.canvas, 'background');

	// Select no object
	menuSelectObject(null);
}

function menuSelectObject(object) {
	let content = document.querySelector('#submenu-object-properties .content');
	
	if(object == null) {
		content.innerHTML = '<div class="text">no object selected</div>';
		return;
	}

	// Type line
	content.innerHTML = '';
	let div = document.createElement('div');
	div.classList.add('parameter');
	div.innerHTML = '<div>type</div>';
	let select = document.createElement('select');
	for(let type in Editor.definitions.objects)
		select.innerHTML += '<option' + (type == object.type ? ' selected' : '') + '>' + type + '</option>';
	let divdiv = document.createElement('div');
	divdiv.append(select);
	div.append(divdiv);
	select.addEventListener('change', function () {
		let target = this.value;

		// Remove all parameters that should not be in object
		for(let key in object) {
			if(key === 'type' || key === 'id' || key === 'position')
				continue;

			if(!(key in Editor.definitions.objects[target].parameters))
				delete object[key];
		}

		// Add parameters that are not yet in object
		for(let param of Editor.definitions.objects[target].parameters) {
			if(param in object)
				continue;

			object[param] = '';
		}

		// Set default blanks
		editorSetDefaultBlanks(object);

		object.type = target;
		editorSelectObject(object);
	});
	content.append(div);

	// Id line
	content.append(createParameterInputLine(object, 'id'));

	// Parameter line for each object's parameter (except type & id)
	for(let key of Object.keys(object)) {
		if(key === 'type' || key === 'id')
			continue;

		content.append(createParameterInputLine(object, key));
	}

	// Open submenu if it is closed
	document.getElementById('submenu-object-properties').classList.remove('closed');
}  



function createParameterInputLine(object, key) {
	let line = document.createElement('div');
	line.classList.add('parameter');
	let name = document.createElement('div');
	name.innerText = key;
	line.append(name);
	let value = document.createElement('div');
	let input = document.createElement('input');
	linkInput(input, object, key);
	value.append(input);
	line.append(value);

	return line;
}
