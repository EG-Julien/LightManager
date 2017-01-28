# LightManager
Led Brightness controller controlled over UNO serial

#Who to build ?

Connect your LED on pins {3, 5, 6, 9} (with a resistor to protect them).
Upload this sketch and enjoy !

#Use it

To change led control type c"id", then type a percentage.
Example :


`c1` => I choose the first LED (the one on the pin 3)


Now i can type a percentage to set the brightness :
  - 100% => FULL
  - 0%   => OFF
Exemple :

`88` => I set the first LED to 88% of it max brightness my UNO will say :

`LED :: 3 | LEVEL :: 88%`

