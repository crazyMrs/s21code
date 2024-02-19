#include <gtest/gtest.h>

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <vector>

#include "s21_containers.h"
#include "s21_containersplus.h"

////////////////////////////////////
//              multiset          //
////////////////////////////////////

TEST(MultisetTest, DefaultConstruction) {
  s21::multiset<int> M;
  std::multiset<int> M2;
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, InitListConstruction) {
  s21::multiset<int> M{1, 2, 3};
  std::multiset<int> M2{1, 2, 3};
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MultisetTest, InitListConstruction2) {
  s21::multiset<std::string> M{"A", "B", "C"};
  std::multiset<std::string> M2{"A", "B", "C"};
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MultisetTest, ConstructionCopy) {
  s21::multiset<std::string> Copy_M{"A", "B", "C"};
  s21::multiset<std::string> M(Copy_M);
  std::multiset<std::string> Copy_M2{"A", "B", "C"};
  std::multiset<std::string> M2(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MultisetTest, ConstructionCopy2) {
  s21::multiset<std::string> Copy_M{"A", "B", "C", "SFS", "SFSF", "J", "R"};
  s21::multiset<std::string> M(Copy_M);
  std::multiset<std::string> Copy_M2{"A", "B", "C", "SFS", "SFSF", "J", "R"};
  std::multiset<std::string> M2(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MultisetTest, ConstructionMove) {
  s21::multiset<std::string> Copy_M{"A", "B", "C"};
  s21::multiset<std::string> M(std::move(Copy_M));
  std::multiset<std::string> Copy_M2{"A", "B", "C"};
  std::multiset<std::string> M2(std::move(Copy_M2));
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MultisetTest, ConstructionOperatorMove) {
  s21::multiset<std::string> Copy_M{"A", "B", "C"};
  s21::multiset<std::string> M = std::move(Copy_M);
  std::multiset<std::string> Copy_M2{"A", "B", "C"};
  std::multiset<std::string> M2 = std::move(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MultisetTest, Begin) {
  s21::multiset<std::string> M{"A", "B", "C", "S21LOVE"};
  std::multiset<std::string> M2{"A", "B", "C", "S21LOVE"};
  auto it = M.begin();
  auto it2 = M2.begin();
  ASSERT_EQ(*it, *it2);
}

TEST(MultisetTest, End) {
  s21::multiset<std::string> M{"A", "B", "C", "S21LOVE"};
  std::multiset<std::string> M2{"A", "B", "C", "S21LOVE"};
  auto it = M.end();
  auto it2 = M2.end();
  ASSERT_EQ(*--it, *--it2);
}

TEST(MultisetTest, Empty) {
  s21::multiset<std::string> M{"A", "B", "C", "S21LOVE"};
  std::multiset<std::string> M2{"A", "B", "C", "S21LOVE"};
  ASSERT_EQ(M.empty(), M2.empty());
}

TEST(MultisetTest, Empty2) {
  s21::multiset<std::string> M;
  M.insert("Hehe");
  M.insert("Baba");
  M.clear();
  std::multiset<std::string, int> M2;
  ASSERT_EQ(M.empty(), M2.empty());
}

TEST(MultisetTest, Size) {
  s21::multiset<std::string> M;
  std::multiset<std::string> M2;
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, Size2) {
  s21::multiset<std::string> M;
  std::multiset<std::string> M2;
  M.insert("Hehe");
  M2.insert("Hehe");
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, Size3) {
  s21::multiset<std::string> M;
  std::multiset<std::string> M2;
  M.insert("Hehe");
  M2.insert("Hehe");
  M.clear();
  M2.clear();
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, MaxSize) {
  s21::multiset<std::string> M;
  std::multiset<std::string> M2;
  ASSERT_EQ(M.max_size(), M2.max_size());
}

TEST(MultisetTest, Clear) {
  s21::multiset<std::string> M;
  std::multiset<std::string> M2;
  M.clear();
  M2.clear();
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, Clear2) {
  s21::multiset<int> M{1, 2, 3, 3};
  std::multiset<int> M2{1, 2, 3, 3};
  M2.clear();
  M.clear();
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, Insert) {
  s21::multiset<int> M{1, 2, 3};
  std::multiset<int> M2{1, 2, 3};
  M.insert(10);
  M2.insert(10);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MultisetTest, Insert2) {
  s21::multiset<int> M{1, 2, 3, 5};
  std::multiset<int> M2{1, 2, 3, 5};
  auto res = M.insert(8);
  auto res2 = M2.insert(8);
  ASSERT_EQ(*(res.first), *(res2));
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> M{1, 55, 56};
  std::multiset<int> M2{1, 55, 56};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, Erase2) {
  s21::multiset<int> M{1};
  std::multiset<int> M2{1};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, Erase3) {
  s21::multiset<int> M{1, 2};
  std::multiset<int> M2{1, 2};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, Erase4) {
  s21::multiset<int> M{1, 55, 56, 33, 22, 54, 66, 897, 7567, -232};
  std::multiset<int> M2{1, 55, 56, 33, 22, 54, 66, 897, 7567, -232};
  auto itr2 = ++M2.begin();
  ++itr2;
  auto itr = ++M.begin();
  ++itr;
  M.erase(itr);
  M2.erase(itr2);
  itr2 = --M2.end();
  itr = --M.end();
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MultisetTest, Swap) {
  s21::multiset<int> M;
  s21::multiset<int> M_second;
  M.insert(1);
  M_second.insert(2);
  std::multiset<int> M2;
  std::multiset<int> M2_second;
  M2.insert(1);
  M2_second.insert(2);
  M.swap(M_second);
  M2.swap(M2_second);
  ASSERT_EQ(*M.begin(), 2);
  ASSERT_EQ(*M_second.begin(), 1);
  ASSERT_EQ(*M2.begin(), 2);
  ASSERT_EQ(*M2_second.begin(), 1);
}

TEST(MultisetTest, Merge) {
  s21::multiset<int> M;
  s21::multiset<int> M_test{7};
  s21::multiset<int> M_result{7};
  M.merge(M_test);
  ASSERT_EQ(M.size(), 1);
  ASSERT_EQ(M.empty(), false);
}

TEST(MultisetTest, Merge2) {
  s21::multiset<int> M;
  s21::multiset<int> M_test;
  s21::multiset<int> M_result;
  M.merge(M_test);
  ASSERT_EQ(M.size(), 0);
  ASSERT_EQ(M.empty(), true);
}

TEST(MultisetTest, Merge3) {
  s21::multiset<int> M{1};
  s21::multiset<int> M_test{2,   3,     1,      400, 32,      5435, 22,
                            324, 65675, 756756, 45,  3435435, -1};
  s21::multiset<int> M_test_result;
  M.merge(M_test);
  ASSERT_EQ(M.size(), 14);
  ASSERT_EQ(M.empty(), false);
  ASSERT_EQ(M_test_result.size(), M_test.size());
  ASSERT_EQ(M_test_result.empty(), M_test.empty());
}

TEST(MultisetTest, Merge4) {
  s21::multiset<int> M{1, -2, -4, 31};
  s21::multiset<int> M_test{8, 2, 3, 39, 1, 43, 657, 6768, 7965};
  std::multiset<int> M2{1, -2, -4, 31};
  std::multiset<int> M2_test{8, 2, 3, 39, 1, 43, 657, 6768, 7965};
  M.merge(M_test);
  M2.merge(M2_test);
  ASSERT_EQ(M2.size(), M.size());
  ASSERT_EQ(M2.empty(), M.empty());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M2_test.size(), M_test.size());
  ASSERT_EQ(M2_test.empty(), M_test.empty());
  auto it3 = M2_test.begin();
  auto it4 = M_test.begin();
  for (; it4 != M_test.end(); ++it4) {
    ASSERT_EQ(*it3++, *it4);
  }
}

TEST(MultisetTest, Count) {
  s21::multiset<int> M{1, 1, 1, 1, 2, 2, 2, 2, 6, 7, 8, 9};
  s21::multiset<int> M2{1, 1, 1, 1, 2, 2, 2, 2, 6, 7, 8, 9};
  ASSERT_EQ(M.size(), M2.size());
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.count(1), M2.count(1));
}

TEST(MultisetTest, EqualRange) {
  s21::multiset<int> M{7, 7, 7, 7, 1, 1, 1, 1, 2, 2, 2, 2, 6, 7, 8, 9};
  std::multiset<int> M2{7, 7, 7, 7, 1, 1, 1, 1, 2, 2, 2, 2, 6, 7, 8, 9};
  ASSERT_EQ(M.size(), M2.size());
  ASSERT_EQ(M.empty(), M2.empty());
  auto res = M.equal_range(1);
  auto res2 = M2.equal_range(1);
  for (; res.first != res.second; ++res.first) {
    ASSERT_EQ(*res.first, *(res2.first++));
  }
  ASSERT_EQ(*res.first, *res2.first);
}

TEST(MultisetTest, MultisetInsertMany) {
  s21::multiset<int> S;
  S.insert_many(1, 1, 2, 3, 4, 5, 6);
  s21::multiset<int> result{1, 1, 2, 3, 4, 5, 6};
  ASSERT_EQ(result.size(), S.size());
}

////////////////////////////////////
//             VECTOR             //
////////////////////////////////////

TEST(VectorTest, DefaultСonstructor) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest, СonstructorSetSize) {
  s21::vector<int> Vector(10);
  std::vector<int> Vector2(10);
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest, СonstructorInitializerList) {
  s21::vector<int> Vector{1, 2, 3, 4, 5};
  std::vector<int> Vector2{1, 2, 3, 4, 5};
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
  std::vector<int>::iterator it2 = Vector2.begin();
  for (s21::vector<int>::iterator it = Vector.begin(); it != Vector.end();
       it++) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(VectorTest, СonstructorCopy) {  // выполнить проверку на тот же тип
  s21::vector<int> Copy_Vector{1, 2, 3, 4, 5};
  s21::vector<int> Vector(Copy_Vector);
  std::vector<int> Copy_Vector2{1, 2, 3, 4, 5};
  std::vector<int> Vector2(Copy_Vector2);
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
  std::vector<int>::iterator it2 = Vector2.begin();
  for (s21::vector<int>::iterator it = Vector.begin(); it != Vector.end();
       it++) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(VectorTest, СonstructorMove) {
  s21::vector<int> Copy_Vector{1, 2, 3, 4, 5};
  s21::vector<int> Vector(std::move(Copy_Vector));
  std::vector<int> Copy_Vector2{1, 2, 3, 4, 5};
  std::vector<int> Vector2(std::move(Copy_Vector2));
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
  std::vector<int>::iterator it2 = Vector2.begin();
  for (s21::vector<int>::iterator it = Vector.begin(); it != Vector.end();
       it++) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(VectorTest, OperatorEq) {  // КОПИРУЮЩИЙ КОНСТРУКТОР
  s21::vector<int> Copy_Vector{1, 2, 3, 4, 5};
  s21::vector<int> Vector = std::move(Copy_Vector);
  std::vector<int> Copy_Vector2{1, 2, 3, 4, 5};
  std::vector<int> Vector2 = std::move(Copy_Vector2);
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
  std::vector<int>::iterator it2 = Vector2.begin();
  for (s21::vector<int>::iterator it = Vector.begin(); it != Vector.end();
       it++) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(VectorTest, At) {
  s21::vector<int> Vector{0, 10, 20, 30, 40};
  std::vector<int> Vector2{0, 10, 20, 30, 40};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector.at(i), Vector2.at(i));
  }
}

TEST(VectorTest, OperatorBrackets) {
  s21::vector<int> Vector{0, 10, 20, 30, 40};
  std::vector<int> Vector2{0, 10, 20, 30, 40};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector[i], Vector2[i]);
  }
}

