#pragma once

#ifdef __linux__
    #define FMT_HEADER_ONLY
    #include <fmt/core.h>
    #include <fmt/printf.h>
#else
    #include <print>
    #include <cstdio>
#endif

#include <sstream>
#include <string>
#include <thread>

namespace utils {

    std::string to_string(std::thread::id id) {
        std::stringstream ss;
        ss << id;
        return ss.str();
    }

    template<typename... Args>
    void print(fmt::format_string<Args...> fmt, Args&&... args) {
        #ifdef __linux__
            fmt::print(fmt, std::forward<Args>(args)...);
        #else
            std::print(fmt, std::forward<Args>(args)...);
        #endif
    };

    template<typename... Args>
    int printf(fmt::format_string<Args...> fmt, Args&&... args) {
        #ifdef __linux__
            return fmt::printf(fmt, std::forward<Args>(args)...);
        #else
            return std::printf(fmt.data(), std::forward<Args>(args)...);
        #endif
    }

    template<typename... Args>
    void println(fmt::format_string<Args...> fmt, Args&&... args) {
        #ifdef __linux__
            fmt::print(fmt, std::forward<Args>(args)...);
            fmt::print("\n");
        #else
            std::println(fmt, std::forward<Args>(args)...);
        #endif
    }
};