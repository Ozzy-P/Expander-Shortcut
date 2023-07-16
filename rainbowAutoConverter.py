import logging
import random
import pyperclip
import keyboard

rainbow = False
# Commented colors are prone to filter.
hex = [
	"#ffe000", # yellow
	"#ff0000", # red
	#"#ffc2c2", -- pink
	"#ffbb1e", # orange
	"#5fff1e", # lime green
	#"#34a507", --green
	"#1effe0", # teal
	"#8df9ea", # light teal
	"#8dacf9", # light blue
	#"#1645b9", -- blue
	"#5b16b9", # purple
	"#b481fa", # lavendar
	"#fa81eb", #light pink
	"#cd4040", # brick red
]

hexStatic = {
    "p": 9,
    "r": 1,
    "l": 8,
    "g": 3,
    "b": 5
}

static = True
color = ""

def clearKey():
    keyboard.send('ctrl+a')
    keyboard.send('del')
    recorded = keyboard.record(until='tab')
    val = next(keyboard.get_typed_strings(recorded))
    x = val.split()
    return recorded, val, x

try:
    while True:
        keyboard.wait('/')
        recorded = keyboard.record(until='tab')
        val = next(keyboard.get_typed_strings(recorded))
        x = val.split()
        coloredMessage = ""
        reset = False

        if val == "rand":
            nonStatic = True
            recorded, val, x = clearKey()
        elif val == "rainbow":
            rainbow = not rainbow
            recorded, val, x = clearKey()
        elif hexStatic.get(val,None) != None:
            static = True
            color = hex[hexStatic[val]]
            recorded, val, x = clearKey()

        if rainbow:
            for y in x:
                hexVal = hex[random.randint(0, 9)]
                coloredMessage = coloredMessage + " (" + hexVal + "/" + y + ")"
        elif not static:
            hexVal = hex[random.randint(0, 9)]
            coloredMessage = coloredMessage + " (" + hexVal + "/" + val + ")"
        else:
            coloredMessage = coloredMessage + " (" + color + "/" + val + ")"
        pyperclip.copy(coloredMessage)
        keyboard.send('ctrl+a')
        keyboard.send('del')
        keyboard.send('ctrl+v')
except Exception as Argument:
    logging.exception("Error occurred while running chat color changer.")
    exitPy = input("")
