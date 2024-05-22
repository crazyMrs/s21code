#ifndef CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_MODEL_H
#define CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_MODEL_H

#include <list>
#include <set>
#include <string>
#include <vector>

#include "observer/observer_inteface.h"
#include "strategy/strategy.h"
#include "viewer_exception.h"

namespace s21 {

struct WrappedArray {
  bool operator<(const WrappedArray& rhs) const;

  int value[2];
};

typedef struct BodyData {
  BodyData();
  ~BodyData() = default;

  std::vector<float> vertices_;
  size_t amount_vertices_;
  std::vector<int> polygons_;
  size_t amount_polygons_;
  float highs_[6];
  float center_[3];
} BodyData;

enum Axis { xAxis, yAxis, zAxis };
// Нужно передать название пути до файла(если файл не найден, то вернем throw)
class ViewerModel : private Subject, protected Context {
 public:
  ViewerModel();
  ViewerModel(const ViewerModel& other) = delete;
  ViewerModel(ViewerModel&& other) = delete;
  ViewerModel& operator=(const ViewerModel& other) = delete;
  ViewerModel& operator=(ViewerModel&& other) = delete;
  ~ViewerModel() = default;

  // Strategy
  void UseStrategy(std::vector<float>& v, const int& value) override;
  void SetStrategy(Strategy* v) override;

  // Для паттерна
  void AttachObserver(Observer* observer) override;
  void DetachObserver(Observer* observer) override;
  void NotifyObserver() override;
  // Getter
  const BodyData& GetData() const noexcept;

  // Result
  void TranslationResult(const std::string& filename);
  void FindingEdges(const std::set<WrappedArray>& array);
  void SearchingEnds();

  // Методы для изменения состояния
  void MoveCoordinate(const Axis& axis, const int& moving);
  void СhangeScale(const int& coefficient);
  void RotateCoordinate(const Axis& axis, const int& number);

 private:
  void ClearAll();
  template <typename T>
  T ConverterNumber(const char* subline, size_t& index);
  void TranslationVertex(const char* line);
  void TranslationPolygon(const char* line, std::set<WrappedArray>& array);

  BodyData data_;
  std::list<Observer*> list_observer_;

  RotateX rotate_x_;
  RotateY rotate_y_;
  RotateZ rotate_z_;
  float prev_moving_[3];
  float last_coefficient_;
};

}  // namespace s21

#endif  // CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_MODEL_H
