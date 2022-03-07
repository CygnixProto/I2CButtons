/*
 * Copyright 2022  Cygnix Proto
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
extern "C" {
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
}
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "I2CButtons.h"

#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_C (1 << 2)
#define BUTTON_D (1 << 3)
#define BUTTON_E (1 << 4)
#define BUTTON_F (1 << 5)
#define BUTTON_G (1 << 6)
#define BUTTON_H (1 << 7)

CygnixProto::I2CButtons::I2CButtons() {

    i2cFile = open("/dev/i2c-1", O_RDWR);
    if(i2cFile < 0) {
        throw std::runtime_error("Error Opening I2C Device");
    }

    int addr = 0x0A;
    if(ioctl(i2cFile, I2C_SLAVE, addr) < 0) {
        throw std::runtime_error("Error calling ioctl()");
    }
}

CygnixProto::I2CButtons::~I2CButtons() {
    close(i2cFile);
}

void CygnixProto::I2CButtons::updateState() {
    auto runStates = [](auto& states) {
        for (auto& s : states) {
            s.Latch.down = false;
            s.Latch.up   = false;

            if (s.bNew != s.bOld) {
                if (s.bNew) {
                    s.Latch.down = !s.Latch.held;
                    s.Latch.held = true;
                } else {
                    s.Latch.up   = true;
                    s.Latch.held = false;
                }
            }
            s.bOld = s.bNew;
        }
    };

    uint8_t res;
    res = i2c_smbus_read_byte(i2cFile);

    changeButtonState(Button::A, res & BUTTON_A);
    changeButtonState(Button::B, res & BUTTON_B);
    changeButtonState(Button::C, res & BUTTON_C);
    changeButtonState(Button::D, res & BUTTON_D);
    changeButtonState(Button::E, res & BUTTON_E);
    changeButtonState(Button::F, res & BUTTON_F);
    changeButtonState(Button::G, res & BUTTON_G);
    changeButtonState(Button::H, res & BUTTON_H);

    runStates(buttonState);
}

bool CygnixProto::I2CButtons::isButtonDown(Button b) {
    if (b < buttonState.size()) {
        return buttonState.at(b).Latch.down;
    }
    return false;
}

bool CygnixProto::I2CButtons::isButtonUp(Button b) {
    if (b < buttonState.size()) {
        return buttonState.at(b).Latch.up;
    }
    return false;
}

bool CygnixProto::I2CButtons::isButtonHeld(Button b) {
    if (b < buttonState.size()) {
        return buttonState.at(b).Latch.held;
    }
    return false;
}

void CygnixProto::I2CButtons::changeButtonState(uint8_t button, bool state) {
    if(button < buttonState.size()) {
        buttonState.at(button).bNew = state;
    }
}
