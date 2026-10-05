#ifndef TEXTINPUT_CPP
#define TEXTINPUT_CPP

#include "textinput.h"
#include <algorithm>

static bool pressedOrHeld(int key)
{
    return IsKeyPressed(key) || IsKeyPressedRepeat(key);
}

int TextInput::caretOffset() const
{
    if (caret == 0) return 0;
    return MeasureText(text.substr(0, caret).c_str(), fontSize) + fontSize / 10;
}

void TextInput::updateScroll()
{
    const int caretWidth = 2;
    const int visible    = static_cast<int>(bounds.width) - 2 * padding;
    const int caretX     = caretOffset();

    // increment caret to the right
    if (caretX + caretWidth - scroll > visible)
        scroll = caretX + caretWidth - visible;

    // decrement caret to the left
    if (caretX - scroll < 0)
        scroll = caretX;

    const int textWidth = MeasureText(text.c_str(), fontSize) + fontSize / 10 + caretWidth;
    const int maxScroll = std::max(0, textWidth - visible);
    // only lets caret shift left or right from 0 to end of text ONLY
    scroll = std::clamp(scroll, 0, maxScroll);
}

void TextInput::Update()
{
    // click inside box to start typing, click anywhere else to unfocus
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        mouseOnText = CheckCollisionPointRec(GetMousePosition(), bounds);
    
    if (!mouseOnText)
    {
        frameCounter = 0;
        return;
    }
    ++frameCounter;

    int key = GetCharPressed();
    while (key > 0)
    {
        // only allow visible, printable characters (no enter, backspace, etc.)
        if (key >= 32 && key <= 126 && text.size() < maxChars) {
            text.insert(caret, 1, static_cast<char>(key));
            ++caret;
            frameCounter = 0;
        }

        // calling GetCharPressed() handles input lag/lost keystrokes
        key = GetCharPressed(); 
    }

    if (pressedOrHeld(KEY_LEFT) && caret > 0) {
        --caret;
        frameCounter = 0;
    }

    if (pressedOrHeld(KEY_RIGHT) && caret < text.size()) {
        ++caret;
        frameCounter = 0;
    }

    if (pressedOrHeld(KEY_BACKSPACE) && caret > 0) {
        text.erase(caret - 1, 1);
        --caret;
        frameCounter = 0;
    }

    if (pressedOrHeld(KEY_DELETE) && caret < text.size()) {
        text.erase(caret, 1);
        frameCounter = 0;
    }

    if (IsKeyPressed(KEY_HOME)) {
        caret = 0;
        frameCounter = 0;
    }

    if (IsKeyPressed(KEY_END)) {
        caret = text.size();
        frameCounter = 0;
    }
    
    updateScroll();

    // pass the text only with enter key only if text is not empty, does nothing
    // if enter is pressed with empty text
    if (IsKeyPressed(KEY_ENTER) && !text.empty() && onEnter)
        onEnter(text);
}

void TextInput::Draw() const
{
    DrawRectangleRec(bounds, fillColor);

    // if mouseOnText, make border thicker
    DrawRectangleLinesEx(bounds, mouseOnText ? 2.0f : 1.0f, borderColor);

    // keeps text message to the left border of box
    int x = static_cast<int>(bounds.x) + padding - scroll;

    // centers each character text in position of box height
    int y = static_cast<int>(bounds.y + (bounds.height - fontSize) / 2);

    // REQUIRED for overflow
    BeginScissorMode(static_cast<int>(bounds.x), static_cast<int>(bounds.y),
                     static_cast<int>(bounds.width), static_cast<int>(bounds.height));

    if (text.empty() && !mouseOnText)
        DrawText(placeholder.c_str(), x, y, fontSize, placeholderColor);
    else
    {
        DrawText(text.c_str(), x, y, fontSize, textColor);
 
        if (mouseOnText && (frameCounter / 20) % 2 == 0)
            DrawRectangle(x + caretOffset() - 1, y, 2, fontSize, textColor);
    }

    EndScissorMode();
}

#endif


