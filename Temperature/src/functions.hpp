#include "structs.hpp"

Rectangle GetFrame(Rectangle ToDraw, Vector2 frameoffset)
{
    return Rectangle{ToDraw.x - frameoffset.x, ToDraw.y - frameoffset.y, ToDraw.width + 2 * frameoffset.x, ToDraw.height + 2 * frameoffset.y};
}
void ButtonBar(GeneralRec ToDraw, Vector2 offset)
{
}
void DrawBar(GeneralRec ToDraw, Vector2 frameoffset, DraggableCircle &MainCircle,
             const char *TempMeasure, float TempNum, int offset)
{
    Rectangle Frame = GetFrame(ToDraw.Info, frameoffset);

    DrawRectangleRec(ToDraw.Info, ToDraw.ColorInfo);

    DrawRectangleRec(Frame, GRAY);
    DrawRectangleGradientV(ToDraw.Info.x, ToDraw.Info.y, ToDraw.Info.width, ToDraw.Info.height, RED, BLUE);
    DrawRectangle(ToDraw.Info.x, ToDraw.Info.y, ToDraw.Info.width, MainCircle.CenterPos.y - ToDraw.Info.y, (Color){100, 100, 130, 255});
    DrawText(TempMeasure, Frame.x - offset, Frame.y - 40, 30, BLACK);
    DrawText(TextFormat("%06.2f", TempNum), Frame.x + 10, Frame.y + Frame.height + 10, 30, BLACK);
}
float ConvertTemperature(int ToConvert, int display)
{
    switch (display)
    {
    case 0:
        return ToConvert / 100.0f;
        break;
    case 1:
        return ToConvert / 100.0f + 273.15f;
        break;
    case 2:
        return ToConvert / 100.0f * 0.8;
        break;
    case 3:
        return (ToConvert / 100.0f * 9 / 5) + 32.0f;
        break;
    default:
        break;
    }
    return 0;
}
void UpdateTemperature(System &Setting, Rectangle CircleFrame, DraggableCircle TempCircle)
{
    Setting.currenttemp = (CircleFrame.height + CircleFrame.y - TempCircle.CenterPos.y) * Setting.maxtemp / CircleFrame.height;
    Setting.displayedtemp = ConvertTemperature(Setting.currenttemp, Setting.currentdisplay);
}