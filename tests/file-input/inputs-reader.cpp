#include <file-input/inputs-reader.h>

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "stdio.h"

using namespace nlohmann::literals;
using json = nlohmann::json;

TEST(ParseTestCases, SingleLineIO) {
  std::vector<test_case> result = parse_test_cases(json::parse(R"(
        [
            {
                "title": "This is a title",
                "description": "This is a description",
                "inputs": "3\n3\n6\n1",
                "outputs": "10\n18"
            }
        ]
    )"));

  ASSERT_TRUE(result.size() > 0);

  EXPECT_EQ(result[0].title, "This is a title");
  EXPECT_EQ(result[0].description, "This is a description");

  EXPECT_EQ(result[0].inputs, "3\n3\n6\n1");
  EXPECT_EQ(result[0].outputs, "10\n18");
}

TEST(ParseTestCases, MultiLineStringIO) {
  std::vector<test_case> result = parse_test_cases(json::parse(R"(
        [
            {
                "title": "This is a title",
                "description": "This is a description",
                "inputs": [
                  "3",
                  "3",
                  "6",
                  "1"
                ],
                "outputs": [
                  "10",
                  "18"
                ]
            }
        ]
    )"));

  EXPECT_EQ(result[0].inputs, "3\n3\n6\n1");
  EXPECT_EQ(result[0].outputs, "10\n18");
}

TEST(ParseTestCases, MultiLineNumberIO) {
  std::vector<test_case> result = parse_test_cases(json::parse(R"(
        [
            {
                "title": "This is a title",
                "description": "This is a description",
                "inputs": [
                  3,
                  3,
                  6,
                  1
                ],
                "outputs": [
                  10,
                  18
                ]
            }
        ]
    )"));

  EXPECT_EQ(result[0].inputs, "3\n3\n6\n1");
  EXPECT_EQ(result[0].outputs, "10\n18");
}

TEST(ParseTestCases, MultiLineOtherIO) {
  std::vector<test_case> result = parse_test_cases(json::parse(R"(
        [
            {
                "title": "This is a title",
                "description": "This is a description",
                "inputs": [
                  [
                    3,
                    3,
                    6,
                    1
                  ]
                ],
                "outputs": [
                  [
                    10,
                    18
                  ]
                ]
            }
        ]
    )"));

  // It does not parse anything other than numbers and strings
  EXPECT_EQ(result[0].inputs, "");
  EXPECT_EQ(result[0].outputs, "");
}