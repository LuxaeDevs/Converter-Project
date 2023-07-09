#include "functions.hpp"

int main()
{
    InitWindow(screenWidth, screenHeight, "Temperature Converter");
    System Setting;
    std::cout
        << "owo";
    // General PlayerHitbox = General(100, 100, 64, 64);
    DraggableCircle TempCircle = DraggableCircle({60, 60, 20}, {0, (float)Setting.maxtemp}, (Color){80, 80, 80, 255}, (Color){220, 220, 220, 255});
    Rectangle CircleFrame = {TempCircle.CenterPos.x - 5, 70, 10, 250};
    TempCircle.CenterPos.y = CircleFrame.y + CircleFrame.height * (Setting.maxtemp - Setting.currenttemp) / Setting.maxtemp;
    GeneralRec Celsius =
        {screenWidth / 5 - 10, CircleFrame.y, 80, CircleFrame.height, (Color){100, 100, 130, 255}};

    GeneralRec Kelvin =
        {2 * screenWidth / 5 - 10, CircleFrame.y, 80, CircleFrame.height, (Color){100, 100, 130, 255}};

    GeneralRec Reamur = {3 * screenWidth / 5 - 10, CircleFrame.y, 80, CircleFrame.height, (Color){100, 100, 130, 255}};
    GeneralRec Fahrenheit = {4 * screenWidth / 5 - 10, CircleFrame.y, 80, CircleFrame.height, (Color){100, 100, 130, 255}};
    Button TempButton = Button({screenWidth / 2 - 200, 100, 400, 50}, RED, GREEN, "Temperature");
    Button QuitButton = Button({10, 10, 100, 30}, RED, GREEN, "QUIT");
    SetTargetFPS(FPS);
    while (!WindowShouldClose())
    {
        UpdateTemperature(Setting, CircleFrame, TempCircle);
        Vector2 MousePos = GetMousePosition();
        Vector2 DeltaMousePos = GetMouseDelta();
        TempCircle.DragCircle(MousePos, DeltaMousePos, CircleFrame);
        BeginDrawing();
        ClearBackground(WHITE);
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(GRAY, 0.6F));
        switch (Setting.measuring)
        {
        case 0:
            TempButton.InteractDefault<int>(MousePos, {10, 10}, &Setting.measuring, 1, 170);
            DrawRectangle(0, 0, screenWidth, 80, PURPLE);
            DrawText("Conversion Collection", 10, 10, 70, GOLD);
            break;
        case 1:
            QuitButton.InteractDefault<int>(MousePos, {5, 5}, &Setting.measuring, 0, 35);
            DrawBar(Celsius, {10, 20}, TempCircle, "Celsius", ConvertTemperature(Setting.currenttemp, 0), 0);
            DrawBar(Kelvin, {10, 20}, TempCircle, "Kelvin", ConvertTemperature(Setting.currenttemp, 1), -5);
            DrawBar(Reamur, {10, 20}, TempCircle, "Reamur", ConvertTemperature(Setting.currenttemp, 2), 0);
            DrawBar(Fahrenheit, {10, 20}, TempCircle, "Fahrenheit", ConvertTemperature(Setting.currenttemp, 3), 30);
            DrawRectangleRec(CircleFrame, GRAY);
            DrawText("TEMPERATURE CONVERTER", 100, 400, 40, BLUE);
            // DrawTriangle(TestTriange.point1, TestTriange.point2, TestTriange.point3, TestTriange.ColorInfo);
            DrawCircle(TempCircle.CenterPos.x, TempCircle.CenterPos.y, TempCircle.radius, TempCircle.ColorInfo);
            break;
        default:
            break;
        }
        EndDrawing();
    }
    CloseWindow();
}