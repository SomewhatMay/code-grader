#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <file-input/inputs-reader.h>
#include <nlohmann/json.hpp>

using namespace nlohmann::literals;

TEST(ParseTestCases, SingleLineIO) {
    std::vector<test_case> result = parse_test_cases(R"(
        [
            {
                "title": "This is a title",
                "description": "This is a description",
                "inputs": "3\n3\n6\n1",
                "outputs": "10\n18"
            }
        ]
    )");

    ASSERT_TRUE(result.size() > 0);

    EXPECT_EQ(result[0].title, "Natural Numebrs");
    EXPECT_EQ(result[0].description, "This is a description");
}