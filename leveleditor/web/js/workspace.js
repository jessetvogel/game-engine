var Workspace = {
  settings: {
    grid: {
      width: 32.0,
      height: 32.0
    }
  },
  view: {
    x: 0.0,
    y: 0.0,
    zoom: 1.0
  },
  cursor: { x: 0, y: 0 },
  objects: [],
  draggingObject: null,
  draggingOffset: { x: 0, y: 0 },
  selectedObject: null,
  colors: {
    background: '#ffffff',
    grid: '#000000'
  }
};

Workspace.initialize = function () {
  // Initialize canvas
  var canvas = $('#workspace canvas');
  Workspace.canvas = canvas.get(0);
  Workspace.resize();
  Workspace.determineColors();

  // Event handler on resize
  $(window).resize(Workspace.resize);

  // Event listener for zooming and navigating
  Workspace.canvas.addEventListener('mousewheel', function(event) {
    if(keyPressed(KEY_ACTION)) {
      Workspace.view.zoom *= Math.exp(event.wheelDelta / 10000.0);
    }
    else {
      Workspace.view.x -= event.wheelDeltaX / (5.0 * Workspace.settings.grid.width  * Workspace.view.zoom);
      Workspace.view.y += event.wheelDeltaY / (5.0 * Workspace.settings.grid.height * Workspace.view.zoom);
    }

    // Prevent leaving the site (history)
    event.preventDefault();
  });

  // Event listener for keys actions
  document.addEventListener('keydown', function (event) {
    if(!Workspace.hasFocus()) return;

    switch(event.keyCode) {
      case KEY_N:
        var object = Workspace.createObject('tile');
        Properties.set(object, 'position', [ Workspace.cursor.x, Workspace.cursor.y ]);
        Workspace.dragObject(object);
        if(Properties.has(object, 'size')) {
          Workspace.draggingOffset.x = object.size[0] / 2;
          Workspace.draggingOffset.y = - object.size[1] / 2;
        }
        break;

      case KEY_DELETE:
        Workspace.deleteObject(Workspace.selectedObject);
        break;
    }
  });

  // Select object
  Workspace.canvas.addEventListener('mousedown', function (event) {
    for(var i = 0;i < Workspace.objects.length; ++i) {
      var object = Workspace.objects[i];
      if(Workspace.hoveringObject(object)) {
        Workspace.selectObject(object);
        return;
      }
    }
    Workspace.selectObject(null);
  });

  // Drop object
  Workspace.canvas.addEventListener('mouseup', function (event) {
    Workspace.dragObject(null);
  });

  // Drag object when mouse moves
  Workspace.canvas.addEventListener('mousemove', function (event) {
    if(mousePressed(MOUSE_LEFT) && Workspace.selectedObject != null && Workspace.draggingObject != Workspace.selectedObject)
      Workspace.dragObject(Workspace.selectedObject);
  });

  // Disable right click menu
  Workspace.canvas.addEventListener('contextmenu', function (event) { event.preventDefault(); });

  // Update and render functions
  Workspace.dt = 1.0 / 60;
  setInterval(function () {
    // Update
    Workspace.update();

    // Render
    Workspace.draw();
  }, Workspace.dt * 1000);
}

Workspace.resize = function () {
  // Update size of workspace canvas
  var canvas = $('#workspace canvas');
  Workspace.canvas.width = canvas.width();
  Workspace.canvas.height = canvas.height();
  Workspace.context = Workspace.canvas.getContext('2d');
  Workspace.context.imageSmoothingEnabled = false;
}

Workspace.update = function () {
  // Update cursor
  var rect = Workspace.canvas.getBoundingClientRect();
  var position = { x: mouseX() - rect.x, y: mouseY() - rect.y };
  Workspace.transformPositionInverse(position);
  Workspace.cursor.x = position.x;
  Workspace.cursor.y = position.y;

  // Update view
  Workspace.updateView();

  // Update selected object
  if(Workspace.draggingObject != null) {
    Workspace.draggingObject.position[0] = Workspace.cursor.x - Workspace.draggingOffset.x;
    Workspace.draggingObject.position[1] = Workspace.cursor.y - Workspace.draggingOffset.y;
    if(!keyPressed(KEY_ALT)) {
      Workspace.draggingObject.position[0] = Math.floor(Workspace.draggingObject.position[0] + 0.5);
      Workspace.draggingObject.position[1] = Math.floor(Workspace.draggingObject.position[1] - 0.5) + 1;
    }
  }
};

Workspace.updateView = function () {
  // Camera movement
  if(Workspace.hasFocus()) {
    if(keyPressed(KEY_UP))    Workspace.view.y += 10.0 / Workspace.view.zoom * Workspace.dt;
    if(keyPressed(KEY_DOWN))  Workspace.view.y -= 10.0 / Workspace.view.zoom * Workspace.dt;
    if(keyPressed(KEY_LEFT))  Workspace.view.x -= 10.0 / Workspace.view.zoom * Workspace.dt;
    if(keyPressed(KEY_RIGHT)) Workspace.view.x += 10.0 / Workspace.view.zoom * Workspace.dt;
  }
};

