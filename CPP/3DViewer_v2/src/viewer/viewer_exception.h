#include <stdexcept>

namespace s21 {

class S21ViewException : public std::runtime_error {
 public:
  explicit S21ViewException(const char* arg) : runtime_error(arg){};
  virtual ~S21ViewException() = default;
};

class S21OpeningFileException : public S21ViewException {
 public:
  explicit S21OpeningFileException(const char* arg) : S21ViewException(arg){};
  virtual ~S21OpeningFileException() = default;
};

class S21VertexParseException : public S21ViewException {
 public:
  explicit S21VertexParseException(const char* arg) : S21ViewException(arg){};
  virtual ~S21VertexParseException() = default;
};

class S21PolygonParseException : public S21ViewException {
 public:
  explicit S21PolygonParseException(const char* arg) : S21ViewException(arg){};
  virtual ~S21PolygonParseException() = default;
};

class S21OperationException : public S21ViewException {
 public:
  explicit S21OperationException(const char* arg) : S21ViewException(arg){};
  virtual ~S21OperationException() = default;
};

}  // namespace s21