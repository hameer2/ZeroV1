#pragma once
#include <string>
#include <vector>

class Client;

namespace ZeroV1 {
    bool handleClientCommand(const std::wstring &message, Client *client, std::wstring &response);
}
