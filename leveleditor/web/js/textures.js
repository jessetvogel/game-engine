var Textures = {
  currentSelection: {
    name: null,
    texture: null,
    texCoords: [ 0, 0, 32, 32 ]
  },
  textures: []
};

Textures.initialize = function () {
  // Set canvas and context
  Textures.canvas = $('#submenu-texture canvas').get(0);
  Textures.canvas.height = 0;

  // Input field in menu
  $('#input-texture').change(function () {
    $(this).removeClass('invalid');
    var textureName = $(this).val();
    Textures.setCurrent(textureName);
  });

  // Initially, set texture to none
  Textures.setCurrent(null);
};

Textures.load = function loadTexture(name, success, fail) {
  // If name is empty, return
  if(name == '') return;

  // If already loaded, stop
  if(Textures.get(name) != null) {
    if(success != undefined) success();
    return;
  }

  // Create new image and try to load it
  var image = new Image();
  image.onload = function () {
    Textures.textures[name] = this;
    if(success != undefined) success();
  }
  if(fail != undefined) image.onerror = fail;
  image.src = '/textures/' + name + '.png';
};

Textures.setCurrent = function (name) {
  // Set texture to none if null was given
  if(name == null) {
    $('#submenu-texture .menu-text').show().text('no texture selected');
    $('#submenu-texture .selected-texture-wrapper').hide();
    Textures.currentSelection.name = null;
    Textures.currentSelection.texture = null;
    Textures.currentSelection.texCoords[0] = 0;
    Textures.currentSelection.texCoords[1] = 0;
    Textures.currentSelection.texCoords[2] = Workspace.settings.grid.width;
    Textures.currentSelection.texCoords[3] = Workspace.settings.grid.height;
    return;
  }

  // Get texture by name
  var texture = Textures.get(name);

  // If it does not exist, try to load it
  if(texture == null) {
    Textures.load(name, function () {
      Textures.setCurrent(name);
    }, function () {
      Textures.setCurrent(null);
      $('#submenu-texture .menu-text').text('texture not found');
    });
    return;
  }

  // Set current selection texture
  Textures.currentSelection.name = name;
  Textures.currentSelection.texture = texture;
  $('#submenu-texture .menu-text').hide();
  $('#submenu-texture .selected-texture-wrapper').show();

  // Resize canvas
  Textures.canvas.width = texture.width;
  Textures.canvas.height = texture.height;
  Textures.drawCurrent();

  // Event listeners for selection
  Textures.canvas.addEventListener('mousedown', function (event) {
    switch(event.button) {
      // Start selection
      case MOUSE_LEFT:
        var rect = Textures.canvas.getBoundingClientRect();
        var x = event.clientX - rect.x;
        var y = event.clientY - rect.y;
        Textures.currentSelection.texCoords[0] = Math.floor(x / Workspace.settings.grid.width) * Workspace.settings.grid.width;
        Textures.currentSelection.texCoords[1] = Math.floor(y / Workspace.settings.grid.height) * Workspace.settings.grid.height;
        Textures.currentSelection.texCoords[2] = Workspace.settings.grid.width;
        Textures.currentSelection.texCoords[3] = Workspace.settings.grid.height;
        Textures.drawCurrent();
        break;
    }
  });

  Textures.canvas.addEventListener('mousemove', function (event) {
    if(!mousePressed(MOUSE_LEFT)) return;
    var rect = Textures.canvas.getBoundingClientRect();
    var x = event.clientX - rect.x;
    var y = event.clientY - rect.y;
    Textures.currentSelection.texCoords[2] =  Math.max(1, 1 + Math.floor((x - Textures.currentSelection.texCoords[0]) / Workspace.settings.grid.width )) * Workspace.settings.grid.width;
    Textures.currentSelection.texCoords[3] = Math.max(1, 1 + Math.floor((y - Textures.currentSelection.texCoords[1]) / Workspace.settings.grid.height)) * Workspace.settings.grid.height;
    Textures.drawCurrent();
  });
};

Textures.get = function (name) {
  // Return texture if it is loaded, otherwise return null
  var image = Textures.textures[name];
  if(image == undefined) return null;
  return image;
};

Textures.drawCurrent = function () {
  // Get context
  var ctx = Textures.canvas.getContext('2d');

  // Clear
  ctx.clearRect(0, 0, Textures.canvas.width, Textures.canvas.height);

  // Draw texture
  ctx.drawImage(Textures.currentSelection.texture, 0, 0);

  // Draw selection rectangle
  ctx.strokeStyle = 'red';
  var lw = ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.rect(
    Textures.currentSelection.texCoords[0] + lw / 2,
    Textures.currentSelection.texCoords[1] + lw / 2,
    Textures.currentSelection.texCoords[2] - lw,
    Textures.currentSelection.texCoords[3] - lw);
  ctx.stroke();
};
