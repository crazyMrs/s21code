#include "viewer_model.h"

#include <algorithm>
#include <cstring>
#include <fstream>

namespace s21 {

bool WrappedArray::operator<(const WrappedArray& rhs) const {
  return (this->value[0] < rhs.value[0]) ||
         (this->value[0] == rhs.value[0] && this->value[1] < rhs.value[1]);
}

BodyData::BodyData()
    : vertices_(), amount_vertices_(0), polygons_(), amount_polygons_(0) {}

ViewerModel::ViewerModel() {}

void ViewerModel::AttachObserver(Observer* observer) {
  list_observer_.push_back(observer);
}

void ViewerModel::DetachObserver(Observer* observer) {
  list_observer_.remove(observer);
}

void ViewerModel::NotifyObserver() {
  for (std::list<Observer*>::iterator it = list_observer_.begin();
       it != list_observer_.end(); ++it) {
    (*it)->OnUpdate();
  }
}

const BodyData& ViewerModel::GetData() const noexcept { return data_; }

void ViewerModel::MoveCoordinate(const s21::Axis& axis, const int& moving) {
  float change = (moving - prev_moving_[axis]) * 0.01;
  size_t index = data_.vertices_.size();
  for (size_t i{}; i != index; i += 3) {
    data_.vertices_[i + axis] += change;
  }
  prev_moving_[axis] = moving;

  NotifyObserver();
}

void ViewerModel::СhangeScale(const int& coefficient) {
  float change = (coefficient / last_coefficient_);
  if (change < 1e-6f)
    throw S21OperationException("Ошибка при попытке задать размер.");
  size_t index = data_.vertices_.size();
  for (size_t i{}; i != index; ++i) {
    data_.vertices_[i] *= change;
  }
  last_coefficient_ = coefficient;
  NotifyObserver();
}

void ViewerModel::RotateCoordinate(const Axis& axis, const int& number) {
  switch (axis) {
    case xAxis:
      SetStrategy(&rotate_x_);
      break;
    case yAxis:
      SetStrategy(&rotate_y_);
      break;
    default:
      SetStrategy(&rotate_z_);
      break;
  }
  UseStrategy(data_.vertices_, number);
  NotifyObserver();
}

// Getter

void ViewerModel::ClearAll() {
  rotate_x_.UpdateLast(0);
  rotate_y_.UpdateLast(0);
  rotate_z_.UpdateLast(0);

  for (int i{}; i != 3; ++i) prev_moving_[i] = 0.;

  last_coefficient_ = 100;

  data_.vertices_.clear();
  data_.amount_vertices_ = 0;

  data_.polygons_.clear();
  data_.amount_polygons_ = 0;

  for (int i{}; i != 6; ++i) {
    if (i % 2)
      data_.highs_[i] = std::numeric_limits<float>::min();
    else
      data_.highs_[i] = std::numeric_limits<float>::max();
  }
}

template <typename T>
T ViewerModel::ConverterNumber(
    const char* subline, size_t& index) {  // Тут проверка на целостность числа
  T result{};
  int is_negative = 1;
  int degree{};
  int check_p{};
  if (subline[index] == '-') {
    is_negative = -1;
    ++index;
  }
  if (!isdigit(subline[index])) throw S21OperationException("Битый файл.");
  while (isdigit(subline[index]) || subline[index] == '.') {
    switch (subline[index]) {
      case '.':
        check_p += 1;
        break;
      default:
        if (check_p) ++degree;
        result *= 10.;
        result += subline[index] - 48;
        break;
    }
    ++index;
  }
  if (check_p > 1) throw S21OperationException("Битый файл.");
  while (degree-- != 0) result /= 10.;
  while (subline[index] != ' ' && subline[index] != '\0') ++index;
  return result * is_negative;
}

void ViewerModel::TranslationVertex(const char* line) {
  int count{};
  for (size_t i{}; i != strlen(line); ++i) {
    if (count == 3) break;
    if (line[i] == '-' || isdigit(line[i]) || line[i] == '.') {
      data_.vertices_.push_back(ConverterNumber<float>(line, i));
      if (line[i] == '\0') --i;
      ++count;
    }
  }
  if (count < 3) throw S21VertexParseException("Битый файл.");
  ++data_.amount_vertices_;
}

void ViewerModel::TranslationPolygon(const char* line,
                                     std::set<WrappedArray>& array) {
  int count{};
  std::vector<int> v;
  for (size_t i{}; i != strlen(line); ++i) {
    if (line[i] == '-' || isdigit(line[i])) {
      int number = ConverterNumber<int>(line, i);
      if (number < 0) {
        number += data_.amount_vertices_;
      } else
        number -= 1;
      if (number < 0) {
        throw S21PolygonParseException("Error f");
      }
      ++count;
      v.push_back(number);
      if (line[i] == '\0') --i;
    }
  }
  if (count == 1) throw S21PolygonParseException("Битый файл.");

  count = 0;
  WrappedArray arr;
  for (auto it : v) {
    arr.value[count++] = it;
    if (count == 2) {
      WrappedArray copy = arr;
      if (copy.value[0] > copy.value[1])
        std::swap(copy.value[0], copy.value[1]);
      array.insert(copy);
      arr.value[0] = arr.value[1];
      --count;
    }
  }
  arr.value[1] = v.front();
  if (arr.value[0] > arr.value[1]) std::swap(arr.value[0], arr.value[1]);
  array.insert(arr);
}

void ViewerModel::SearchingEnds() {
  for (size_t i{}; i != data_.amount_vertices_; ++i) {
    int index{};
    while (index != 3) {
      if (data_.vertices_[i * 3 + index] < data_.highs_[index * 2])
        data_.highs_[index * 2] = data_.vertices_[i * 3 + index];
      else if ((data_.vertices_[i * 3 + index] > data_.highs_[index * 2 + 1]))
        data_.highs_[index * 2 + 1] = data_.vertices_[i * 3 + index];
      ++index;
    }
  }
}

void ViewerModel::FindingEdges(const std::set<WrappedArray>& array) {
  for (auto it : array) {
    data_.polygons_.push_back(it.value[0]);
    data_.polygons_.push_back(it.value[1]);
  }
  data_.amount_polygons_ = data_.polygons_.size();
}

void ViewerModel::TranslationResult(const std::string& filename) {
  std::ifstream in_file(filename);
  if (!in_file.is_open())
    throw S21OpeningFileException("Указанного файла не существует.");
  ClearAll();

  std::string line;
  std::set<WrappedArray> array;

  while (getline(in_file, line)) {
    if (line[0] == 'v' && line[1] == ' ')
      TranslationVertex(line.data());
    else if (line[0] == 'f' && line[1] == ' ')
      TranslationPolygon(line.data(), array);
  }
  in_file.close();

  SearchingEnds();
  FindingEdges(array);

  float maxAbsValue = -INFINITY;
  for (int i{}; i != 6; ++i) {
    if (abs(data_.highs_[i]) > maxAbsValue) maxAbsValue = data_.highs_[i];
  }
  float scale_factor = maxAbsValue > 1.0f ? 1.0f / maxAbsValue : maxAbsValue;

  for (int i{}; i != 3; ++i) {
    data_.center_[i] = (data_.highs_[i * 2] + data_.highs_[i * 2 + 1]) / 2.f;
    for (size_t j{}; j != data_.amount_vertices_; ++j)
      data_.vertices_[j * 3 + i] =
          (data_.vertices_[j * 3 + i] - data_.center_[i]) * scale_factor;
    data_.highs_[i * 2] =
        (data_.highs_[i * 2] - data_.center_[i]) * scale_factor;
    data_.highs_[i * 2 + 1] =
        (data_.highs_[i * 2 + 1] - data_.center_[i]) * scale_factor;
  }

  NotifyObserver();  // Уведомим всех о изменении объекта
}

void ViewerModel::SetStrategy(Strategy* v) { operation_ = v; }

void ViewerModel::UseStrategy(std::vector<float>& v, const int& value) {
  operation_->UseStrategy(v, value);
}

}  // namespace s21
