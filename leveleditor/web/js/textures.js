function textureGet(name) {
	// If texture already loaded, return it
	if(name in Editor.textures)
		return Editor.textures[name];

	Editor.textures[name] = null; // So that this function will only be called once!

	// Load the texture from definition
	if(!(name in Editor.definitions.textures))
		return null;

	let image = new Image();
	image.onload = function () {
		Editor.textures[name] = this;
	}
	image.onerror = () => alert('Failed to load texture \'' + name + '\'');
	image.src = '/data/textures/' + Editor.definitions.textures[name];	
}