TEST(VectorTest, Front) {
  s21::vector<int> Vector{0, 10, 20, 30, 40};
  std::vector<int> Vector2{0, 10, 20, 30, 40};
  ASSERT_EQ(Vector.front(), Vector2.front());
}

TEST(VectorTest, Back) {
  s21::vector<int> Vector{0, 10, 20, 30, 40};
  std::vector<int> Vector2{0, 10, 20, 30, 40};
  ASSERT_EQ(Vector.back(), Vector2.back());
}

TEST(VectorTest, Data) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.data(), Vector2.data());
}

TEST(VectorTest, Data2) {
  s21::vector<int> Vector{1, 2, 3, 4, 5, 666, 333, 444};
  std::vector<int> Vector2{1, 2, 3, 4, 5, 666, 333, 444};
  for (size_t i = 0; i < Vector.size(); ++i) {
    ASSERT_EQ(Vector.data()[i], Vector2.data()[i]);
  }
}

TEST(VectorTest, Empty) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest, Empty2) {
  s21::vector<int> Vector{1};
  std::vector<int> Vector2{1};
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest, Empty3) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  Vector.reserve(1);
  Vector2.reserve(1);
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest, Size) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest, Size2) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest, MaxSize) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.max_size(), Vector2.max_size());
}

TEST(VectorTest, Reserve) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  Vector.reserve(0);
  Vector2.reserve(0);
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest, Reserve2) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  Vector.reserve(6);
  Vector2.reserve(6);
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
  auto i2 = Vector.begin();
  for (auto i = Vector.begin(); i != Vector.end(); ++i) {
    ASSERT_EQ(*i, *i2++);
  }
}

