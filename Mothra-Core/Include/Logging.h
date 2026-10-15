#pragma once
/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/


#include <format>
#include <iostream>
#include <string_view>
#include <mutex>
#include <string>

enum class VulkanLogLevel
{
    Trace,
    Info,
    Warning,
    Error,
    Critical
};

class VulkanLogger
{
public:
    template<typename... Args>
    static void Trace(std::format_string<Args...> fmt, Args&&... args)
    {
        Log(VulkanLogLevel::Trace,
            std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void Info(std::format_string<Args...> fmt, Args&&... args)
    {
        Log(VulkanLogLevel::Info,
            std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void Warn(std::format_string<Args...> fmt, Args&&... args)
    {
        Log(VulkanLogLevel::Warning,
            std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void Error(std::format_string<Args...> fmt, Args&&... args)
    {
        Log(VulkanLogLevel::Error,
            std::format(fmt, std::forward<Args>(args)...));
    }

    template<typename... Args>
    static void Critical(std::format_string<Args...> fmt, Args&&... args)
    {
        Log(VulkanLogLevel::Critical,
            std::format(fmt, std::forward<Args>(args)...));
    }

private:
    template<typename... Args>
    static void Log(VulkanLogLevel level, Args&&... args)
    {
        static std::mutex mutex;
        std::lock_guard<std::mutex> lock(mutex);

        constexpr const char* RESET = "\033[0m";
        constexpr const char* GRAY = "\033[90m";
        constexpr const char* GREEN = "\033[32m";
        constexpr const char* YELLOW = "\033[33m";
        constexpr const char* RED = "\033[31m";
        constexpr const char* MAGENTA = "\033[35m";

        const char* color = RESET;
        const char* label = "";

        switch (level)
        {
        case VulkanLogLevel::Trace:
            color = GRAY;
            label = "[VULKAN TRACE] ";
            break;

        case VulkanLogLevel::Info:
            color = GREEN;
            label = "[VULKAN INFO] ";
            break;

        case VulkanLogLevel::Warning:
            color = YELLOW;
            label = "[VULKAN WARNING] ";
            break;

        case VulkanLogLevel::Error:
            color = RED;
            label = "[VULKAN ERROR] ";
            break;

        case VulkanLogLevel::Critical:
            color = MAGENTA;
            label = "[VULKAN CRITICAL] ";
            break;
        }

        std::clog << color << label;
        (std::clog << ... << std::forward<Args>(args));
        std::clog << RESET << '\n';
    }
};

// Logging macros
#define VK_LOG_TRACE(...)    VulkanLogger::Trace(__VA_ARGS__)
#define VK_LOG_INFO(...)     VulkanLogger::Info(__VA_ARGS__)
#define VK_LOG_WARN(...)     VulkanLogger::Warn(__VA_ARGS__)
#define VK_LOG_ERROR(...)    VulkanLogger::Error(__VA_ARGS__)
#define VK_LOG_CRITICAL(...) VulkanLogger::Critical(__VA_ARGS__)
