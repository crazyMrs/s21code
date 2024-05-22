#ifndef CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_CONTROLLER_H
#define CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_CONTROLLER_H

#include "viewer_model.h"

namespace s21 {
class ViewerController {
 public:
  static ViewerController& Instance() {
    static ViewerController theSingleInstance;
    return theSingleInstance;
  }

  // Setter
  void SetModel(ViewerModel* model);

  void ChangeScale(const int& value);
  void MoveCoordinate(const s21::Axis& axis, const int& moving);
  void RotateCoordinate(const Axis& axis, const int& number);
  // Getter
  const BodyData& GetData() const noexcept;

  // Result
  void TranslateResult(const std::string& filename);

 private:
  ViewerController();
  ViewerController(const ViewerController& other) = delete;
  ViewerController(ViewerController&& other) = delete;
  ViewerController& operator=(const ViewerController& other) = delete;
  ViewerController& operator=(ViewerController&& other) = delete;
  ~ViewerController() = default;

  ViewerModel* viewer_model_;
};
}  // namespace s21

#endif  // CPP4_S21_VIEWER_V20_SRC_VIEWER_VIEWER_CONTROLLER_H