Workspace.draw = function () {
  // Clear screen
  Workspace.determineColors();
  Workspace.context.fillStyle = Workspace.colors.background;
  Workspace.context.fillRect(0, 0, Workspace.canvas.width, Workspace.canvas.height);

  // Draw grid
  Workspace.drawGrid();

  // Draw objects
  Workspace.drawObjects();

  // Draw selection border
  Workspace.drawSelectionBorder();

  // Draw cursor coordinates
  Workspace.drawCursorCoordinates();
};

Workspace.drawGrid = function () {
  // Get context
  var ctx = Workspace.context;

  // Grid style
  ctx.strokeStyle = Workspace.colors.grid;
  ctx.lineWidth = 1;

  // Determine origin
  var origin = { x: 0, y: 0 };
  Workspace.transformPosition(origin);

  // Draw vertical lines
  var dx = Workspace.settings.grid.width * Workspace.view.zoom;
  while(dx < 16) dx *= 2;
  for(var x = origin.x % dx;x < Workspace.canvas.width;x += dx) {
    ctx.beginPath();
    ctx.moveTo(x - 0.5, 0);
    ctx.lineTo(x - 0.5, Workspace.canvas.height);
    ctx.stroke();
  }

  // Draw horizontal lines
  var dy = Workspace.settings.grid.height * Workspace.view.zoom;
  while(dy < 16) dy *= 2;
  for(var y = origin.y % dy;y < Workspace.canvas.height;y += dy) {
    ctx.beginPath();
    ctx.moveTo(0, y + 0.5);
    ctx.lineTo(Workspace.canvas.width, y + 0.5);
    ctx.stroke();
  }
};

Workspace.drawObjects = function () {
  // Draw objects
  for(var i = 0;i < Workspace.objects.length; ++i)
    Workspace.drawObject(Workspace.objects[i]);
};

Workspace.drawObject = function (object) {
  // Requires position
  if(!Properties.has(object, 'position')) return;

  // Compute coordinates
  var position = { x: object.position[0], y: object.position[1] };
  Workspace.transformPosition(position);

  // If no size, simply draw a circle
  if(!Properties.has(object, 'size')) {
    Workspace.context.beginPath();
    Workspace.context.arc(position.x, position.y, 8, 0, 2 * Math.PI, false);
    Workspace.context.fillStyle = 'blue';
    Workspace.context.globalAlpha = (object == Workspace.draggingObject) ? 0.5 : 1.0;
    Workspace.context.fill();
    Workspace.context.globalAlpha = 1.0;
    return;
  }

  // Compute size
  var size = { width: object.size[0], height: object.size[1] };
  Workspace.transformSize(size);

  // If has no texture, draw a blue rectangle
  var texture;
  if(!Properties.has(object, 'texture') || !Properties.has(object, 'texCoords') || (texture = Textures.get(object.texture)) == null) {
    Workspace.context.globalAlpha = (object == Workspace.draggingObject) ? 0.5 : 1.0;
    Workspace.context.fillStyle = 'blue';
    Workspace.context.fillRect(position.x, position.y, size.width, size.height);
    Workspace.context.globalAlpha = 1.0;
    return;
  }

  // Draw image
  Workspace.context.globalAlpha = (object == Workspace.draggingObject) ? 0.5 : 1.0;
  Workspace.context.drawImage(
    texture,
    object.texCoords[0],
    object.texCoords[1],
    object.texCoords[2],
    object.texCoords[3],
    position.x,
    position.y,
    size.width,
    size.height
  );
  Workspace.context.globalAlpha = 1.0;
};

Workspace.drawSelectionBorder = function () {
  // Draw selection border
  if(Workspace.selectedObject != null) {
    // Get selected object
    var object = Workspace.selectedObject;

    // Requires position
    if(!Properties.has(object, 'position')) return;

    // Border style
    Workspace.context.strokeStyle = 'red';
    Workspace.context.lineWidth = 3;

    // Compute coordinates
    var position = { x: object.position[0], y: object.position[1] };
    Workspace.transformPosition(position);

    // If no size, simply draw a circle
    if(!Properties.has(object, 'size')) {
      Workspace.context.beginPath();
      Workspace.context.arc(position.x, position.y, 16, 0, 2 * Math.PI, false);
      Workspace.context.stroke();
      return;
    }

    // Compute size
    var size = { width: object.size[0], height: object.size[1] };
    Workspace.transformSize(size);

    // Draw border
    Workspace.context.strokeStyle = 'red';
    Workspace.context.lineWidth = 3;
    Workspace.context.beginPath();
    Workspace.context.rect(position.x, position.y, size.width, size.height);
    Workspace.context.stroke();
  }
};

