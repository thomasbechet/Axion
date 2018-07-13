#pragma once

namespace ax
{
    struct Mouse
    {
        enum Button : unsigned
        {
            Left = 0,
            Right = Left + 1,
            Middle = Right + 1,
            Button1 = Middle + 1,
            Button2 = Button1 + 1,
            Button3 = Button2 + 1,
            Button4 = Button3 + 1,
            Button5 = Button4 + 1,
            Button6 = Button5 + 1
        };

        enum Axis : unsigned
        {
            X = 0,
            Y = X + 1,
            WheelX = Y + 1,
            WheelY = WheelX + 1
        };
    };
}