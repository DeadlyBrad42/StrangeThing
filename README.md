# StrangeThing
### Another Arduino-powered Stranger Things wall
---

![Stranger Things light-up wall](https://raw.githubusercontent.com/DeadlyBrad42/StrangeThing/master/img/lightup01.gif)

_sorry for potato-cam_

### About
After years of only ever using my Arduino to make an LED blink, me and my roommate Clinton got the bright idea to make use my Arduino-blinking skills to build an awesome decoration for our Halloween party, inspired by similar Stranger Things walls we saw online.

### The Build
![before adding the light strand](https://raw.githubusercontent.com/DeadlyBrad42/StrangeThing/master/img/build01.jpg)

To build the wall's electronics, I used an Arduino Duemilanove, two strands of [WS2811 RGB LEDs](https://www.amazon.com/dp/B00MXW054Y/ref=as_li_ss_tl?_encoding=UTF8&me=&linkCode=ll1&tag=om03-20&linkId=76a7c1abdb34ac500a43f9974eba99ec), a [power supply](https://www.adafruit.com/product/1466), and some other [odds](https://www.adafruit.com/product/368) & [ends](https://www.adafruit.com/product/2880).

The board itself is made of styrofoam with a flowered wallpaper applied to it, and wooden framed edges.

I basically followed [this Adafruit wiring guide](https://learn.adafruit.com/12mm-led-pixels/wiring), although the lightstrand I used doesn't have the addtional data line. I then wired in the power connector ([this page of the same guide](https://learn.adafruit.com/12mm-led-pixels/power))

### Running the Code
Running the code on your own lightstrand is pretty straight-forward:

* Include the [NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel) by going to _Sketch > Include Library > Manage Libraries..._ and searching for **Adafruit NeoPixel**. I'm using **v1.0.6**.
* You'll want to change some of the parameters which are defined at the top of the file, particulary the _phrase & phrase count_, _the letter->LED mappings_, and `pixelsInStrip` and `controlPin` variables (depending on your setup)
* After that, just plug in your Arduino and compile & upload! If it doesn't work, you plugged something into the wrong place :(

### Issues & PRs
If you run into any issues you can submit them to this repository, though depending on how long we keep the wall up I'm not certain I'll be able to help much...

Feel free to fork this repository and submit PRs for any missing features or effects that you'd like to see!

### Additional References
* [Adafruit's guide to using the NeoPixel library on an LED strand](https://learn.adafruit.com/12mm-led-pixels/overview)

### License
[I mean, whatever really](https://github.com/DeadlyBrad42/StrangeThing/blob/master/LICENSE).
