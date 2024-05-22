#include "viewer_controller.h"

namespace s21 {
ViewerController::ViewerController() : viewer_model_(nullptr) {}
void ViewerController::SetModel(ViewerModel *model) { viewer_model_ = model; }

// Getter
const BodyData &ViewerController::GetData() const noexcept {
  return viewer_model_->GetData();
}
// Change
void ViewerController::ChangeScale(const int &value) {
  viewer_model_->СhangeScale(value);
}

void ViewerController::MoveCoordinate(const s21::Axis &axis,
                                      const int &moving) {
  viewer_model_->MoveCoordinate(axis, moving);
}

void ViewerController::RotateCoordinate(const Axis &axis, const int &number) {
  viewer_model_->RotateCoordinate(axis, number);
}

// Result
void ViewerController::TranslateResult(const std::string &filename) {
  viewer_model_->TranslationResult(filename);
}

}  // namespace s21