Workspace.drawCursorCoordinates = function () {
  // Only draw if hovering canvas
  if(!Workspace.hoveringCanvas()) return;

  // Get cursor coordinates
  var x = Workspace.cursor.x;
  var y = Workspace.cursor.y;

  // Possibly round coordinates
  if(!keyPressed(KEY_ALT)) {
    x = Math.floor(x);
    y = Math.floor(y) + 1;
  }
  else {
    x = Math.floor(x * 100) / 100;
    y = Math.floor(y * 100) / 100;
  }

  // Transform coordinates
  var position = { x: x, y: y };
  Workspace.transformPosition(position);

  // Draw coordinates
  var ctx = Workspace.context;
  ctx.font = '10px museosans';
  ctx.textAlign = 'center';
  ctx.textBaseline = 'middle';
  var str = '(' + x + ', ' + y + ')';
  var w = ctx.measureText(str).width + 8;
  ctx.fillStyle = 'black';
  ctx.globalAlpha = 0.5;
  ctx.fillRect(position.x - w / 2, position.y - 12, w, 24);
  ctx.globalAlpha = 1.0;
  ctx.fillStyle = 'white';
  ctx.fillText(str, position.x, position.y);
};

// Transformation functions
Workspace.transformPosition = function (position) {
  position.x = Workspace.canvas.width / 2 + (position.x - Workspace.view.x) * Workspace.settings.grid.width * Workspace.view.zoom;
  position.y = Workspace.canvas.height / 2 - (position.y - Workspace.view.y) * Workspace.settings.grid.height * Workspace.view.zoom;
}

Workspace.transformPositionInverse = function (position) {
  position.x = (position.x - Workspace.canvas.width / 2) / (Workspace.settings.grid.width * Workspace.view.zoom) + Workspace.view.x;
  position.y = - (position.y - Workspace.canvas.height / 2) / (Workspace.settings.grid.height * Workspace.view.zoom) + Workspace.view.y;
}

Workspace.transformSize = function (size) {
  size.width = size.width * Workspace.settings.grid.width * Workspace.view.zoom;
  size.height = size.height * Workspace.settings.grid.height * Workspace.view.zoom;
}

Workspace.transformSizeInverse = function (size) {
  size.width = size.width / (Workspace.settings.grid.width * Workspace.view.zoom);
  size.height = size.height / (Workspace.settings.grid.height * Workspace.view.zoom);
}

Workspace.createObject = function (type) {
  // Get selection
  var selection = Textures.currentSelection;

  // Construct object
  var object = { type: type };

  // If there is a texture selection, set some more properties
  if(selection.texture != null) {
    Properties.set(object, 'size', [ selection.texCoords[2] / Workspace.settings.grid.width, selection.texCoords[3] / Workspace.settings.grid.height ]);
    Properties.set(object, 'texture', selection.name);
    Properties.set(object, 'texCoords', selection.texCoords.slice(0));
  };

  // Add object to list
  Workspace.objects.push(object);

  // Return object
  return object;
};

Workspace.hoveringObject = function (object) {
  // Requires position
  if(!Properties.has(object, 'position')) return false;

  // Get mouse coordinates
  var x = Workspace.cursor.x;
  var y = Workspace.cursor.y;

  // If no size, return true if mouse is within 8 pixels
  if(!Properties.has(object, 'size')) {
    var distance = { width: x - object.position[0], height: y - object.position[1] };
    Workspace.transformSize(distance);
    return Math.sqrt(distance.width * distance.width + distance.height * distance.height) <= 8.0;
  }

  // Check if the mouse is within the borders of the object
  return x > object.position[0] && y > object.position[1] - object.size[1] && x < object.position[0] + object.size[0] && y < object.position[1];
};

Workspace.hoveringCanvas = function () {
  var x = mouseX();
  var y = mouseY();
  var rect = Workspace.canvas.getBoundingClientRect();
  return x > rect.left && x < rect.right && y > rect.top && y < rect.bottom;
};

Workspace.selectObject = function (object) {
  // Set selected object
  Workspace.selectedObject = object;

  // Select it in the menu
  Menu.setSelectedObject(object);
};

Workspace.dragObject = function (object) {
  // If null, reset dragging object
  if(object == null) {
    Workspace.draggingObject = null;
    return;
  }

  // Requires position
  if(!Properties.has(object, 'position')) return;

  // Set dragging object
  Workspace.draggingObject = object;

  // Set dragging offset
  Workspace.draggingOffset.x = Workspace.cursor.x - object.position[0];
  Workspace.draggingOffset.y = Workspace.cursor.y - object.position[1];
};

Workspace.deleteObject = function (object) {
  // Remove object from array (TODO: can we do this without making a new array?)
  Workspace.objects = Workspace.objects.filter(function (o) { return o !== object; });

  // If it was the selected or dragging object, that to null
  if(object == Workspace.selectedObject) Workspace.selectObject(null);
  if(object == Workspace.draggingObject) Workspace.dragObject(null);
};

Workspace.hasFocus = function () {
  return !document.activeElement || (document.activeElement.tagName.toLowerCase() != 'input');
}

Workspace.determineColors = function () {
  // Get computed colors from body style
  var style = getComputedStyle(document.body);
  Workspace.colors.background = style.getPropertyValue('--workspace-background');
  Workspace.colors.grid = style.getPropertyValue('--grid-color');
}