TEST(VectorTest, Capacity) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest, Capacity2) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest, ShrinkToFit) {
  s21::vector<int> Vector{1, 2, 3, 4, 5};
  std::vector<int> Vector2{1, 2, 3, 4, 5};
  Vector.reserve(10);
  Vector2.reserve(10);
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest, ShrinkToFit2) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest, Begin) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  ASSERT_EQ(*(Vector.begin()), *(Vector2.begin()));
}

TEST(VectorTest, End) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  ASSERT_EQ(*(--Vector.end()), *(--Vector2.end()));
}

TEST(VectorTest, Clear) {
  s21::vector<int> Vector{5, 6, 7};
  std::vector<int> Vector2{5, 6, 7};
  Vector.clear();
  Vector2.clear();
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest, Insert) {
  s21::vector<int> Vector{5, 6, 7};
  std::vector<int> Vector2{5, 6, 7};
  auto it = Vector.cbegin();
  auto it2 = Vector2.cbegin();
  ++it, ++it2;
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  auto it4 = Vector2.cbegin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest, Insert2) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  auto it = Vector.cbegin();
  auto it2 = Vector2.cbegin();
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  auto it4 = Vector2.cbegin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest, Insert3) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  auto it = Vector.cend();
  auto it2 = Vector2.cend();
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  it = Vector.cend();
  it2 = Vector2.cend();
  Vector.insert(it, 67);
  Vector2.insert(it2, 67);
  auto it4 = Vector2.cbegin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest, Erase) {
  s21::vector<int> Vector{21, 22, 23, 22, 21};
  std::vector<int> Vector2{21, 22, 23, 22, 21};
  auto it = Vector.begin();
  auto it2 = Vector2.begin();
  Vector2.erase(it2);
  Vector.erase(it);
  auto it4 = Vector2.begin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest, PushBack) {
  s21::vector<int> Vector{21, 22, 23, 22, 21};
  std::vector<int> Vector2{21, 22, 23, 22, 21};
  Vector2.push_back(1);
  Vector.push_back(1);
  auto it4 = Vector2.begin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest, Swap) {
  s21::vector<int> Vector{21, 22, 23, 22, 21, 1};
  s21::vector<int> Copy_Vector{21, 22, 23, 22, 21, 1};
  s21::vector<int> Vector2{15, 1};
  s21::vector<int> Copy_Vector2{15, 1};

  Vector.swap(Copy_Vector2);
  Vector2.swap(Copy_Vector);

  auto it1 = Copy_Vector.begin();
  for (s21::vector<int>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }

  auto it4 = Copy_Vector2.begin();
  for (s21::vector<int>::iterator it3 = Vector2.begin(); it3 != Vector2.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), 2);
  ASSERT_EQ(Vector2.size(), 6);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> Vector{21, 22, 23, 22, 21, 1};
  std::vector<int> Vector_Ans{21, 22, 23, 22, 21, 1, 2, 3, 4};
  Vector.insert_many_back(2, 3, 4);
  auto it1 = Vector_Ans.begin();
  for (s21::vector<int>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> Vector{21, 22, 23, 22, 21, 1};
  std::vector<int> Vector_Ans{21, 22, 23, 22, 21, 1, 2, 3, 4};
  auto it = Vector.cend();
  Vector.insert_many(it, 2, 3, 4);
  auto it1 = Vector_Ans.begin();
  for (s21::vector<int>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
}

TEST(VectorTest, InsertMany2) {
  s21::vector<int> Vector{21, 22, 23, 22, 21, 1};
  std::vector<int> Vector_Ans{21, 22, 23, 22, 21, 2, 3, 4, 1};
  s21::vector<int>::const_iterator it = --(Vector.cend());
  Vector.insert_many(it, 2, 3, 4);
  auto it1 = Vector_Ans.begin();
  for (s21::vector<int>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
}

////////////////////////////////////
//              set               //
////////////////////////////////////

TEST(SetTest, DefaultConstruction) {
  s21::set<int> M;
  std::set<int> M2;
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, InitListConstruction) {
  s21::set<int> M{1, 2, 3};
  std::set<int> M2{1, 2, 3};
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(SetTest, InitListConstruction2) {
  s21::set<std::string> M{"A", "B", "C"};
  std::set<std::string> M2{"A", "B", "C"};
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(SetTest, ConstructionCopy) {
  s21::set<std::string> Copy_M{"A", "B", "C"};
  s21::set<std::string> M(Copy_M);
  std::set<std::string> Copy_M2{"A", "B", "C"};
  std::set<std::string> M2(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(SetTest, ConstructionCopy2) {
  s21::set<std::string> Copy_M{"A", "B", "C", "SFS", "SFSF", "J", "R"};
  s21::set<std::string> M(Copy_M);
  std::set<std::string> Copy_M2{"A", "B", "C", "SFS", "SFSF", "J", "R"};
  std::set<std::string> M2(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(SetTest, ConstructionMove) {
  s21::set<std::string> Copy_M{"A", "B", "C"};
  s21::set<std::string> M(std::move(Copy_M));
  std::set<std::string> Copy_M2{"A", "B", "C"};
  std::set<std::string> M2(std::move(Copy_M2));
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(SetTest, ConstructionOperatorMove) {
  s21::set<std::string> Copy_M{"A", "B", "C"};
  s21::set<std::string> M = std::move(Copy_M);
  std::set<std::string> Copy_M2{"A", "B", "C"};
  std::set<std::string> M2 = std::move(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(SetTest, Begin) {
  s21::set<std::string> M{"A", "B", "C", "S21LOVE"};
  std::set<std::string> M2{"A", "B", "C", "S21LOVE"};
  auto it = M.begin();
  auto it2 = M2.begin();
  ASSERT_EQ(*it, *it2);
}

TEST(SetTest, End) {
  s21::set<std::string> M{"A", "B", "C", "S21LOVE"};
  std::set<std::string> M2{"A", "B", "C", "S21LOVE"};
  auto it = M.end();
  auto it2 = M2.end();
  ASSERT_EQ(*--it, *--it2);
}

TEST(SetTest, Empty) {
  s21::set<std::string> M{"A", "B", "C", "S21LOVE"};
  std::set<std::string> M2{"A", "B", "C", "S21LOVE"};
  ASSERT_EQ(M.empty(), M2.empty());
}

TEST(SetTest, Empty2) {
  s21::set<std::string> M;
  M.insert("Hehe");
  M.insert("Baba");
  M.clear();
  std::set<std::string, int> M2;
  ASSERT_EQ(M.empty(), M2.empty());
}

TEST(SetTest, Size) {
  s21::set<std::string> M;
  std::set<std::string> M2;
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, Size2) {
  s21::set<std::string> M;
  std::set<std::string> M2;
  M.insert("Hehe");
  M2.insert("Hehe");
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, Size3) {
  s21::set<std::string> M;
  std::set<std::string> M2;
  M.insert("Hehe");
  M2.insert("Hehe");
  M.clear();
  M2.clear();
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, MaxSize) {
  s21::set<std::string> M;
  std::set<std::string> M2;
  ASSERT_EQ(M.max_size(), M2.max_size());
}

TEST(SetTest, Clear) {
  s21::set<std::string> M;
  std::set<std::string> M2;
  M.clear();
  M2.clear();
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, Clear2) {
  s21::set<int> M{1, 2, 3, 3};
  std::set<int> M2{1, 2, 3, 3};
  M2.clear();
  M.clear();
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, Insert) {
  s21::set<int> M{1, 2, 3};
  std::set<int> M2{1, 2, 3};
  M.insert(10);
  M2.insert(10);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(SetTest, Insert2) {
  s21::set<int> M{1, 2, 3, 5};
  std::set<int> M2{1, 2, 3, 5};
  auto res = M.insert(8);
  auto res2 = M2.insert(8);
  ASSERT_EQ((*(res.first)), (*(res2.first)));
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(SetTest, Erase) {
  s21::set<int> M{1, 55, 56};
  std::set<int> M2{1, 55, 56};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, Erase2) {
  s21::set<int> M{1};
  std::set<int> M2{1};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, Erase3) {
  s21::set<int> M{1, 2};
  std::set<int> M2{1, 2};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, Erase4) {
  s21::set<int> M{1, 55, 56, 33, 22, 54, 66, 897, 7567, -232};
  std::set<int> M2{1, 55, 56, 33, 22, 54, 66, 897, 7567, -232};
  auto itr2 = ++M2.begin();
  ++itr2;
  auto itr = ++M.begin();
  ++itr;
  M.erase(itr);
  M2.erase(itr2);
  itr2 = --M2.end();
  itr = --M.end();
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(SetTest, Swap) {
  s21::set<int> M;
  s21::set<int> M_second;
  M.insert(1);
  M_second.insert(2);
  std::set<int> M2;
  std::set<int> M2_second;
  M2.insert(1);
  M2_second.insert(2);
  M.swap(M_second);
  M2.swap(M2_second);
  ASSERT_EQ(*M.begin(), 2);
  ASSERT_EQ(*M_second.begin(), 1);
  ASSERT_EQ(*M2.begin(), 2);
  ASSERT_EQ(*M2_second.begin(), 1);
}

TEST(SetTest, Merge) {
  s21::set<int> M;
  s21::set<int> M_test{7};
  s21::set<int> M_result{7};
  M.merge(M_test);
  ASSERT_EQ(M.size(), 1);
  ASSERT_EQ(M.empty(), false);
}

TEST(SetTest, Merge2) {
  s21::set<int> M;
  s21::set<int> M_test;
  s21::set<int> M_result;
  M.merge(M_test);
  ASSERT_EQ(M.size(), 0);
  ASSERT_EQ(M.empty(), true);
}

TEST(SetTest, Merge3) {
  s21::set<int> M{1};
  s21::set<int> M_test{2,   3,     1,      400, 32,      5435, 22,
                       324, 65675, 756756, 45,  3435435, -1};
  s21::set<int> M_test_result{1};
  M.merge(M_test);
  ASSERT_EQ(M.size(), 13);
  ASSERT_EQ(M.empty(), false);
  ASSERT_EQ(M_test_result.size(), M_test.size());
  ASSERT_EQ(M_test_result.empty(), M_test.empty());
}

TEST(SetTest, Merge4) {
  s21::set<int> M{1, -2, -4, 31};
  s21::set<int> M_test{8, 2, 3, 39, 1, 43, 657, 6768, 7965};
  std::set<int> M2{1, -2, -4, 31};
  std::set<int> M2_test{8, 2, 3, 39, 1, 43, 657, 6768, 7965};
  M.merge(M_test);
  M2.merge(M2_test);
  ASSERT_EQ(M2.size(), M.size());
  ASSERT_EQ(M2.empty(), M.empty());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M2_test.size(), M_test.size());
  ASSERT_EQ(M2_test.empty(), M_test.empty());
  auto it3 = M2_test.begin();
  auto it4 = M_test.begin();
  for (; it4 != M_test.end(); ++it4) {
    ASSERT_EQ(*it3++, *it4);
  }
}

TEST(SetTest, InsertMany) {
  s21::set<int> S;
  S.insert_many(1, 2, 3, 4, 5, 6);
  s21::set<int> result{1, 2, 3, 4, 5, 6};
  ASSERT_EQ(result.size(), S.size());
}

////////////////////////////////////
//              MAP               //
////////////////////////////////////

TEST(MapTest, DefaultConstruction) {
  s21::map<int, int> M;
  std::map<int, int> M2;
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTest, InitListConstruction) {
  s21::map<int, int> M{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> M2{{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, InitListConstruction2) {
  s21::map<std::string, int> M{{"A", 1}, {"B", 2}, {"C", 3}};
  std::map<std::string, int> M2{{"A", 1}, {"B", 2}, {"C", 3}};
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, ConstructionCopy) {
  s21::map<std::string, int> Copy_M{{"A", 1}, {"B", 2}, {"C", 3}};
  s21::map<std::string, int> M(Copy_M);
  std::map<std::string, int> Copy_M2{{"A", 1}, {"B", 2}, {"C", 3}};
  std::map<std::string, int> M2(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, ConstructionCopy2) {
  s21::map<std::string, int> Copy_M{{"A", 1},   {"B", 2},    {"C", 3},
                                    {"SFS", 4}, {"SFSF", 4}, {"J", 65}};
  s21::map<std::string, int> M(Copy_M);
  std::map<std::string, int> Copy_M2{{"A", 1},   {"B", 2},    {"C", 3},
                                     {"SFS", 4}, {"SFSF", 4}, {"J", 65}};
  std::map<std::string, int> M2(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, ConstructionMove) {
  s21::map<std::string, int> Copy_M{{"A", 1}, {"B", 2}, {"C", 3}};
  s21::map<std::string, int> M(std::move(Copy_M));
  std::map<std::string, int> Copy_M2{{"A", 1}, {"B", 2}, {"C", 3}};
  std::map<std::string, int> M2(std::move(Copy_M2));
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, ConstructionOperatorMove) {
  s21::map<std::string, int> Copy_M{{"A", 1}, {"B", 2}, {"C", 3}};
  s21::map<std::string, int> M = std::move(Copy_M);
  std::map<std::string, int> Copy_M2{{"A", 1}, {"B", 2}, {"C", 3}};
  std::map<std::string, int> M2 = std::move(Copy_M2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, ConstructionOperatorCopy) {
  s21::map<std::string, int> Copy_M{{"A", 1}, {"B", 2}, {"C", 3}};
  s21::map<std::string, int> M = Copy_M;
  std::map<std::string, int> Copy_M2{{"A", 1}, {"B", 2}, {"C", 3}};
  std::map<std::string, int> M2 = Copy_M2;
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, At) {
  s21::map<std::string, int> M{{"A", 1}, {"B", 2}, {"C", 3}};
  std::map<std::string, int> M2{{"A", 1}, {"B", 2}, {"C", 3}};
  ASSERT_EQ(M.at("A"), M2.at("A"));
  M.at("A") = 999;
  M2.at("A") = 999;
  ASSERT_EQ(M.at("A"), M2.at("A"));
}

TEST(MapTest, At2) {
  s21::map<std::string, int> M{{"A", 1}, {"B", 2}, {"C", 3}, {"S21LOVE", 777}};
  std::map<std::string, int> M2{{"A", 1}, {"B", 2}, {"C", 3}, {"S21LOVE", 777}};
  ASSERT_ANY_THROW(M.at("K"));
  ASSERT_ANY_THROW(M2.at("K"));
}

TEST(MapTest, OperatorBrackets) {
  s21::map<std::string, int> M{{"A", 1}, {"B", 2}, {"C", 3}, {"S21LOVE", 777}};
  std::map<std::string, int> M2{{"A", 1}, {"B", 2}, {"C", 3}, {"S21LOVE", 777}};
  ASSERT_EQ(M["S21LOVE"], M2["S21LOVE"]);
  M["D"] = 15;
  M2["D"] = 15;
  ASSERT_EQ(M["D"], M2["D"]);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, Begin) {
  s21::map<std::string, int> M{{"A", 1}, {"B", 2}, {"C", 3}, {"S21LOVE", 777}};
  std::map<std::string, int> M2{{"A", 1}, {"B", 2}, {"C", 3}, {"S21LOVE", 777}};
  auto it = M.begin();
  auto it2 = M2.begin();
  ASSERT_EQ(*it, *it2);
}

TEST(MapTest, Empty) {
  s21::map<std::string, int> M{{"A", 1}, {"B", 2}, {"C", 3}, {"S21LOVE", 777}};
  std::map<std::string, int> M2{{"A", 1}, {"B", 2}, {"C", 3}, {"S21LOVE", 777}};
  ASSERT_EQ(M.empty(), M2.empty());
}

TEST(MapTest, Empty2) {
  s21::map<std::string, int> M;
  M.insert({"Hehe", 21});
  M.clear();
  std::map<std::string, int> M2;
  ASSERT_EQ(M.empty(), M2.empty());
}

TEST(MapTest, Size) {
  s21::map<std::string, int> M;
  std::map<std::string, int> M2;
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTest, Size2) {
  s21::map<std::string, int> M;
  std::map<std::string, int> M2;
  M.insert({"Hehe", 21});
  M2.insert({"Hehe", 21});
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTest, Size3) {
  s21::map<std::string, int> M;
  std::map<std::string, int> M2;
  M.insert({"Hehe", 21});
  M2.insert({"Hehe", 21});
  M.clear();
  M2.clear();
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTestMap, MaxSize) {
  s21::map<std::string, int> M;
  std::map<std::string, int> M2;
  ASSERT_EQ(M.max_size(), M2.max_size());
}

TEST(MapTest, Clear) {
  s21::map<std::string, int> M;
  std::map<std::string, int> M2;
  M.clear();
  M2.clear();
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTest, Clear2) {
  s21::map<int, int> M{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> M2{{1, 1}, {2, 2}, {3, 3}};
  M.clear();
  M2.clear();
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTest, InsertPair) {
  s21::map<int, int> M{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> M2{{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTestMap, InsertPair2) {
  s21::map<int, int> M{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, int> M2{{1, 1}, {2, 2}, {3, 3}};

  auto res = M.insert({8, 8});
  auto res2 = M2.insert({8, 8});
  (*(res.first)).second = 4;
  (*(res2.first)).second = 4;
  ASSERT_EQ((*(res.first)).second, (*(res.first)).second);

  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, Insert) {
  s21::map<int, int> M{{1, 1}, {2, 2}, {3, 3}, {8, 8}};
  std::map<int, int> M2{{1, 1}, {2, 2}, {3, 3}, {8, 8}};

  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, int> M{{1, 1}, {2, 2}, {3, 3}, {8, 8}, {5, 5}, {12, 12}};
  std::map<int, int> M2{{1, 1}, {2, 2}, {3, 3}, {8, 8}, {5, 5}, {12, 12}};
  auto res = M.insert_or_assign(1, 10);
  auto res2 = M2.insert_or_assign(1, 10);
  ASSERT_EQ(res.second, res2.second);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, InsertOrAssign2) {
  s21::map<int, int> M;
  std::map<int, int> M2;
  auto res = M.insert_or_assign(10, 10);
  auto res2 = M2.insert_or_assign(10, 10);
  ASSERT_EQ(res.second, res2.second);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(MapTest, Erase) {
  s21::map<int, int> M{{1, 1}, {55, 55}};
  std::map<int, int> M2{{1, 1}, {55, 55}};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTest, Erase2) {
  s21::map<int, int> M{{1, 1}};
  std::map<int, int> M2{{1, 1}};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTest, Erase3) {
  s21::map<int, int> M{{1, 1},   {2, 2},       {3, 3},   {99, 99}, {55, 55},
                       {66, 66}, {-324, -324}, {-1, -1}, {56, 56}, {18, 18}};
  std::map<int, int> M2{{1, 1},   {2, 2},       {3, 3},   {99, 99}, {55, 55},
                        {66, 66}, {-324, -324}, {-1, -1}, {56, 56}, {18, 18}};
  auto itr2 = M2.begin();
  auto itr = M.begin();
  M.erase(itr);
  M2.erase(itr2);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  ASSERT_EQ(M.empty(), M2.empty());
  ASSERT_EQ(M.size(), M2.size());
}

TEST(MapTest, Swap) {
  s21::map<int, int> M;
  s21::map<int, int> M_second;
  M.insert(1, 1);
  M_second.insert(2, 2);
  std::map<int, int> M2;
  std::map<int, int> M2_second;
  M2.insert({1, 1});
  M2_second.insert({2, 2});
  M.swap(M_second);
  M2.swap(M2_second);
  ASSERT_EQ(M.at(2), 2);
  ASSERT_EQ(M_second.at(1), 1);
  ASSERT_EQ(M2.at(2), 2);
  ASSERT_EQ(M2_second.at(1), 1);
}

TEST(MapTest, Merge) {
  s21::map<int, int> M{{1, 1}, {-2, -2}, {-4, -4}, {31, 31}};
  s21::map<int, int> M_test{{8, 8}, {2, 2}, {3, 3}, {39, 39}, {1, 1}};
  std::map<int, int> M2{{1, 1}, {-2, -2}, {-4, -4}, {31, 31}};
  std::map<int, int> M2_test{{8, 8}, {2, 2}, {3, 3}, {39, 39}, {1, 1}};
  M.merge(M_test);
  M2.merge(M2_test);
  auto it2 = M2.begin();
  auto it = M.begin();
  for (; it != M.end(); ++it) {
    ASSERT_EQ(*it, *it2++);
  }
  auto it3 = M2_test.begin();
  auto it4 = M_test.begin();
  for (; it4 != M_test.end(); ++it4) {
    ASSERT_EQ(*it3++, *it4);
  }
}

TEST(MapTest, InsertMany) {
  s21::map<int, int> M;
  M.insert_many(std::make_pair(1, 1), std::make_pair(2, 2));
  ASSERT_EQ(2, M.size());
}

////////////////////////////////////
//             LIST               //
////////////////////////////////////

TEST(ListTest, DefaultConstructor) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  auto it_2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it_2, *it);
    ++it_2;
  }
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, InitListConstructor) {
  s21::list<int> s21_list{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto it_2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end();) {
    EXPECT_EQ(*it_2, *it);
    ++it;
    ++it_2;
  }
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, ParameterizedConstructor) {
  s21::list<int> s21_list(10);
  std::list<int> std_list(10);
  auto it_2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end();) {
    EXPECT_EQ(*it_2, *it);
    ++it;
    ++it_2;
  }
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> copy_s21_list{1, 2, 3, 4, 5};
  s21::list<int> s21_list(std::move(copy_s21_list));
  std::list<int> copy_std_list{1, 2, 3, 4, 5};
  std::list<int> std_list(std::move(copy_std_list));
  auto it_2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end();) {
    EXPECT_EQ(*it_2, *it);
    ++it;
    ++it_2;
  }
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(copy_s21_list.empty(), copy_std_list.empty());
  EXPECT_EQ(copy_s21_list.size(), copy_std_list.size());
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> copy_s21_list{1, 2, 3, 4, 5};
  s21::list<int> s21_list(copy_s21_list);
  std::list<int> copy_std_list{1, 2, 3, 4, 5};
  std::list<int> std_list(copy_std_list);
  auto it_2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end();) {
    EXPECT_EQ(*it_2, *it);
    ++it;
    ++it_2;
  }
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(copy_s21_list.empty(), copy_std_list.empty());
  EXPECT_EQ(copy_s21_list.size(), copy_std_list.size());
}

TEST(ListTest, EquallyConstructor) {
  s21::list<int> copy_s21_list{1, 2, 3, 4, 5};
  s21::list<int> s21_list = std::move(copy_s21_list);
  std::list<int> copy_std_list{1, 2, 3, 4, 5};
  std::list<int> std_list = std::move(copy_std_list);
  auto it_2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end();) {
    EXPECT_EQ(*it_2, *it);
    ++it;
    ++it_2;
  }
  EXPECT_EQ(s21_list.empty(), std_list.empty());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(copy_s21_list.empty(), copy_std_list.empty());
  EXPECT_EQ(copy_s21_list.size(), copy_std_list.size());
}

TEST(ListTest, Front) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list{1, 2, 3, 4};
  EXPECT_EQ(s21_list.front(), std_list.front());
  s21_list.push_front(77);
  std_list.push_front(77);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Back) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list{1, 2, 3, 4};
  EXPECT_EQ(s21_list.back(), std_list.back());
  s21_list.push_back(77);
  std_list.push_back(77);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Empty) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Empty2) {
  s21::list<int> s21_list{1, 2, 3, 4};
  std::list<int> std_list{1, 2, 3, 4};
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Size) {
  s21::list<int> s21_list = {1, 2, 3, 4, 7, 7, 7, 7};
  std::list<int> std_list{1, 2, 3, 4, 7, 7, 7, 7};
  EXPECT_EQ(std_list.size(), s21_list.size());
}

TEST(ListTest, MaxSize) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  EXPECT_EQ(std_list.max_size(), s21_list.max_size());
}

TEST(ListTest, Clear) {
  s21::list<int> s21_list = {1, 2, 3, 4, 7, 7, 7, 7};
  std::list<int> std_list{1, 2, 3, 4, 7, 7, 7, 7};
  s21_list.clear();
  std_list.clear();
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Insert) {
  s21::list<int> s21_list = {1, 2, 3, 4, 7, 7, 7, 7};
  std::list<int> std_list{1, 2, 3, 4, 7, 7, 7, 7};
  auto it = s21_list.end();
  auto it2 = std_list.end();
  --it;
  --it2;
  s21_list.insert(it, 77);
  std_list.insert(it2, 77);
  auto it4 = std_list.begin();
  for (auto it3 = s21_list.begin(); it3 != s21_list.end(); ++it3) {
    EXPECT_EQ(*it3, *(it4++));
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Erase) {
  s21::list<int> s21_list = {1, 2, 3, 4, 7, 7, 7, 7, 99};
  std::list<int> std_list{1, 2, 3, 4, 7, 7, 7, 7, 99};

  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());

  auto it = s21_list.end();
  auto it2 = std_list.end();
  --it;
  --it2;
  --it;
  --it2;

  s21_list.erase(it);
  std_list.erase(it2);

  auto it4 = std_list.begin();
  for (auto it3 = s21_list.begin(); it3 != s21_list.end(); ++it3) {
    EXPECT_EQ(*it3, *(it4++));
  }
}

TEST(ListTest, PushBack) {
  s21::list<int> s21_list = {1, 2, 3, 4, 7, 7, 7, 7, 99};
  std::list<int> std_list{1, 2, 3, 4, 7, 7, 7, 7, 99};
  s21_list.push_back(21);
  std_list.push_back(21);
  auto it2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, *(it2++));
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, PopBack) {
  s21::list<int> s21_list = {1, 2, 3, 4, 7, 7, 7, 7, 99};
  std::list<int> std_list{1, 2, 3, 4, 7, 7, 7, 7, 99};
  s21_list.pop_back();
  std_list.pop_back();
  auto it2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, *(it2++));
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, PushFront) {
  s21::list<int> s21_list = {1, 2, 3, 4, 7, 7, 7, 7, 99};
  std::list<int> std_list{1, 2, 3, 4, 7, 7, 7, 7, 99};
  s21_list.push_front(21);
  std_list.push_front(21);
  auto it2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, *(it2++));
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, PopFront) {
  s21::list<int> s21_list = {1, 2, 3, 4, 7, 7, 7, 7, 99};
  std::list<int> std_list{1, 2, 3, 4, 7, 7, 7, 7, 99};
  s21_list.pop_front();
  std_list.pop_front();
  auto it2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, *(it2++));
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Swap) {
  s21::list<int> copy_s21_list{1, 2, 3, 4, 7, 7, 7, 7, 99};
  std::list<int> copy_std_list{1, 2, 3, 4, 7, 7, 7, 7, 99};
  s21::list<int> s21_list;
  std::list<int> std_list;
  s21_list.swap(copy_s21_list);
  std_list.swap(copy_std_list);
  auto it2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, *(it2++));
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());

  auto it4 = copy_std_list.begin();
  for (auto it3 = copy_s21_list.begin(); it3 != copy_s21_list.end(); ++it3) {
    EXPECT_EQ(*it3, *(it4++));
  }
  EXPECT_EQ(copy_std_list.size(), copy_s21_list.size());
  EXPECT_EQ(copy_std_list.empty(), copy_s21_list.empty());
}

TEST(ListTest, Merge) {
  s21::list<int> copy_s21_list{1, 2, 3, 4, 7, 7, 7, 7, 99};
  std::list<int> copy_std_list{1, 2, 3, 4, 7, 7, 7, 7, 99};
  s21::list<int> s21_list{1, 2, 3, 88, 99};
  std::list<int> std_list{1, 2, 3, 88, 99};
  s21_list.merge(copy_s21_list);
  std_list.merge(copy_std_list);
  auto it2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, *(it2++));
  }
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());

  auto it4 = copy_std_list.begin();
  for (auto it3 = copy_s21_list.begin(); it3 != copy_s21_list.end(); ++it3) {
    EXPECT_EQ(*it3, *(it4++));
  }
  EXPECT_EQ(copy_std_list.size(), copy_s21_list.size());
  EXPECT_EQ(copy_std_list.empty(), copy_s21_list.empty());
}

TEST(ListTest, Reverse) {
  s21::list<int> s21_list{1, 2, 3, 4, 86};
  std::list<int> std_list{1, 2, 3, 4, 86};
  s21_list.reverse();
  std_list.reverse();
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());

  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Unique) {
  s21::list<int> s21_list{1, 1, 1, 1, 1, 2, 3, 4, 86};
  std::list<int> std_list{1, 1, 1, 1, 1, 2, 3, 4, 86};
  s21_list.unique();
  std_list.unique();
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Sort) {
  s21::list<int> s21_list{118, 22, 21, 45, 6, 3, 1, 2, 3, 4, 86};
  std::list<int> std_list{118, 22, 21, 45, 6, 3, 1, 2, 3, 4, 86};
  s21_list.sort();
  std_list.sort();
  auto it2 = std_list.begin();
  for (auto it = s21_list.begin(); it != s21_list.end(); ++it) {
    EXPECT_EQ(*it, *(it2++));
  }
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

TEST(ListTest, Splice) {
  s21::list<int> s21_list{118, 22, 21, 45, 6, 3, 1, 2, 3, 4, 86};
  std::list<int> std_list{118, 22, 21, 45, 6, 3, 1, 2, 3, 4, 86};
  s21::list<int> copy_s21_list{2, 226, 444};
  std::list<int> copy_std_list{2, 226, 444};
  s21_list.sort();
  std_list.sort();
  auto it = s21_list.begin();
  auto it2 = std_list.begin();
  it++;
  it2++;
  s21_list.splice(it, copy_s21_list);
  std_list.splice(it2, copy_std_list);
  auto it4 = std_list.begin();
  for (auto it3 = s21_list.begin(); it3 != s21_list.end(); ++it3) {
    EXPECT_EQ(*it3, *(it4++));
  }
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(std_list.size(), s21_list.size());
  EXPECT_EQ(std_list.empty(), s21_list.empty());
}

////////////////////////////////////
//            STACK               //
////////////////////////////////////

TEST(Stack, Constructor_Default) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.Empty(), std_stack.empty());
}

TEST(Stack, Constructor_List) {
  s21::stack<int> s21_stack;
  s21_stack.Push(1);
  s21_stack.Push(2);
  s21_stack.Push(3);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(s21_stack.Top(), std_stack.top());
}

TEST(Stack, Constructor_Copy) {
  s21::stack<int> s21_stack;
  s21_stack.Push(1);
  s21_stack.Push(2);
  s21_stack.Push(3);
  s21::stack<int> our_copy(s21_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  EXPECT_EQ(our_copy.Top(), std_copy.top());
}

TEST(Stack, Operator_Copy) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.Push(1);
  s21_stack_int.Push(2);
  s21_stack_int.Push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;
  s21_stack_empty = s21_stack_int;
  std_stack_empty = std_stack_int;
  EXPECT_EQ(s21_stack_empty.Top(), std_stack_empty.top());
  EXPECT_EQ(s21_stack_int.Empty(), std_stack_int.empty());
}

TEST(Stack, Constructor_Move) {
  s21::stack<int> s21_stack;
  s21_stack.Push(1);
  s21_stack.Push(2);
  s21_stack.Push(3);
  s21::stack<int> our_move(std::move(s21_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  EXPECT_EQ(our_move.Top(), std_move.top());
  EXPECT_EQ(s21_stack.Empty(), std_stack.empty());
}

TEST(Stack, Top) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.Push(1);
  s21_stack_int.Push(2);
  s21_stack_int.Push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<double> s21_stack_double;
  s21_stack_double.Push(1.1f);
  s21_stack_double.Push(2.1f);
  s21_stack_double.Push(3.1f);
  std::stack<double> std_stack_double;
  std_stack_double.push(1.1f);
  std_stack_double.push(2.1f);
  std_stack_double.push(3.1f);
  s21::stack<std::string> s21_stack_string;
  s21_stack_string.Push("abc");
  s21_stack_string.Push("def");
  s21_stack_string.Push("ghf");
  std::stack<std::string> std_stack_string;
  std_stack_string.push("abc");
  std_stack_string.push("def");
  std_stack_string.push("ghf");
  EXPECT_EQ(s21_stack_int.Top(), std_stack_int.top());
  EXPECT_EQ(s21_stack_double.Top(), std_stack_double.top());
  EXPECT_EQ(s21_stack_string.Top(), std_stack_string.top());
}

TEST(Stack, Empty) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.Push(1);
  s21_stack_int.Push(2);
  s21_stack_int.Push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(s21_stack_int.Empty(), std_stack_int.empty());
  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(s21_stack_empty.Empty(), std_stack_empty.empty());
}

TEST(Stack, Size) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.Push(1);
  s21_stack_int.Push(2);
  s21_stack_int.Push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(s21_stack_int.Size(), std_stack_int.size());
  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(s21_stack_empty.Size(), std_stack_empty.size());
}

TEST(Stack, Push) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.Push(1);
  s21_stack_int.Push(2);
  s21_stack_int.Push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(s21_stack_int.Top(), std_stack_int.top());
}

TEST(Stack, Pop) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.Push(1);
  s21_stack_int.Push(2);
  s21_stack_int.Push(3);
  s21_stack_int.Pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  std_stack_int.pop();
  EXPECT_EQ(s21_stack_int.Top(), std_stack_int.top());
  s21_stack_int.Pop();
  s21_stack_int.Pop();
  std_stack_int.pop();
  std_stack_int.pop();
  EXPECT_EQ(s21_stack_int.Empty(), std_stack_int.empty());
}

