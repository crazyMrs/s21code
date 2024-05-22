#ifndef S21_VIEWER_V20_INTERFACES_OBSERVER_OBSERVER_INTERFACE_H_
#define S21_VIEWER_V20_INTERFACES_OBSERVER_OBSERVER_INTERFACE_H_

namespace s21 {
class Observer {
 public:
  virtual ~Observer() = default;

  virtual void OnUpdate() = 0;
};

class Subject {
 public:
  virtual ~Subject() = default;

  virtual void AttachObserver(Observer *observer) = 0;
  virtual void DetachObserver(Observer *observer) = 0;
  virtual void NotifyObserver() = 0;
};
}  // namespace s21

#endif  // S21_VIEWER_V20_INTERFACES_OBSERVER_OBSERVER_INTERFACE_H_