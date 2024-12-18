#include "gtest/gtest.h"
#include <nlohmann/json.hpp>
#include "fstream"

using json = nlohmann::json;

TEST(JsonLib, readArr) {
    std::ifstream f("tests/file-input/test-arr.json");
    ASSERT_FALSE(!f) << "File could not be loaded\n";

    json data = json::parse(f); // will throw if there is a parse error

    EXPECT_EQ(data[0]["title"], "foo");
    EXPECT_EQ(data[0]["desc"], "bar");

    EXPECT_EQ(data[1]["title"], "hello");
    EXPECT_EQ(data[1]["desc"], "world");
}

TEST(JsonLib, readObj) {
    std::ifstream f("tests/file-input/test-obj.json");
    ASSERT_FALSE(!f) << "File could not be loaded\n";
    
    json data = json::parse(f);

    // Test even
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(data["even"][i], i*2);
    }

    // Test odd
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(data["odd"][i], i*2 + 1);
    }

    // Test squares
    for (int i = 1; i < 5; i++) {
        EXPECT_EQ(data["squares"][i-1], i*i);
    }
}