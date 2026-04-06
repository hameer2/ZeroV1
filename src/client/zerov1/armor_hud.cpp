#include "armor_hud.h"
#include "zerov1.h"
#include <IVideoDriver.h>

namespace ZeroV1 {

void ArmorHud_draw(video::IVideoDriver *driver, int armor_val, float durability)
{
    if (!driver || !ZeroV1::armor_hud_visible) return;

    const int ICON = 12;
    const int GAP  = 3;
    const int MAX  = 4;

    auto screen = driver->getScreenSize();
    int total_w = MAX * (ICON + GAP) - GAP;
    int base_x  = screen.Width / 2 - total_w / 2;
    int base_y  = screen.Height - 56 - ICON - 6;

    for (int i = 0; i < MAX; i++) {
        int x = base_x + i * (ICON + GAP);
        core::recti r(x, base_y, x + ICON, base_y + ICON);
        video::SColor fill = (i < armor_val)
            ? video::SColor(220, 80, 140, 200)
            : video::SColor(120, 30, 30, 40);
        driver->draw2DRectangle(fill, r);
    }

    if (armor_val > 0) {
        int by = base_y + ICON + 3;
        int bw = total_w;
        driver->draw2DRectangle(video::SColor(160,20,20,20),
            core::recti(base_x, by, base_x + bw, by + 4));
        int fw = (int)(bw * durability);
        u8 rc  = (u8)((1.f - durability) * 220);
        u8 gc  = (u8)(durability * 200);
        driver->draw2DRectangle(video::SColor(220, rc, gc, 40),
            core::recti(base_x, by, base_x + fw, by + 4));
    }
}

} // namespace ZeroV1
