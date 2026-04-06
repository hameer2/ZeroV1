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

static void cmd_fov(const std::vector<std::string> &args) {
    if (args.empty()) return;
    float v = (float)atof(args[0].c_str());
    if (v < 30.f) v = 30.f;
    if (v > 160.f) v = 160.f;
    g_settings->setFloat("fov", v);
}

static void cmd_armor(const std::vector<std::string> &args) {
    ZeroV1::armor_hud_visible = !ZeroV1::armor_hud_visible;
}

static void cmd_hitbox(const std::vector<std::string> &args) {
    ZeroV1::hitbox_debug_visible = !ZeroV1::hitbox_debug_visible;
}

bool handleClientCommand(const std::wstring &message, Client *client)
{
    if (message.empty() || message[0] != L'.')
        return false;

    std::string narrow = wide_to_utf8(message).substr(1);
    auto args = splitArgs(narrow);
    if (args.empty()) return true;

    std::string cmd = args[0];
    args.erase(args.begin());

    if (cmd == "fov")    { cmd_fov(args);    return true; }
    if (cmd == "armor")  { cmd_armor(args);  return true; }
    if (cmd == "hitbox") { cmd_hitbox(args); return true; }

    return true;
}

} // namespace ZeroV1
