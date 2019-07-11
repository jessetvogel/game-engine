// Links an <input> to object[key]
function linkInput(input, object, key) {
	input.value = object[key];
	input.addEventListener('change', function () {
		if(typeof object[key] == 'string')
			object[key] = this.value;
		
		if(typeof object[key] == 'number')
			object[key] = parseFloat(this.value);
	});
}

// Converts color from hex format to rgb
function hexToRGB(hex) {       
    let r = hex.substring(1, 3),
        g = hex.substring(3, 5),
        b = hex.substring(5, 7);

    return [ parseInt(r, 16), parseInt(g, 16), parseInt(b, 16) ];
}

// Returns black or white depending on the background color
function textColor(hex) {
	let rgb = hexToRGB(hex);
	let threshold = 150;
	return (rgb[0] * 0.299 + rgb[1] * 0.587 + rgb[2] * 0.114 > threshold) ? '#263238' : '#ffffff';
}

// Parses the string, outputs a number or array of some sort
function parse(str) {
	if(/^\s*\d*\.?\d+\s*$/.test(str))
		return parseFloat(str);

	if(str.includes(','))
		return str.split(',').map((x) => parse(x));

	return undefined;
}
