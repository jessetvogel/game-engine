var Settings = {};

Settings.initialize = function () {
  // Link input fields
  $('#input-grid-width').change(function () {
    var width = parseInt($(this).val());
    if(width != width || width <= 0) return;
    Workspace.settings.grid.width = width;
  }).val(Workspace.settings.grid.width);

  $('#input-grid-height').change(function () {
    var height = parseInt($(this).val());
    if(height != height || height <= 0) return;
    Workspace.settings.grid.height = height;
  }).val(Workspace.settings.grid.height);
};
