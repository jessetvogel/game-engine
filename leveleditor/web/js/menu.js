var Menu = {};

Menu.initialize = function () {
  // Initially, close all submenus
  // $('.submenu').addClass('closed');

  // Slide toggle submenus when clicking on them
  $('.submenu-title').click(function () { $(this).parent().toggleClass('closed'); });

  // Select no object
  Menu.setSelectedObject(null);
};

Menu.setSelectedObject = function (object) {
  // In case object = null
  var submenuContent = $('#submenu-object-properties .submenu-content').html('');
  if(object == null) {
    submenuContent.html('<div class="menu-text">no object selected</div>');
    return;
  }

  // Go through all properties that the object has
  for(var i = 0;i < Properties.list.length; ++i) {
    var property = Properties.list[i];
    if(!Properties.has(object, property.name)) continue;

    // Create an input
    var input = $('<input>').val('' + object[property.name]);
    var line = $('<div>')
      .addClass('input-property-value-wrapper')
      .append($('<div>').addClass('property').text(property.description))
      .append($('<div>').addClass('value').append(input));
    (function (object, property) {
      input.change(function () {
        Properties.set(object, property.name, $(this).val());
      });
    })(object, property);

    // Append line to menu
    submenuContent.append(line);
  }

  // Button for new properties
  var addButton = $('<div>').addClass('button button-green').text('+');
  var minusButton = $('<div>').addClass('button button-red').text('-');
  (function (object) {
    addButton.click(function () {
      var property = $('#input-property-name').val();
      Properties.set(object, property);
      Menu.setSelectedObject(object);
    });
    minusButton.click(function () {
      var property = $('#input-property-name').val();
      Properties.unset(object, property);
      Menu.setSelectedObject(object);
    });
  })(object);
  var line = $('<div>')
    .addClass('input-property-value-wrapper')
    .append($('<div>').addClass('property').append($('<input>').attr('id', 'input-property-name').attr('placeholder', 'property')))
    .append($('<div>').addClass('value').append($('<div>').addClass('button-row').append(addButton).append(minusButton)));
  submenuContent.append(line);

  // If submenu closed, open it
  var submenuProperties = $('#submenu-object-properties');
  if(submenuProperties.hasClass('closed'))
    submenuProperties.find('.submenu-title').click();
};
