$(document).ready(function () {
  // Initialize menu
  Menu.initialize();

  // Initialize workspace
  Workspace.initialize();

  // Initialize textures
  // Textures.initialize();

  // Initialize settings
  Settings.initialize();

  initSaveLoad();

  // Prevent accidental page unloading
  // window.onbeforeunload = function () {
  //   return 'Are you sure you want to leave?';
  // };

});


var Level = { "objects": [] };