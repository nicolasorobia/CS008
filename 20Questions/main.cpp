#include "raylib.h"
#include "twentyq.h"
#include <string>
#include <vector>
#include <sstream>

const int SCREEN_W = 800;
const int SCREEN_H = 500;

// Which screen is showing
enum class Screen {
    Title,          // "Dave has some questions"  [Start] [Quit]
    Asking,         // a question or a guess      [Yes]   [No]
    Correct,        // Dave guessed it
    AskThing,       // Dave was wrong: what was it?
    AskQuestion,    // a question that tells the two apart
    AskSide,        // is the answer yes or no for the new thing?
    Learned,        // thanks, saved
    Stumped         // ran out of questions
};

// ===================== GUI (button, textbox, input, game juice) =====================

// fades button color to show mouse is hovering over it
Color Lighter(Color c)
{
    return Color { 
        (unsigned char)(c.r + (255 - c.r) / 5),
        (unsigned char)(c.g + (255 - c.g) / 5),
        (unsigned char)(c.b + (255 - c.b) / 5), 255
    };
}

// Draws a button and returns true on the frame it is clicked.
bool Button(Rectangle box, const char* label, Color color)
{
    bool hover = CheckCollisionPointRec(GetMousePosition(), box);

    DrawRectangleRounded(box, 0.3f, 8, hover ? Lighter(color) : color);

    const int fontSize = 28;
    int textW = MeasureText(label, fontSize);
    DrawText(label, (int)(box.x + (box.width - textW) / 2),
                    (int)(box.y + (box.height - fontSize) / 2), fontSize, RAYWHITE);

    return hover && IsMouseButtonReleased(MOUSE_BUTTON_LEFT);
}

// Centered text that wraps onto several lines when it is too wide.
int DrawCenteredText(const std::string& text, int y, int fontSize, Color color,
                     int maxWidth = SCREEN_W - 100)
{
    std::vector<std::string> lines;
    std::istringstream words(text);
    std::string word, line;

    while (words >> word) {
        std::string tryLine = line.empty() ? word : line + " " + word;
        if (!line.empty() && MeasureText(tryLine.c_str(), fontSize) > maxWidth) {
            lines.push_back(line);
            line = word;
        } else {
            line = tryLine;
        }
    }
    if (!line.empty()) lines.push_back(line);

    for (const std::string& l : lines) {
        int x = (SCREEN_W - MeasureText(l.c_str(), fontSize)) / 2;
        DrawText(l.c_str(), x, y, fontSize, color);
        y += fontSize + 10;
    }
    return y;
}

bool TextBox(Rectangle box, std::string& text, size_t maxLength = 60)
{
    int ch = GetCharPressed();
    while (ch > 0) {
        if (ch >= 32 && ch <= 126 && text.size() < maxLength)
            text += (char)ch;
        ch = GetCharPressed();
    }
    if ((IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) && !text.empty())
        text.pop_back();

    DrawRectangleRounded(box, 0.2f, 8, RAYWHITE);
    DrawRectangleRoundedLinesEx(box, 0.2f, 8, 2.0f, DARKBLUE);

    // If the text is wider than the box, show only its end.
    const int fontSize = 26;
    std::string shown = text;
    while (!shown.empty() && MeasureText(shown.c_str(), fontSize) > box.width - 30)
        shown.erase(0, 1);

    int textX = (int)box.x + 14;
    int textY = (int)(box.y + (box.height - fontSize) / 2);
    DrawText(shown.c_str(), textX, textY, fontSize, BLACK);

    if ((int)(GetTime() * 2) % 2 == 0)                       // blinking cursor
        DrawRectangle(textX + MeasureText(shown.c_str(), fontSize) + 3, textY, 2, fontSize, BLACK);

    return IsKeyPressed(KEY_ENTER) && !text.empty();
}

// Two side-by-side buttons in the lower half of the window.
const Rectangle LEFT_BUTTON  = { 190, 330, 190, 64 };
const Rectangle RIGHT_BUTTON = { 420, 330, 190, 64 };

// ===================== the game =====================

