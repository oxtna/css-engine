#include "Array.hxx"
#include "Engine.h"
#include "String.h"
#include "log.hxx"
#include "utility.h"

static const std::size_t INPUT_BUFFER_SIZE = 1024;

int main() {
    std::cin.unsetf(std::ios_base::skipws);
    using InputBuffer = css::Array<char, INPUT_BUFFER_SIZE>;
    InputBuffer inputBuffer;
    css::Engine engine;
    bool commandMode = false;

    while (std::cin.good()) {
        char c = '\0';
        std::cin >> c;
        if (c <= ' ' && inputBuffer.GetLength() == 0) {
            continue;
        }

        inputBuffer.Add(c);
        if (!commandMode) {
            if (streq(inputBuffer.GetRawData(), "????")) {
                commandMode = true;
                inputBuffer = InputBuffer();
            }
            else if (inputBuffer[inputBuffer.GetLength() - 1] == '}') {
                engine.Parse(inputBuffer.GetRawData());
                inputBuffer = InputBuffer();
            }
        }
        else {  // commandMode
            if (streq(inputBuffer.GetRawData(), "****")) {
                commandMode = false;
                inputBuffer = InputBuffer();
            }
            else if (streq(inputBuffer.GetRawData(), "?")) {
                log(inputBuffer.GetRawData(), engine.CountSections());
                inputBuffer = InputBuffer();
            }
            else if (inputBuffer[inputBuffer.GetLength() - 1] == '\n') {
                inputBuffer[inputBuffer.GetLength() - 1] = '\0';
                css::String input = inputBuffer.GetRawData();
                inputBuffer = InputBuffer();
                if (input.Count(',') > 2) {
                    input = input.GetSubstring(input.Find(',') + 1, input.GetLength());
                }
                auto commandStrings = splitCommand(input);
                if (streq(commandStrings[1].GetData(), "D")) {
                    std::size_t index = strToN(commandStrings[0]) - 1;
                    if (streq(commandStrings[2].GetData(), "*")) {
                        if (engine.DeleteSection(index)) {
                            log(input, "deleted");
                        }
                    }
                    else {
                        if (engine.DeleteAttributeFromSection(index, commandStrings[2])) {
                            log(input, "deleted");
                        }
                    }
                }
                else if (streq(commandStrings[1].GetData(), "E")) {
                    css::String output = engine.GetAttributeValueOfSelector(
                        commandStrings[0], commandStrings[2]);
                    if (output != css::String()) {
                        log(input, output);
                    }
                }
                else if (streq(commandStrings[1].GetData(), "S")) {
                    if (streq(commandStrings[2].GetData(), "?")) {
                        char first = *(commandStrings[0].GetData());
                        if (first >= '1' && first <= '9') {
                            std::size_t index = strToN(commandStrings[0]) - 1;
                            int output = engine.CountSelectorsInSection(index);
                            if (output != -1) {
                                log(input, output);
                            }
                        }
                        else {
                            log(input, engine.CountSelector(commandStrings[0]));
                        }
                    }
                    else {
                        std::size_t sectionIndex = strToN(commandStrings[0]) - 1;
                        std::size_t selectorIndex = strToN(commandStrings[2]) - 1;
                        css::String output =
                            engine.GetSelectorInSection(sectionIndex, selectorIndex);
                        if (output != css::String()) {
                            log(input, output);
                        }
                    }
                }
                else {
                    if (streq(commandStrings[2].GetData(), "?")) {
                        char first = *(commandStrings[0].GetData());
                        if (first >= '1' && first <= '9') {
                            std::size_t index = strToN(commandStrings[0]) - 1;
                            int output = engine.CountAttributesInSection(index);
                            if (output != -1) {
                                log(input, output);
                            }
                        }
                        else {
                            log(input, engine.CountAttribute(commandStrings[0]));
                        }
                    }
                    else {
                        std::size_t index = strToN(commandStrings[0]) - 1;
                        css::String output =
                            engine.GetAttributeValueInSection(index, commandStrings[2]);
                        if (output != css::String()) {
                            log(input, output);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
