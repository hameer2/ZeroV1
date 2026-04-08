#include "command_handler.h"
#include "zerov1.h"
#include "settings.h"
#include "util/string.h"
#include <sstream>
#include <vector>

namespace ZeroV1 {

static std::vector<std::string> splitArgs(const std::string &s) {
    std::istringstream ss(s);
    std::vector<std::string> out;
    std::string tok;
    while (ss >> tok) out.push_back(tok);
    return out;
}

bool handleClientCommand(const std::wstring &message, Client *client, std::wstring &response)
{
    if (message.empty() || message[0] != L'.')
        return false;

    std::string narrow = wide_to_utf8(message).substr(1);
    auto args = splitArgs(narrow);
    if (args.empty()) return true;

    std::string cmd = args[0];
    args.erase(args.begin());

    if (cmd == "fov") {
        if (args.empty()) { response = L"[ZeroV1] Usage: .fov <30-160>"; return true; }
        float v = (float)atof(args[0].c_str());
        if (v < 30.f) v = 30.f;
        if (v > 160.f) v = 160.f;
        g_settings->setFloat("fov", v);
        response = L"[ZeroV1] FOV set to " + utf8_to_wide(args[0]);
        return true;
    }
    if (cmd == "armor") {
        ZeroV1::armor_hud_visible = !ZeroV1::armor_hud_visible;
        response = ZeroV1::armor_hud_visible ? L"[ZeroV1] Armor HUD: ON" : L"[ZeroV1] Armor HUD: OFF";
        return true;
    }
    if (cmd == "hitbox") {
        ZeroV1::hitbox_debug_visible = !ZeroV1::hitbox_debug_visible;
        response = ZeroV1::hitbox_debug_visible ? L"[ZeroV1] Hitbox debug: ON" : L"[ZeroV1] Hitbox debug: OFF";
        return true;
    }

    if (cmd == "fovscroll") {
        bool cur = g_settings->getBool("zerov1_fov_scroll");
        g_settings->setBool("zerov1_fov_scroll", !cur);
        response = !cur ? L"[ZeroV1] FOV scroll: ON  (scroll wheel changes FOV)" : L"[ZeroV1] FOV scroll: OFF";
        return true;
    }
    if (cmd == "help") {
        response = L"[ZeroV1] Commands: .fov <val>  .armor  .hitbox  .fovscroll  .help";
        return true;
    }

    response = L"[ZeroV1] Unknown command. Type .help for a list of commands.";
    return true;
}

} // namespace ZeroV1
