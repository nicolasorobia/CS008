#include "textinput.h"
#include <iostream>

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1024, 768, "Just a text input window");
    SetWindowMinSize(400, 300);
    SetTargetFPS(60);

    // Audio
    InitAudioDevice();
    std::string audioPath = std::string(GetApplicationDirectory()) + "hello.wav";
    Music music = LoadMusicStream(audioPath.c_str());
    music.looping = false;

    const float boxWidth  = 320.0f;
    const float boxHeight = 30.0f;
    TextInput inputBox(Rectangle{ 0, 0, boxWidth, boxHeight }, "*input name here*");

    std::string greeting;
    // update string when user presses enter based on what they put inside inputBox
    inputBox.setOnEnter([&](const std::string& name) {
        greeting = "Hello, " + name;

        // check if music loads properly
        if (IsMusicValid(music)) {
            
            // rewind song first if audio already playing
            StopMusicStream(music);
            PlayMusicStream(music);
        }
    });

    const char* prompt     = "What is your name?";
    const int   promptSize = 40;
    const int   greetSize  = 20;

    while (!WindowShouldClose())
    {
        // F11 toggles fullscreen
        if (IsKeyPressed(KEY_F11))
            ToggleBorderlessWindowed();

        UpdateMusicStream(music);
        
        // read current size of window every frame
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        
        Rectangle boxBounds {
            screenWidth  / 2.0f - boxWidth  / 2.0f,
            screenHeight / 2.0f - boxHeight / 2.0f,
            boxWidth,
            boxHeight
        };

        // reposition inputBox according to screen size adjustments
        inputBox.setBounds(boxBounds);

        // greeting stays empty until user presses enter,
        // update inputBox as is
        if (greeting.empty())
            inputBox.Update();

        BeginDrawing();
        ClearBackground(SKYBLUE);

        if (greeting.empty())
        {
            int promptWidth = MeasureText(prompt, promptSize);
            DrawText(prompt, screenWidth / 2 - promptWidth / 2,
                     static_cast<int>(boxBounds.y) - 35, promptSize, WHITE);

            inputBox.Draw();
        } else
        {
            int greetWidth = MeasureText(greeting.c_str(), greetSize);
            DrawText(greeting.c_str(), screenWidth / 2 - greetWidth / 2,
                     screenHeight / 2 - greetSize / 2, greetSize, WHITE);
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}