# StrangeThing
### Another Arduino-powered Stranger Things wall
---

![Stranger Things light-up wall, spelling "v original"](https://raw.githubusercontent.com/DeadlyBrad42/StrangeThing/master/assets/img/lightup02.gif)

## About
After years of only ever using my Arduino to make an LED blink, me and my roommate Clinton got the bright idea to make use my Arduino-blinking skills to build an awesome decoration for our Halloween party, inspired by similar Stranger Things walls we saw online.

## The (Physical) Build
![before adding the light strand](https://raw.githubusercontent.com/DeadlyBrad42/StrangeThing/master/assets/img/build01.jpg)

To build the wall's electronics, I used an Arduino Duemilanove, two strands of [WS2811 RGB LEDs](https://www.amazon.com/dp/B00MXW054Y/ref=as_li_ss_tl?_encoding=UTF8&me=&linkCode=ll1&tag=om03-20&linkId=76a7c1abdb34ac500a43f9974eba99ec), a [power supply](https://www.adafruit.com/product/1466), and some other [odds](https://www.adafruit.com/product/368) & [ends](https://www.adafruit.com/product/2880).

The board itself is made of styrofoam with a flowered wallpaper applied to it, and wooden framed edges.

I basically followed [this Adafruit wiring guide](https://learn.adafruit.com/12mm-led-pixels/wiring), although the lightstrand I used doesn't have the addtional data line. I then wired in the power connector ([this page of the same guide](https://learn.adafruit.com/12mm-led-pixels/power))

![Wired in power & data lines using a JST connector](https://raw.githubusercontent.com/DeadlyBrad42/StrangeThing/master/assets/img/wiring01.jpg)

## The (Software) Build
Running the code on your own lightstrand is fairly straight-forward. Depending on your needs, you can set up the project using either the **Arduino IDE**, or **Visual Studio Code** with the _Arduino_ extension.

### For the Arduino IDE
* Make sure you have the latest&greatest version of the [Arduino IDE](https://www.arduino.cc/en/Main/Software) installed
* Include the [NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel) by going to _Sketch > Include Library > Manage Libraries..._ and searching for **Adafruit NeoPixel**. I'm using **v1.0.6**.
* You'll probably want to set your board & COM ports to the correct values... after that, just plug in your Arduino, and compile & upload!

### For Visual Studio Code
* Make sure you have the latest&greatest version of the [Arduino IDE](https://www.arduino.cc/en/Main/Software) installed
* You'll also need [Visual Studio Code](https://code.visualstudio.com/) & the [Arduino extension](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino) installed.
* You'll want to double-check the paths mentioned in _.vscode/c_cpp_properties.json_ and ensure they point to the proper folders on your machine. After that, you should be able to plug in your Arduino, press `Ctrl+Shift+P`, and type `Arduino: Upload`!

## Modifying the Code
You'll want to make several changes to the code before using it to run your own lightstrip, which you can do by editing the parameters at the top of the file.

You can update the `phraseCount` and the `phrase` list to add your own sayings. In my testing, my _Arduino Duemilanove_ seems to hit a memory limit with much more than ~30 phrases.

You'll also probably want to check that the `#define led` statements, `pixelsInStrip`, and `controlPin` variables match your setup. The `#define led` statements in particular need to be updated in order for the code to know which letter to light up.

In addition, the code was written to make it simple to program your own effects. I've included two example functions (`effects_curated()` && `effects_shuffle()`), but you can also write your own & directly call the `fx_` functions I've created, or use them as examples to write your own.

## Issues & PRs
If you run into any issues you can submit them to this repository, though depending on how long we keep the wall up I'm not certain I'll be able to help much...

Feel free to fork this repository and submit PRs for any missing features or effects that you'd like to see!

## Additional References
* [Adafruit's guide to using the NeoPixel library on an LED strand](https://learn.adafruit.com/12mm-led-pixels/overview)

## License
[lol sure](https://github.com/DeadlyBrad42/StrangeThing/blob/master/LICENSE)

## More Photos
Here's what it looks like in the dark, right before the Halloween party when you're slightly buzzed but still think you could be steady enough to take a video:
![](https://raw.githubusercontent.com/DeadlyBrad42/StrangeThing/master/assets/img/lightup01.gif)
