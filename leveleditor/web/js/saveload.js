function initSaveLoad() {
	document.getElementById('save-button').addEventListener('click', save);
	document.getElementById('input-file').addEventListener('change', load);
	document.title = Editor.filename;
}

// Saves the current level as a file
function save() {
	download(Editor.filename, JSON.stringify(Editor.objects));
};

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
};
