#include "cc/roomba/serial_port.h"

#include <fcntl.h>
#include <unistd.h>

namespace roomba {

namespace {
int ModeToInt(SerialPort::Mode mode) {
  switch (mode) {
    case SerialPort::READ:
      return O_RDONLY;
    case SerialPort::WRITE:
      return O_WRONLY;
    case SerialPort::READ_AND_WRITE:
      return O_RDWR;
    default:
      return -1;
  }
}
} // namespace 

Error SerialPort::Open(const std::string& path, Mode mode) {
  int raw_mode = ModeToInt(mode);
  ERROR_IF(raw_mode == -1, "Invalid mode given.");
  fd_ = open(path.c_str(), raw_mode | O_CREAT, S_IRUSR | S_IWUSR);
  CHECK_SYSCALL(fd_, "Open failed");
  return Error::Success();
}

Error SerialPort::Read(void* buffer, size_t *amount_written, size_t size) {
  CHECK_HANDLE(fd_);
  *amount_written = read(fd_, buffer, size);
  CHECK_SYSCALL(*amount_written, "Read failed");
  return Error::Success();
}

Error SerialPort::Write(void* buffer, size_t size) {
  CHECK_HANDLE(fd_);
  CHECK_SYSCALL(write(fd_, buffer, size), "Write failed");
  return Error::Success();
}

Error SerialPort::Close() {
  CHECK_HANDLE(fd_);
  CHECK_SYSCALL(close(fd_), "Close failed");
  return Error::Success();
}

} // namespace roomba
