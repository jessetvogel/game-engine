var Properties = {
  list: [
    { name: 'type',       description: 'Type',            type: 's',   amount: 1,   default: 'tile' },
    { name: 'position',   description: 'Position',        type: 'f',   amount: 2,   default: [ 0, 0 ] },
    { name: 'size',       description: 'Size',            type: 'f',   amount: 2,   default: [ 1, 1 ] },
    { name: 'texture',    description: 'Texture',         type: 's',   amount: 1,   default: ''  },
    { name: 'texCoords',  description: 'Tex. Coords.',    type: 'i',   amount: 4,   default: [ 0, 0, 32, 32] },
    { name: 'angle',      description: 'Angle',           type: 'f',   amount: 1,   default: 0 }
  ]
};

Properties.set = function (object, name, value) {
  // Make sure this property exists
  var property = Properties.get(name);
  if(property == null) {
    console.log('Property \'' + name + '\' does not exist');
    return false;
  }

  // If value is undefined, set default value
  if(value == undefined) {
      if(property.default instanceof Array)
        object[property.name] = property.default.slice(0);
      else
        object[property.name] = property.default;
      return true;
  }

  // Make sure value has right format
  var values = ('' + value).split(',');
  if(values.length != property.amount) {
    console.log('Property \'' + property.name + '\' has ' + property.amount + ' values, only ' + values.length + ' given');
    return false;
  }

  // Convert to correct type
  var array = new Array(property.amount);
  for(var i = 0;i < property.amount; ++i) {
    switch(property.type) {
      case 's': array[i] = values[i]; break;
      case 'i': array[i] = parseInt(values[i]); break;
      case 'f': array[i] = parseFloat(values[i]); break;
    }

    // Make sure numbers are entered correctly
    if(array[i] != array[i]) {
      console.log('Invalid value \'' + values[i] + '\' given');
      return false;
    }
  }

  // Set object property
  if(property.amount == 1)
    object[property.name] = array[0];
  else
    object[property.name] = array;
};

Properties.get = function (name) {
  for(var i = 0;i < Properties.list.length; ++i)
    if(Properties.list[i].name == name || Properties.list[i].description == name) return Properties.list[i];
  return null;
};

Properties.has = function (object, name) {
  return object.hasOwnProperty(name);
};

Properties.unset = function (object, name) {
  if(Properties.has(object, name) && name != 'type')
    delete object[name];
};
