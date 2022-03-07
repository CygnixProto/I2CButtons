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
#include <memory>
#include <chrono>
#include <thread>

#include "I2CButtons.h"

int main() {

    std::unique_ptr<CygnixProto::I2CButtons> buttons;
    try {
        buttons = std::make_unique<CygnixProto::I2CButtons>();
    } catch (std::exception &e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    for(;;) {
        if(buttons != nullptr) {
            buttons->updateState();
        }

        if(buttons->isButtonDown(CygnixProto::Button::A)) {
            std::cout << "Button A is Pressed\n";
        }

        if(buttons->isButtonHeld(CygnixProto::Button::A)) {
            std::cout << "Button A is Held\n";
        }

        if(buttons->isButtonUp(CygnixProto::Button::A)) {
            std::cout << "Button A is Released\n";
        }
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
