# Paths
output_file = "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/definitions.def"
audio_prefix = "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/audio/"
fonts_prefix = "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/fonts/"
textures_prefix = "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/textures/"
shaders_prefix = "/Users/jessetvogel/Projects/game-engine/c++/src/example-game/shaders/"

# Util functions
import json 
def loadJSON(filename):
	with open(filename, "r") as file:
		data = json.load(file)
		return data

# Load data
audios = loadJSON("audios.json")
fonts = loadJSON("fonts.json")
textures = loadJSON("textures.json")
sprites = loadJSON("sprites.json")
objects = loadJSON("objects.json")

# Write definition instructions
definitions = ""
for name, path in audios.items():
	definitions += "c->defineAudio(\"{}\", \"{}\");\n".format(name, audio_prefix + path)

for name, path in fonts.items():
	definitions += "c->defineFont(\"{}\", \"{}\");\n".format(name, fonts_prefix + path)

for name, path in textures.items():
	definitions += "c->defineTexture(\"{}\", \"{}\");\n".format(name, textures_prefix + path)

for name, sprite in sprites.items():
	if "texture" not in sprite:
		print("Sprite '{}' has undefined texture".format(name))
		continue

	if sprite["texture"] not in textures:
		print("Sprite '{}' uses undefined texture '{}'".format(name, texture))
		continue

	if "frames" not in sprite:
		sprite["frames"] = 1

	if "frame" not in sprite or len(sprite["frame"]) != 4:
		print("Sprite '{}' has undefined (or ill-defined) frame".format(name))
		continue

	x, y, w, h = sprite["frame"][0:4]

	definitions += "c->defineSprite(\"{}\", {{ \"{}\", {{ {}, {}, {}, {} }}, {} }});\n".format(name, sprite["texture"], x, y, w, h, sprite["frames"])

for name, _object in objects.items():
	if "class" not in _object:
		print("Object '{}' as undefined class".format(name))
		continue

	definitions += "c->defineObject(\"{}\", [](ObjectData& data) -> IObject* {{ return new {}(data); }});\n".format(name, _object["class"])

# Write to file
output = open(output_file, "w+")
output.write(definitions)
output.close()
