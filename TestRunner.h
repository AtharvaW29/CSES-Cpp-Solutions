#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <filesystem>
#include <fstream>
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

    template <typename>
    inline constexpr bool AlwaysFalse = false;

    class ScopedStreamRedirect
    {
    public:
        ScopedStreamRedirect(std::ostream& stream, std::streambuf* replacement)
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
        std::ostream& stream_;
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

    template <typename Problem>
    concept HasCustomValidator = requires(
        const std::string& input,
        const std::string& expected,
        const std::string& actual,
        std::string& reason)
    {
        { Problem::Validate(input, expected, actual, reason) } -> std::convertible_to<bool>;
    };

    inline bool ValidateFourSum(
        const std::string& inputText,
        const std::string& expectedText,
        const std::string& actualText,
        std::string& reason)
    {
        std::istringstream input(inputText);
        int size = 0;
        long long target = 0;
        if (!(input >> size >> target) || size < 0)
        {
            reason = "invalid test input";
            return false;
        }

        std::vector<long long> values(static_cast<std::size_t>(size));
        for (long long& value : values)
        {
            if (!(input >> value))
            {
                reason = "invalid test input";
                return false;
            }
        }

        std::istringstream expected(expectedText);
        std::string expectedFirst;
        expected >> expectedFirst;

        std::istringstream actual(actualText);
        std::string actualFirst;
        if (!(actual >> actualFirst))
        {
            reason = "empty output";
            return false;
        }

        if (expectedFirst == "IMPOSSIBLE")
        {
            if (actualFirst == "IMPOSSIBLE")
            {
                return true;
            }
            reason = "a solution was printed for an impossible case";
            return false;
        }

        if (actualFirst == "IMPOSSIBLE")
        {
            reason = "a valid solution exists";
            return false;
        }

        std::array<int, 4> indices{};
        try
        {
            std::size_t used = 0;
            indices[0] = std::stoi(actualFirst, &used);
            if (used != actualFirst.size())
            {
                throw std::invalid_argument("not an integer");
            }
        }
        catch (const std::exception&)
        {
            reason = "output must contain four indices or IMPOSSIBLE";
            return false;
        }

        if (!(actual >> indices[1] >> indices[2] >> indices[3]))
        {
            reason = "fewer than four indices";
            return false;
        }

        std::string extra;
        if (actual >> extra)
        {
            reason = "more than four indices";
            return false;
        }

        for (int index : indices)
        {
            if (index < 1 || index > size)
            {
                reason = "an index is outside the input array";
                return false;
            }
        }

        std::array<int, 4> sortedIndices = indices;
        std::sort(sortedIndices.begin(), sortedIndices.end());
        if (std::adjacent_find(sortedIndices.begin(), sortedIndices.end()) != sortedIndices.end())
        {
            reason = "indices are not distinct";
            return false;
        }

        long long sum = 0;
        for (int index : indices)
        {
            sum += values[static_cast<std::size_t>(index - 1)];
        }
        if (sum != target)
        {
            reason = "the selected values do not sum to the target";
            return false;
        }

        return true;
    }

    template <typename Problem>
    void RunProblem(const std::string& inputText, std::ostream& output)
    {
        if constexpr (
            std::default_initializable<Problem> &&
            requires(Problem& problem, std::istream& input, std::ostream& result)
            {
                problem.Solve(input, result);
            })
        {
            std::istringstream input(inputText);
            Problem problem;
            problem.Solve(input, output);
        }
        else if constexpr (std::constructible_from<Problem, int, int, std::vector<int>&>)
        {
            // Supports classes such as FourSum whose constructor receives the
            // first two input values followed by an integer array, invokes
            // Solve() itself, and writes its answer to std::cout.
            std::istringstream input(inputText);
            int size = 0;
            int target = 0;
            if (!(input >> size >> target) || size < 0)
            {
                throw std::runtime_error("expected: <size> <target> followed by <size> integers");
            }

            std::vector<int> values(static_cast<std::size_t>(size));
            for (int& value : values)
            {
                if (!(input >> value))
                {
                    throw std::runtime_error("input contains fewer values than its declared size");
                }
            }

            ScopedStreamRedirect capture(std::cout, output.rdbuf());
            Problem problem(size, target, values);
            (void)problem;
        }
        else
        {
            static_assert(
                AlwaysFalse<Problem>,
                "Unsupported problem class. Provide either a default constructor plus "
                "Solve(std::istream&, std::ostream&), or a constructor matching "
                "Problem(int size, int target, std::vector<int>&).");
        }
    }

    template <typename Problem>
    bool OutputMatches(
        std::string_view problemName,
        const std::string& input,
        const std::string& expected,
        const std::string& actual,
        std::string& reason)
    {
        if (problemName == "FourSum")
        {
            return ValidateFourSum(input, expected, actual, reason);
        }
        else if constexpr (HasCustomValidator<Problem>)
        {
            return Problem::Validate(input, expected, actual, reason);
        }
        else if (Tokens(expected) == Tokens(actual))
        {
            return true;
        }
        else
        {
            reason = "output differs";
            return false;
        }
    }

    template <typename Problem>
    bool RunTests(std::string_view problemName, const fs::path& testCaseFolder)
    {
        std::cout << "Testing " << problemName << " from " << testCaseFolder.string() << "\n\n";

        if (!fs::is_directory(testCaseFolder))
        {
            std::cerr << "Test folder not found: " << fs::absolute(testCaseFolder).string() << '\n';
            return false;
        }

        std::vector<fs::path> inputFiles;
        for (const fs::directory_entry& entry : fs::directory_iterator(testCaseFolder))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".in")
            {
                inputFiles.push_back(entry.path());
            }
        }
        std::sort(inputFiles.begin(), inputFiles.end(), NaturalLess);

        if (inputFiles.empty())
        {
            std::cerr << "No .in files found in " << fs::absolute(testCaseFolder).string() << '\n';
            return false;
        }

        std::size_t passed = 0;
        for (const fs::path& inputPath : inputFiles)
        {
            fs::path outputPath = inputPath;
            outputPath.replace_extension(".out");

            if (!fs::exists(outputPath))
            {
                std::cout << "[FAIL] " << inputPath.filename().string()
                          << " (missing " << outputPath.filename().string() << ")\n";
                continue;
            }

            try
            {
                const std::string inputText = ReadFile(inputPath);
                const std::string expectedText = ReadFile(outputPath);
                std::ostringstream actual;

                RunProblem<Problem>(inputText, actual);

                std::string reason;
                if (OutputMatches<Problem>(problemName, inputText, expectedText, actual.str(), reason))
                {
                    ++passed;
                    std::cout << "[PASS] " << inputPath.filename().string() << '\n';
                }
                else
                {
                    std::cout << "[FAIL] " << inputPath.filename().string()
                              << " (" << reason << ")\n"
                              << "       expected: " << expectedText
                              << "       actual:   " << actual.str() << '\n';
                }
            }
            catch (const std::exception& error)
            {
                std::cout << "[FAIL] " << inputPath.filename().string()
                          << " (exception: " << error.what() << ")\n";
            }
        }

        const std::size_t failed = inputFiles.size() - passed;
        std::cout << "\n" << passed << '/' << inputFiles.size() << " passed";
        if (failed != 0)
        {
            std::cout << ", " << failed << " failed";
        }
        std::cout << '\n';
        return failed == 0;
    }
}

#define Test(ProblemClass, TestCaseFolder) \
    ::cses_test::RunTests<ProblemClass>(#ProblemClass, TestCaseFolder)
