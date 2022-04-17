#include "Settings.h"

const std::string& Game::Settings::showCode(CodeBase key)
{
    static std::map<CodeBase, std::string> base{
        { CodeBase::UnknownCode, "Unknown code!" }
        , { CodeBase::AllGood, "Everything is good!" }
        , { CodeBase::ErrorFileNotFound, "File not found!" }
    };
    if (base.find(key) == base.end()) return base[CodeBase::UnknownCode];
    
    return base[key];
}
