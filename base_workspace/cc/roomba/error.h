#ifndef ROOMBA_ERROR_H_
#define ROOMBA_ERROR_H_

#include <cerrno>
#include <cstring>
#include <string>

namespace roomba {

class Error {
 public:
  Error(bool success, const std::string& message) 
      : success_(success), error_message_(message) {}

  static Error Success() {
    return Error(true, "success");
  }

  bool is_success() const { return success_; }

  const std::string& error_message() const { return error_message_; }

  operator bool() { return is_success(); }

 private:
  bool success_;
  std::string error_message_;
};

Error CreateError(std::string message, int line_number, std::string file_name);

Error CreateError(const Error& error, int line_number, std::string file_name);

} // namespace roomba

#define ERROR(message) return roomba::CreateError(message, __LINE__, __FILE__);

#define ERROR_IF(predicate, message) if (predicate) { ERROR(message) }

#define ERROR_IF_NOT(predicate, message) ERROR_IF(!(predicate), message)

#define CHECK_ERROR(error) { roomba::Error temp = error; ERROR_IF_NOT(temp, temp) }

#define CHECK_SYSCALL(result, message) \
    ERROR_IF_NOT(result >= 0, std::string(message) + ": " + strerror(errno))

#endif // ROOMBA_ERROR_H_
