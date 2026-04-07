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
    if (cmd == "chatcolor") {
        if (args.empty()) { response = L"[ZeroV1] Usage: .chatcolor <red|green|blue|yellow|white|purple|orange|none>"; return true; }
        std::string color = args[0];
        if (color == "none" || color == "off") { ZeroV1::chat_color_hex = ""; response = L"[ZeroV1] Chat color cleared."; }
        else if (color == "red")    { ZeroV1::chat_color_hex = "#FF4444"; response = L"[ZeroV1] Chat color: red"; }
        else if (color == "green")  { ZeroV1::chat_color_hex = "#44FF44"; response = L"[ZeroV1] Chat color: green"; }
        else if (color == "blue")   { ZeroV1::chat_color_hex = "#4488FF"; response = L"[ZeroV1] Chat color: blue"; }
        else if (color == "yellow") { ZeroV1::chat_color_hex = "#FFFF44"; response = L"[ZeroV1] Chat color: yellow"; }
        else if (color == "white")  { ZeroV1::chat_color_hex = "#FFFFFF"; response = L"[ZeroV1] Chat color: white"; }
        else if (color == "purple") { ZeroV1::chat_color_hex = "#CC44FF"; response = L"[ZeroV1] Chat color: purple"; }
        else if (color == "orange") { ZeroV1::chat_color_hex = "#FF8844"; response = L"[ZeroV1] Chat color: orange"; }
        else { response = L"[ZeroV1] Colors: red green blue yellow white purple orange none"; }
        return true;
    }
    if (cmd == "fovscroll") {
        ZeroV1::fov_scroll_mode = !ZeroV1::fov_scroll_mode;
        response = ZeroV1::fov_scroll_mode ? L"[ZeroV1] FOV scroll: ON  (scroll wheel changes FOV)" : L"[ZeroV1] FOV scroll: OFF";
        return true;
    }
    if (cmd == "help") {
        response = L"[ZeroV1] Commands: .fov <val>  .armor  .hitbox  .chatcolor <color>  .fovscroll  .help";
        return true;
    }

    response = L"[ZeroV1] Unknown command. Type .help for a list of commands.";
    return true;
}

} // namespace ZeroV1
