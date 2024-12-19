// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "test.h"

#include <carla/ListView.h>

#include <array>
#include <cstring>
#include <list>
#include <set>
#include <string>
#include <vector>

using carla::MakeListView;

template <typename Iterator>
static void TestSequence(carla::ListView<Iterator> view) {
  int count = 0;
  for (auto &&x : view) {
    ASSERT_EQ(x, count);
    ++count;
  }
  ASSERT_EQ(count, 6);
}

TEST(listview, sequence) {
  // 定义一个整数数组，并初始化为 {0, 1, 2, 3, 4, 5}
  int array[] = {0, 1, 2, 3, 4, 5};
  // 使用 MakeListView 创建视图，并传递给 TestSequence 进行测试
  TestSequence(MakeListView(array));
  // 定义一个 std::array<int, 6> 类型的数组，并初始化为 {0, 1, 2, 3, 4, 5}
  std::array<int, 6u> std_array = {0, 1, 2, 3, 4, 5};
  // 使用 MakeListView 创建视图，并传递给 TestSequence 进行测试
  TestSequence(MakeListView(std_array));
  // 定义一个 std::vector<int> 类型的向量，并初始化为 {0, 1, 2, 3, 4, 5}
  std::vector<int> vector = {0, 1, 2, 3, 4, 5};
  // 使用 MakeListView 创建视图，并传递给 TestSequence 进行测试
  TestSequence(MakeListView(vector));
  // 定义一个 std::list<int> 类型的列表，并初始化为 {0, 1, 2, 3, 4, 5}
  std::list<int> list = {0, 1, 2, 3, 4, 5};
  // 使用 MakeListView 创建视图，并传递给 TestSequence 进行测试
  TestSequence(MakeListView(list));
  // 定义一个 std::set<int> 类型的集合，并初始化为 {0, 1, 2, 3, 4, 5}
  std::set<int> set = {0, 1, 2, 3, 4, 5};
  // 使用 MakeListView 创建视图，并传递给 TestSequence 进行测试
  TestSequence(MakeListView(set));
}

TEST(listview, string) {
  std::string str = "Hello list view!";
  std::string result;
  for (char c : MakeListView(str)) {
    result += c;
  }
  ASSERT_EQ(result, str);
  char hello[6u] = {0};
  auto begin = std::begin(hello);
  for (char c : MakeListView(str.begin(), str.begin() + 5u)) {
    *begin = c;
    ++begin;
  }
  ASSERT_EQ(std::strcmp(hello, "Hello"), 0);
}
