#include "gtest/gtest.h"
// #include "viewer/viewer_model.h"
#include "viewer/viewer_model.cc"

TEST(OpenFileTest, error_test_1) {
  s21::ViewerModel model;
  EXPECT_ANY_THROW(model.TranslationResult("hello.y"));
};

TEST(OpenFileTest, error_test_2) {
  s21::ViewerModel model;
  model.TranslationResult("obj_files/cube.obj");
  EXPECT_ANY_THROW(model.СhangeScale(0));
};

TEST(OpenFileTest, error_test_3) {
  s21::ViewerModel model;
  EXPECT_ANY_THROW(model.TranslationResult("obj_files/cube_error.obj"));
};

TEST(OpenFileTest, error_test_4) {
  s21::ViewerModel model;
  EXPECT_ANY_THROW(model.TranslationResult("obj_files/cube_error_2.obj"));
};

TEST(OpenFileTest, test_1) {
  s21::ViewerModel model;
  model.TranslationResult("obj_files/cube.obj");
  size_t true_AmountP = 36;
  size_t true_AmountV = 8;
  EXPECT_EQ(model.GetData().amount_polygons_, true_AmountP);
  EXPECT_EQ(model.GetData().amount_vertices_, true_AmountV);
};

TEST(OpenFileTest, test_2) {
  s21::ViewerModel model;
  model.TranslationResult("obj_files/cube.obj");
  model.СhangeScale(150);
  size_t i{};
  float arr[24] = {-1.5, -1.5, 1.5, 1.5, -1.5, 1.5,  1.5,  1.5,
                   1.5,  -1.5, 1.5, 1.5, -1.5, -1.5, -1.5, 1.5,
                   -1.5, -1.5, 1.5, 1.5, -1.5, -1.5, 1.5,  -1.5};
  for (auto it : model.GetData().vertices_) {
    EXPECT_FLOAT_EQ(arr[i++], it);
  }
};

TEST(OpenFileTest, test_3) {
  s21::ViewerModel model;

  model.TranslationResult("obj_files/cube.obj");
  model.RotateCoordinate(s21::xAxis, 100);
  size_t i{};
  float arr[24] = {-1, 1.15846,  0.81116,  1,  1.15846,  0.81116,
                   1,  0.81116,  -1.15846, -1, 0.81116,  -1.15846,
                   -1, -0.81116, 1.15846,  1,  -0.81116, 1.15846,
                   1,  -1.15846, -0.81116, -1, -1.15846, -0.81116};
  for (auto it : model.GetData().vertices_) {
    EXPECT_NEAR(arr[i++], it, 1e-5);
  }
};

TEST(OpenFileTest, test_4) {
  s21::ViewerModel model;

  model.TranslationResult("obj_files/cube.obj");
  model.RotateCoordinate(s21::yAxis, 100);
  size_t i{};
  float arr[24] = {1.15846,  -1, 0.81116,  0.81116,  -1, -1.15846,
                   0.81116,  1,  -1.15846, 1.15846,  1,  0.81116,
                   -0.81116, -1, 1.15846,  -1.15846, -1, -0.81116,
                   -1.15846, 1,  -0.81116, -0.81116, 1,  1.15846};
  for (auto it : model.GetData().vertices_) {
    EXPECT_NEAR(arr[i++], it, 1e-5);
  }
};

TEST(OpenFileTest, test_5) {
  s21::ViewerModel model;
  model.TranslationResult("obj_files/cube.obj");
  model.RotateCoordinate(s21::zAxis, 100);
  size_t i{};
  float arr[24] = {-0.81116, 1.15846,  1,  -1.15846, -0.81116, 1,
                   0.81116,  -1.15846, 1,  1.15846,  0.81116,  1,
                   -0.81116, 1.15846,  -1, -1.15846, -0.81116, -1,
                   0.81116,  -1.15846, -1, 1.15846,  0.81116,  -1};
  for (auto it : model.GetData().vertices_) {
    EXPECT_NEAR(arr[i++], it, 1e-5);
  }
};

TEST(OpenFileTest, test_6) {
  s21::ViewerModel model;

  model.TranslationResult("obj_files/cube.obj");
  model.MoveCoordinate(s21::xAxis, 100);
  size_t i{};
  float arr[24] = {0, -1, 1,  2, -1, 1,  2, 1, 1,  0, 1, 1,
                   0, -1, -1, 2, -1, -1, 2, 1, -1, 0, 1, -1};
  for (auto it : model.GetData().vertices_) {
    EXPECT_FLOAT_EQ(arr[i++], it);
  }
};

TEST(OpenFileTest, test_7) {
  s21::ViewerModel model;

  model.TranslationResult("obj_files/cube.obj");
  model.MoveCoordinate(s21::yAxis, 100);
  size_t i{};
  float arr[24] = {-1, 0, 1,  1, 0, 1,  1, 2, 1,  -1, 2, 1,
                   -1, 0, -1, 1, 0, -1, 1, 2, -1, -1, 2, -1};
  for (auto it : model.GetData().vertices_) {
    EXPECT_FLOAT_EQ(arr[i++], it);
  }
};

TEST(OpenFileTest, test_8) {
  s21::ViewerModel model;

  model.TranslationResult("obj_files/cube.obj");
  model.MoveCoordinate(s21::zAxis, 100);
  size_t i{};
  float arr[24] = {-1, -1, 2, 1, -1, 2, 1, 1, 2, -1, 1, 2,
                   -1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0};
  for (auto it : model.GetData().vertices_) {
    EXPECT_FLOAT_EQ(arr[i++], it);
  }
};

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
