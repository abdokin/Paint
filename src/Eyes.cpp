#include "Eyes.h"
#include <math.h>       // Required for: atan2f()

void Eyes::update()
{
    irisLeftPosition = GetMousePosition();
    irisRightPosition = GetMousePosition();

    // Check not inside the left eye sclera
    if (!CheckCollisionPointCircle(irisLeftPosition, scleraLeftPosition, scleraRadius - 20))
    {
        dx = irisLeftPosition.x - scleraLeftPosition.x;
        dy = irisLeftPosition.y - scleraLeftPosition.y;

        angle = atan2f(dy, dx);

        dxx = (scleraRadius - irisRadius) * cosf(angle);
        dyy = (scleraRadius - irisRadius) * sinf(angle);

        irisLeftPosition.x = scleraLeftPosition.x + dxx;
        irisLeftPosition.y = scleraLeftPosition.y + dyy;
    }

    // Check not inside the right eye sclera
    if (!CheckCollisionPointCircle(irisRightPosition, scleraRightPosition, scleraRadius - 20))
    {
        dx = irisRightPosition.x - scleraRightPosition.x;
        dy = irisRightPosition.y - scleraRightPosition.y;

        angle = atan2f(dy, dx);

        dxx = (scleraRadius - irisRadius) * cosf(angle);
        dyy = (scleraRadius - irisRadius) * sinf(angle);

        irisRightPosition.x = scleraRightPosition.x + dxx;
        irisRightPosition.y = scleraRightPosition.y + dyy;
    }
}

void Eyes::draw()
{
    DrawCircleV(scleraLeftPosition, scleraRadius, LIGHTGRAY);
    DrawCircleV(irisLeftPosition, irisRadius, BROWN);
    DrawCircleV(irisLeftPosition, 10, BLACK);

    DrawCircleV(scleraRightPosition, scleraRadius, LIGHTGRAY);
    DrawCircleV(irisRightPosition, irisRadius, DARKGREEN);
    DrawCircleV(irisRightPosition, 10, BLACK);

}