TEST(Stack, Swap) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.Push(1);
  s21_stack_int.Push(2);
  s21_stack_int.Push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::stack<int> s21_stack_empty;
  std::stack<int> std_stack_empty;
  s21_stack_empty.Swap(s21_stack_int);
  std_stack_empty.swap(std_stack_int);
  EXPECT_EQ(s21_stack_empty.Top(), std_stack_empty.top());
  EXPECT_EQ(s21_stack_int.Empty(), std_stack_int.empty());
}

TEST(Stack, InsertManyFront) {
  s21::stack<int> s21_stack_int;
  s21_stack_int.insert_many_front(1, 2, 3);
  EXPECT_EQ(s21_stack_int.Top(), 3);
}

////////////////////////////////////
//            QUEUE               //
////////////////////////////////////

TEST(QueueTest, DefaultConstructor) {
  s21::queue<int> q;
  EXPECT_TRUE(q.my_empty());
  EXPECT_EQ(q.my_size(), 0);
}

TEST(QueueTest, PushPop) {
  s21::queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);

  EXPECT_FALSE(q.my_empty());
  EXPECT_EQ(q.my_size(), 3);

  EXPECT_EQ(q.front(), 1);
  q.pop();
  EXPECT_EQ(q.front(), 2);

  q.pop();
  q.pop();
  EXPECT_TRUE(q.my_empty());
  EXPECT_EQ(q.my_size(), 0);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<int> q1;
  q1.push(1);
  q1.push(2);
  s21::queue<int> q2(q1);

  EXPECT_EQ(q2.front(), 1);
  q1.pop();
  EXPECT_EQ(q1.my_size(), 1);
  EXPECT_EQ(q2.my_size(), 2);
}

