# Demonic-Buttons
This project is designed for use with an Arduino Mega, since the amount of hookups required far exceeded the amount of pins available on an Arduino Uno.
In this project, players must press nine buttons in the correct order, and each button turns itself "off" once pressed. In other words, the backlight LED in the button deactivates.
The buttons used are arcade buttons from Adafruit, and the interior of the button cap was painted to show a symbol from the oblivion font, which ends up translating to GIVE UP OAF, for no other reason than it's funny.
Once the buttons are pressed in order, an led strip lights, filling the room with a red glow, and a maglock disengages, revealing more puzzle from a drawer nearby.
One button can be held down during this process to reset the entire puzzle, but we most often just power cycle the arduino anyways.
