# I2CButtons
The included class and Arduino sketch provide a way to interface up to 8 buttons to a RaspberryPI over I2C

While you could instantiate this on the stack it is recommended to use a heap allocation to catch any exceptions and checking for nullptr before updating the button states

The following code examples assume that this is a pointer called `buttons` all code is namespaced in `CygnixProto`

### Updating the internal state
```c++
buttons->UpdateState();
```
This should be called once per "frame" or loop of your application. It will make an I2C read to the Arduino which by default is configured to address 0x0A

Once it reads the data it will process the result and update the button latches

### Button Inputs
```c++
buttons->isButtonDown(Button::A);
```
isButtonDown is readable every time a button is pressed. This state is triggered once per button press. If the button is still down when the next UpdateState() is called this will then return false. Essentially this can be used as a debounced input.

```c++
buttons->isButtonHeld(Button::A);
```
isButtonHeld is true for the duration a button is held, it will resolve true from the moment isButtonDown resolves true and will hold this state until the button is released

```c++
buttons->isButtonUp(Button::A);
```
isButtonUp will be true once the button is released, like isButtonDown however it is only true until the next time UpdateState() is called.



For a more detailed example of how this code is intended to be used, please see `example.cpp`

### Dependencies for building the example
> cmake
> make
> i2c-tools
> i2c-tools-dev

### Building the Example
```bash
mkdir build
cd build
cmake ../
make
```


### Using this for yourself
Edit the sketch `i2c_buttons.ino` to your requirements and upload it to an Arduino. Connect the I2C pins on the Arduino and the Pi together. Do not connect +5v if you power your Arduino externally, however you will require a common ground connection. That said, running an Arduino Uno from the +5v of a Pi4 is possible.

Include I2CButtons.h/cpp in your project, add `#include "I2CButtons.h"` in your program and off you go.

You will require i2c-tools-dev as a dependency or whatever package provides `#include <i2c/smbus.h>` on your distribution.

Additionally, when building your executable please ensure that you link against i2c with `-li2c` if using GCC or Clang

This code is licensed under Apache2 and if you use this in your project I ask that you keep the copyright notice intact in the headers.

### Useful links
- https://pinout.xyz/pinout/i2c#
- https://www.kernel.org/doc/Documentation/i2c/dev-interface
