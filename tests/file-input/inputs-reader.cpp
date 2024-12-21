#include <file-input/inputs-reader.h>

#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <zeus/expected.hpp>

#include "gtest/gtest.h"
#include "stdio.h"

using namespace nlohmann::literals;
using json = nlohmann::json;
// using namespace fio;

// parse_io()
namespace {
TEST(ParseIO, EmptyString) {
  zeus::expected<std::string, std::string> result =
      fio::internal::parse_io(json::parse(R"(
      "")"));

  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, "");
}

TEST(ParseIO, SpacedString) {
  zeus::expected<std::string, std::string> result =
      fio::internal::parse_io(json::parse(R"("a b $ d")"));

  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, "a b $ d");
}

TEST(ParseIO, SpacedNumerics) {
  zeus::expected<std::string, std::string> result =
      fio::internal::parse_io(json::parse(R"("1 2 3.14 4")"));

  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, "1 2 3.14 4");
}

TEST(ParseIO, NewLinedString) {
  zeus::expected<std::string, std::string> result =
      fio::internal::parse_io(json::parse(R"("a\nb\n$\nd")"));

  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, "a\nb\n$\nd");
}

TEST(ParseIO, NewLinedNumerics) {
  zeus::expected<std::string, std::string> result =
      fio::internal::parse_io(json::parse(R"("1\n2\n3.14\n4")"));

  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, "1\n2\n3.14\n4");
}

TEST(ParseIO, ArrayedString) {
  zeus::expected<std::string, std::string> result =
      fio::internal::parse_io(json::parse(R"(
    [
      "1",
      "2.1",
      "c",
      "$"
    ]
  )"));

  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, "1\n2.1\nc\n$");
}

TEST(ParseIO, ArrayedNumerics) {
  zeus::expected<std::string, std::string> result =
      fio::internal::parse_io(json::parse(R"([
      1,
      2.1,
      3,
      4
    ])"));

  EXPECT_TRUE(result.has_value());
  EXPECT_EQ(*result, "1\n2.1\n3\n4");
}
}  // namespace

// parse_test_cas()
namespace {
TEST(ParseTestCase, EmptyContents) {}
}  // namespace

// parse_test_cases()
namespace {
TEST(ParseTestCases, SingleLineIO) {
  std::vector<fio::test_case> result =
      fio::internal::parse_test_cases(json::parse(R"(
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
  std::vector<fio::test_case> result =
      fio::internal::parse_test_cases(json::parse(R"(
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
  std::vector<fio::test_case> result =
      fio::internal::parse_test_cases(json::parse(R"(
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

TEST(ParseTestCases, MultiLineNumberFloatIO) {
  std::vector<fio::test_case> result =
      fio::internal::parse_test_cases(json::parse(R"(
        [
            {
                "title": "This is a title",
                "description": "This is a description",
                "inputs": [
                  3.0,
                  3.1,
                  6.2,
                  1.3
                ],
                "outputs": [
                  10.4,
                  18.5
                ],

                "outputType": "float",
                "round": 2
            }
        ]
    )"));

  EXPECT_EQ(result[0].inputs, "3.0\n3.1\n6.2\n1.3");
  EXPECT_EQ(result[0].outputs, "10.4\n18.5");
}

TEST(ParseTestCases, MultiLineNumberFloatRoundIO) {
  std::vector<fio::test_case> result =
      fio::internal::parse_test_cases(json::parse(R"(
        [
            {
                "title": "This is a title",
                "description": "This is a description",
                "inputs": [
                  3.0,
                  3.1,
                  6.2,
                  1.3
                ],
                "outputs": [
                  10.4,
                  18.5
                ],

                "outputType": "float",
                "round": 1
            }
        ]
    )"));

  EXPECT_EQ(result[0].inputs, "3.0\n3.1\n6.2\n1.3");
  EXPECT_EQ(result[0].outputs, "10.4\n18.5");
}

TEST(ParseTestCases, MultiLineOtherIO) {
  std::vector<fio::test_case> result =
      fio::internal::parse_test_cases(json::parse(R"(
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
}  // namespace
