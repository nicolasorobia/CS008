#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "raylib.h"
#include <string>
#include <cstddef>
#include <functional>

class TextInput{
private:
    // layout
    Rectangle bounds;
    std::string text;
    std::string placeholder;
    std::size_t maxChars {100};

    // focus state
    bool mouseOnText {false};
    int frameCounter {0}; // caret blink rate

    // style
    int fontSize {30};
    int padding {4};
    Color fillColor        {BLACK};
    Color borderColor      {WHITE};
    Color textColor        {WHITE};
    Color placeholderColor {LIGHTGRAY};

    // moves caret left or right
    std::size_t caret {0};
    int scroll {0};

    // logic for these two functions were AI prompted for shortcut
    // prompt: how to implement left and arrow keys to adjust caret position in raylib
    int caretOffset() const;
    void updateScroll();

    // call when user presses Enter key
    std::function<void(const std::string&)> onEnter;
    
public:
    TextInput(Rectangle bounds, const std::string& placeholder)
        : bounds {bounds}, placeholder {placeholder} {}

    void setBounds(Rectangle newBounds) { bounds = newBounds; }

    void setOnEnter(std::function<void(const std::string&)> callback) {
        onEnter = std::move(callback);
    }

    void Update();
    void Draw() const;
};

#endif