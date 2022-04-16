#pragma once
#include <iostream>
#include <utility>

namespace Game {

    template <typename T = std::string>
    class Logs {
    public: 

        template <typename Arg, typename... Args>
        Logs(Arg arg, Args&&... args) {
            if (id == std::numeric_limits<unsigned long long>::max()) id = 0;
            out_ << "log_id:\t" << ++id << "\n";
            (out_ << arg, ((out_ << " " << std::forward<Args>(args)), ...));
            out_ << "\n";
        }
    private:
        Logs() = delete;
        inline static unsigned long long id{};
        inline static std::ostream& out_{ std::cout };
    };
}