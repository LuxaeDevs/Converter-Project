#include <iostream>
#include <vector>
#include <raylib.h>
using std::cout;
using std::string;
using std::vector;

int FPS = 300;
int screenWidth = 800;
int screenHeight = 480;
struct System
{
    string Condition = "Idle";
    float transitiontime = 0.5;
    int measuring = 0;
    int currentdisplay = 0;
    int currenttemp = 1000;
    int maxtemp = 10000;
    float displayedtemp;
};
struct Objects
{
    Color ColorInfo;
    Objects(Color ColorInfo)
    {
        this->ColorInfo = ColorInfo;
    }
};

struct GeneralRec
{
    Rectangle Info;
    Color ColorInfo;
    void Draw()
    {
        DrawRectangleRec(Info, ColorInfo);
    }
};
Rectangle GetFrame(Rectangle ToDraw, Vector2 frameoffset);
struct Button : GeneralRec
{
    Color ColorIdle;
    Color ColorInteract;
    string Name;
    Button(Rectangle Rec, Color Idle, Color Interact, string Name)
    {
        Info.x = Rec.x;
        Info.y = Rec.y;
        Info.width = Rec.width;
        Info.height = Rec.height;
        ColorIdle = Idle;
        ColorInteract = Interact;
        this->Name = Name;
    }
    template <typename Val>
    void InteractDefault(Vector2 MousePos, Vector2 Offset, Val *ToSwitch, Val Switching, int offset)
    {
        DrawRectangleRounded(GetFrame(Info, Offset), 0.2, 0.3, Color{100, 100, 100, 255});
        Draw();
        DrawText(Name.c_str(), Info.x + Info.width / 2 - offset, Info.y, Info.height, BLACK);
        if (!CheckCollisionPointRec(MousePos, Info))
        {
            ColorInfo = ColorIdle;
            return;
        }
        ColorInfo = ColorInteract;
        if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            return;
        }
        *ToSwitch = Switching;
    }
};
struct Triangle : Objects
{
    Vector2 point1;
    Vector2 point2;
    Vector2 point3;
    Triangle(Vector2 point1, Vector2 point2, Vector2 point3, Color ColorInfo) : Objects(ColorInfo)
    {
        this->point1 = point1;
        this->point2 = point2;
        this->point3 = point3;
    }
};
struct DraggableCircle : Objects
{
    Color ColorIdle;
    Color ColorInteract;
    Vector2 CenterPos;
    float minposx;
    float maxposx;
    float radius;
    DraggableCircle(Vector3 Info, Vector2 Border, Color ColorIdle, Color ColorInteract) : Objects(ColorIdle)
    {
        this->CenterPos.x = Info.x;
        this->CenterPos.y = Info.y;
        this->radius = Info.z;
        this->ColorInteract = ColorInteract;
        this->ColorIdle = ColorIdle;
    }
    void DragCircle(Vector2 MousePos, Vector2 DeltaPos, Rectangle Frame)
    {
        if (!CheckCollisionPointCircle(MousePos, CenterPos, radius))
        {
            ColorInfo = ColorIdle;
            return;
        }
        ColorInfo = ColorInteract;
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            return;
        }
        if (CenterPos.y + DeltaPos.y < Frame.y)
        {
            CenterPos.y = Frame.y;
            return;
        }
        if (CenterPos.y + DeltaPos.y > Frame.y + Frame.height)
        {
            CenterPos.y = Frame.y + Frame.height;
            return;
        }
        CenterPos.y = CenterPos.y + DeltaPos.y;
    }
};

struct OnScreen
{
};