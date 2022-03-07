
#ifndef I2CTESTING_I2CBUTTONS_H
#define I2CTESTING_I2CBUTTONS_H
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

#include <array>

namespace CygnixProto {
    enum Button {
        A, B, C, D, E, F, G, H
    };

    class I2CButtons {

    public:
        I2CButtons();
        ~I2CButtons();
        void updateState();
        bool isButtonDown(Button b);
        bool isButtonUp(Button b);
        bool isButtonHeld(Button b);

    private:
        int i2cFile;

        struct HButton {
            bool down = false;
            bool up = false;
            bool held = false;
        };

        struct StateLatch {
            bool bOld{};
            bool bNew{};
            HButton Latch;
        };
        std::array<StateLatch, 8> buttonState{{{false, false, {false}}}};

        void changeButtonState(uint8_t button, bool state);
    };
}

#endif //I2CTESTING_I2CBUTTONS_H
