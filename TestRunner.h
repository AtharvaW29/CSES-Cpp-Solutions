#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace cses_test
{
    namespace fs = std::filesystem;

    using Validator = bool (*)(
        const std::string& input,
        const std::string& expected,
        const std::string& actual,
        std::string& reason);

    class ScopedStreamRedirect
    {
    public:
        ScopedStreamRedirect(std::ios& stream, std::streambuf* replacement)
            : stream_(stream), original_(stream.rdbuf(replacement))
        {
        }

        ScopedStreamRedirect(const ScopedStreamRedirect&) = delete;
        ScopedStreamRedirect& operator=(const ScopedStreamRedirect&) = delete;

        ~ScopedStreamRedirect()
        {
            stream_.rdbuf(original_);
        }

    private:
        std::ios& stream_;
        std::streambuf* original_;
    };

    inline std::string ReadFile(const fs::path& path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Could not open " + path.string());
        }

        return { std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
    }

    inline std::vector<std::string> Tokens(std::string_view text)
    {
        std::istringstream input{ std::string(text) };
        std::vector<std::string> tokens;
        for (std::string token; input >> token;)
        {
            tokens.push_back(std::move(token));
        }
        return tokens;
    }

    inline bool NaturalLess(const fs::path& left, const fs::path& right)
    {
        const std::string a = left.stem().string();
        const std::string b = right.stem().string();

        const bool aIsNumber = !a.empty() &&
            std::all_of(a.begin(), a.end(), [](unsigned char c) { return c >= '0' && c <= '9'; });
        const bool bIsNumber = !b.empty() &&
            std::all_of(b.begin(), b.end(), [](unsigned char c) { return c >= '0' && c <= '9'; });

        if (aIsNumber && bIsNumber)
        {
            return std::stoull(a) < std::stoull(b);
        }
        return a < b;
    }

    inline bool ValidateFourSum(
        const std::string& inputText,
        const std::string& expectedText,
        const std::string& actualText,
        std::string& reason)
    {
        std::istringstream input(inputText);
        int size = 0;
        long long target = 0;