#pragma once

#ifdef __linux__
#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fmt/printf.h>
#else
#include <cstdio>
#include <print>
#endif

#include <sstream>
#include <string>
#include <thread>

namespace utils
{

std::string to_string(std::thread::id id)
{
    std::stringstream ss;
    ss << id;
    return ss.str();
}

#ifdef __linux__
template < typename... Args > void print(fmt::format_string< Args... > fmt, Args &&...args)
{
    fmt::print(fmt, std::forward< Args >(args)...);
};
#else
template < typename... Args > int print(std::format_string< Args... > fmt, Args &&...args)
{
    return std::printf(fmt.data(), std::forward< Args >(args)...);
}
#endif

#ifdef __linux__
template < typename... Args > void printf(fmt::format_string< Args... > fmt, Args &&...args)
{
    fmt::print(fmt, std::forward< Args >(args)...);
};
#else
template < typename... Args > int printf(std::format_string< Args... > fmt, Args &&...args)
{
    return std::printf(fmt, std::forward< Args >(args)...);
}
#endif

#ifdef __linux__
template < typename... Args > void println(fmt::format_string< Args... > fmt, Args &&...args)
{
    fmt::print(fmt, std::forward< Args >(args)...);
    fmt::print("\n");

#else
template < typename... Args > void println(std::format_string< Args... > fmt, Args &&...args)
{
    std::println(fmt, std::forward< Args >(args)...);
}
#endif
}; // namespace utils
