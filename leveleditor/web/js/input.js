function initInput() {
  // Add event listeners
  document.addEventListener('keydown',   function (e) { Editor.input.keyState[e.keyCode] = true;   });
  document.addEventListener('keyup',     function (e) { Editor.input.keyState[e.keyCode] = false;  });
  document.addEventListener('mousedown', function (e) { Editor.input.mouseState[e.button] = true;  });
  document.addEventListener('mouseup',   function (e) { Editor.input.mouseState[e.button] = false; });
  document.addEventListener('mousemove', function (e) { Editor.input.mousePosition = [ e.clientX, e.clientY ]; });
}

function inputKeyDown(keyCode) {
  return !!Editor.input.keyState[keyCode];
}

function inputMouseDown(button) {
  return !!Editor.input.mouseState[button];
}

function inputMouse() {
  return Editor.input.mousePosition;
}

const KEY_UP = 38;
const KEY_DOWN = 40;
const KEY_LEFT = 37;
const KEY_RIGHT = 39;

const KEY_BACKSPACE = 8;
const KEY_CONTROL = 17;
const KEY_ALT = 18;
const KEY_DELETE = 46;
const KEY_ACTION = 91;

const KEY_A = 65;
const KEY_B = 66;
const KEY_C = 67;
const KEY_D = 68;
const KEY_E = 69;
const KEY_F = 70;
const KEY_G = 71;
const KEY_H = 72;
const KEY_I = 73;
const KEY_J = 74;
const KEY_K = 75;
const KEY_L = 76;
const KEY_M = 77;
const KEY_N = 78;
const KEY_O = 79;
const KEY_P = 80;
const KEY_Q = 81;
const KEY_R = 82;
const KEY_S = 83;
const KEY_T = 84;
const KEY_U = 85;
const KEY_V = 86;
const KEY_W = 87;
const KEY_X = 88;
const KEY_Y = 89;
const KEY_Z = 90;

const MOUSE_LEFT = 0;
const MOUSE_MIDDLE = 1;
const MOUSE_RIGHT = 2;
