function initSaveLoad() {
	$('#save-button').click(save);
	$('#input-file').change(load);
}

// Saves the current level as a file
function save() {
	download('untitled.json', JSON.stringify(Level.objects));
};

// Loads 
function load(event) {
	// Clear list of objects
	Level.objects = [];

	// Get filename
	var file = event.target.files[0];
	// currentFileName = file.name;
	// document.title = currentFileName;

	var fileReader = new FileReader();
	fileReader.onload = function(e) {
		try {
			Level.objects = JSON.parse(fileReader.result);
		}
		catch(e) {
			alert("Failed to parse file! (" + e + ")");
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
