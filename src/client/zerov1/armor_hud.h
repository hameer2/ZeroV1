#pragma once

namespace video { class IVideoDriver; }

namespace ZeroV1 {
    void ArmorHud_draw(video::IVideoDriver *driver, int armor_val, float durability);
}
