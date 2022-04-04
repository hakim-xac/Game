#include "Settings.h"

std::string_view Game::Settings::showError(CodeErrors key)
{
    static std::map<CodeErrors, std::string_view> base{
        { CodeErrors::FileNotFound, "File not found!" }
    };
    if (base.find(key) == base.end()) return std::string_view{ "Unique bug! " };
    
    return base[key];
}
