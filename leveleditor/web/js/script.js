function init() {
	// Initialize some stuff
	initMenu();
	initCanvas();
	initToolbar();
	initInput();

	// Fetch data
	fetch('/data/definitions/objects.json').then((result) =>  { result.json().then((data) => {
			Editor.definitions.objects = data;
			let types = Object.keys(data);
			Editor.selectedType = types[0];

			let select = document.getElementById('select-object-type');
			for(let type of types)
				select.innerHTML += '<option' + (type == Editor.selectedType ? ' selected' : '') + '>' + type + '</option>';
		});
	});
	fetch('/data/definitions/textures.json').then((result) => { result.json().then((data) => { Editor.definitions.textures = data; }); });
	fetch('/data/definitions/sprites.json').then((result) =>  { result.json().then((data) => { Editor.definitions.sprites = data; }); });

	editorSelectObject(null);

	// // Prevent accidental page unloading
	// window.onbeforeunload = function () {
	// 	return 'Are you sure you want to leave?';
	// };
}
