function init() {
  // Initialize some stuff
  initMenu();
  initCanvas();
  initSaveLoad();
  initInput();

  // Fetch data
  fetch("/data/definitions/objects.json").then((result) =>  { result.json().then((data) => { Editor.definitions.objects = data; }); });
  fetch("/data/definitions/textures.json").then((result) => { result.json().then((data) => { Editor.definitions.textures = data; }); });
  fetch("/data/definitions/sprites.json").then((result) =>  { result.json().then((data) => { Editor.definitions.sprites = data; }); });

  // Prevent accidental page unloading
  // window.onbeforeunload = function () {
  //   return 'Are you sure you want to leave?';
  // };
};