int main()
{
    InitWindow(SCREEN_W, SCREEN_H, "Dave's 20 Questions - The Game");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);           // Esc won't close the window while typing; use Quit

    const std::string saveFile = "animals.txt";
    TwentyQuestions dave;
    dave.load(saveFile);            // keeps the starter tree if there's no file yet

    Screen screen = Screen::Title;
    std::string lastGuess, thing, question;
    bool quit = false;

    // Audio
    InitAudioDevice();
    std::string audioPath = std::string(GetApplicationDirectory()) + "assets/wiimusic.ogg";
    Music music = LoadMusicStream(audioPath.c_str());
    music.looping = true;

    if (IsMusicValid(music)) {
        StopMusicStream(music);
        PlayMusicStream(music);
    }

    while (!quit && !WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        UpdateMusicStream(music);

        switch (screen)
        {
        case Screen::Title:
            DrawCenteredText("Dave has some questions", 120, 52, BLACK);
            DrawCenteredText("Think of an animal. Dave will try to guess it.", 200, 30, GRAY);

            if (Button({ 300, 270, 200, 64 }, "Start", DARKBLUE)) {
                dave.start();
                screen = Screen::Asking;
            }
            if (Button({ 300, 352, 200, 64 }, "Quit", GRAY))
                quit = true;
            break;

        case Screen::Asking: {
            // Keeps counter of questions asked in top left corner
            std::string count = "Question " + std::to_string(dave.questionsAsked() + 1)
                              + " of " + std::to_string(TwentyQuestions::MAX_QUESTIONS);
            DrawText(count.c_str(), 30, 26, 22, GRAY);

            std::string text = dave.isGuessing() ? "Is it " + dave.prompt() + "?"
                                                 : dave.prompt();
            DrawCenteredText(dave.isGuessing() ? "Dave thinks he knows..." : "Dave asks:",
                             120, 24, GRAY);
            DrawCenteredText(text, 170, 40, BLACK);

            bool yes = Button(LEFT_BUTTON,  "Yes", GREEN);
            bool no  = Button(RIGHT_BUTTON, "No",  RED);

            if (yes || no) {
                lastGuess = dave.prompt();               // only used if this was a wrong guess

                switch (dave.answer(yes)) {
                case TwentyQuestions::Result::NextQuestion:
                    break;                               // stay here; next frame shows the next question
                case TwentyQuestions::Result::Correct:
                    screen = Screen::Correct;
                    break;
                case TwentyQuestions::Result::Wrong:
                    thing.clear();
                    question.clear();
                    screen = Screen::AskThing;
                    break;
                case TwentyQuestions::Result::OutOfQuestions:
                    screen = Screen::Stumped;
                    break;
                }
            }
            break;
        }

        case Screen::Correct: {
            std::string msg = "Dave got it in " + std::to_string(dave.questionsAsked())
                            + " questions!";
            DrawCenteredText(msg, 170, 40, BLACK);

            if (Button(LEFT_BUTTON,  "Play again", DARKBLUE)) { dave.start(); screen = Screen::Asking; }
            if (Button(RIGHT_BUTTON, "Menu",       GRAY)) screen = Screen::Title;
            break;
        }

        case Screen::AskThing:
            DrawCenteredText("Dave gives up! What were you thinking of?", 110, 30, BLACK);
            DrawCenteredText("for example: a tiger", 160, 22, GRAY);

            if (TextBox({ 150, 220, 500, 60 }, thing) ||
                (Button({ 300, 330, 200, 64 }, "Next", DARKBLUE) && !thing.empty()))
                screen = Screen::AskQuestion;
            break;

        case Screen::AskQuestion: {
            std::string msg = "Type a yes/no question that tells " + thing
                            + " apart from " + lastGuess + ".";
            DrawCenteredText(msg, 100, 28, BLACK);

            if (TextBox({ 100, 220, 600, 60 }, question) ||
                (Button({ 300, 330, 200, 64 }, "Next", DARKBLUE) && !question.empty())) {
                if (question.back() != '?') question += '?';
                screen = Screen::AskSide;
            }
            break;
        }

        case Screen::AskSide: {
            int y = DrawCenteredText("For " + thing + ", what's the answer to:", 110, 28, GRAY);
            DrawCenteredText(question, y + 10, 34, BLACK);

            bool yes = Button(LEFT_BUTTON,  "Yes", GREEN);
            bool no  = Button(RIGHT_BUTTON, "No",  RED);

            if (yes || no) {
                dave.learn(thing, question, yes);
                dave.save(saveFile);
                screen = Screen::Learned;
            }
            break;
        }

        case Screen::Learned:
            DrawCenteredText("Thanks! Dave will remember " + thing + ".", 170, 36, BLACK);

            if (Button(LEFT_BUTTON,  "Play again", DARKBLUE)) { dave.start(); screen = Screen::Asking; }
            if (Button(RIGHT_BUTTON, "Menu",       GRAY)) screen = Screen::Title;
            break;

        case Screen::Stumped:
            DrawCenteredText("20 questions and Dave is stumped. You win!", 170, 36, BLACK);

            if (Button(LEFT_BUTTON,  "Play again", DARKBLUE)) { dave.start(); screen = Screen::Asking; }
            if (Button(RIGHT_BUTTON, "Menu",       GRAY)) screen = Screen::Title;
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
