#include <file-input/parser.h>

#include "gtest/gtest.h"

TEST(HeadingTest, HeadingWithSpaces) {
  const std::string heading = "foo bar";
  const std::string line = "# " + heading;

  parse_result result = get_heading(line);
  EXPECT_TRUE(result.status);
  EXPECT_EQ(heading, result.data());
  EXPECT_EQ("", result.what());
}

TEST(HeadingTest, HeadingWithoutSpaces) {
  const std::string heading = "foo-bar";
  const std::string line = "#" + heading;

  parse_result result = get_heading(line);
  EXPECT_TRUE(result.status);
  EXPECT_EQ(heading, result.data());
  EXPECT_EQ("", result.what());
}

TEST(HeadingTest, EmptyInput) {
  parse_result result = get_heading("");
  EXPECT_FALSE(result.status);
  EXPECT_EQ("expected test case title", result.what());
  EXPECT_EQ("", result.data());
}

TEST(HeadingTest, SpecialCharsInput) {
  parse_result result = get_heading("$ ");
  EXPECT_FALSE(result.status);
  EXPECT_EQ("expected test case title", result.what());
  EXPECT_EQ("", result.data());
}

TEST(HeadingTest, EmptyHeadingWithoutSpace) {
  const std::string heading = "";
  const std::string line = "#" + heading;

  parse_result result = get_heading(line);
  EXPECT_TRUE(result.status);
  EXPECT_EQ(heading, result.data());
  EXPECT_EQ("", result.what());
}

TEST(HeadingTest, EmptyHeadingWithSpace) {
  const std::string heading = "";
  const std::string line = "# " + heading;

  parse_result result = get_heading(line);
  EXPECT_TRUE(result.status);
  EXPECT_EQ(heading, result.data());
  EXPECT_EQ("", result.what());
}