TEST(QueueTest, MoveConstructor) {
  s21::queue<int> q1;
  q1.push(1);
  q1.push(2);
  s21::queue<int> q2(std::move(q1));

  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q1.my_size(), 0);  // q1 был перемещен, поэтому должен быть пустым
  EXPECT_EQ(q2.my_size(), 2);
}

TEST(QueueTest, CopyAssignmentOperator) {
  s21::queue<int> q1;
  q1.push(1);
  q1.push(2);
  s21::queue<int> q2;
  q2 = q1;

  EXPECT_EQ(q2.front(), 1);
  q1.pop();
  EXPECT_EQ(q1.my_size(), 1);
  EXPECT_EQ(q2.my_size(), 2);
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<int> q1;
  q1.push(1);
  q1.push(2);
  s21::queue<int> q2;
  q2 = std::move(q1);

  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q1.my_size(), 0);
  EXPECT_EQ(q2.my_size(), 2);
}

////////////////////////////////////
//            ARRAY               //
////////////////////////////////////

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr = {0, 0, 0, 0, 0};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(arr.back(), 0);
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.size(), 4);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr.back(), 4);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 3> arr1 = {10, 20, 30};
  s21::array<int, 3> arr2(arr1);
  EXPECT_EQ(arr2.front(), 10);
  EXPECT_EQ(arr2.back(), 30);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 3> arr1 = {10, 20, 30};
  s21::array<int, 3> arr2(std::move(arr1));
  EXPECT_EQ(arr2.front(), 10);
  EXPECT_EQ(arr2.back(), 30);
  EXPECT_EQ(arr1.size(), 3);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 3> arr1 = {10, 20, 30};
  s21::array<int, 3> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.front(), 10);
  EXPECT_EQ(arr2.back(), 30);
  EXPECT_EQ(arr1.size(), 3);
}

TEST(ArrayTest, At) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, Swap) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = {4, 5, 6};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(42);
  EXPECT_EQ(arr.front(), 42);
  EXPECT_EQ(arr.back(), 42);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
