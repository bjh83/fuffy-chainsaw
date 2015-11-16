#ifndef ROOMBA_SERIAL_PORT_H_
#define ROOMBA_SERIAL_PORT_H_

#include <termios.h>
#include <unistd.h>

#include <string>
#include "cc/roomba/error.h"

namespace roomba {

class SerialPort {
 public:
  enum Mode {
    READ,
    WRITE,
    READ_AND_WRITE
  };

  ~SerialPort() { Close(); }

  Error Open(const std::string& path, Mode mode);

  virtual Error Read(void* buffer, size_t* amount_written, size_t size);

  virtual Error Write(void* buffer, size_t size);

  virtual Error SetBaudRate(speed_t baud_rate);

  virtual Error Close();

  template<typename T>
  Error Read(T* value) {
    size_t amount_written = 0;
    return Read(reinterpret_cast<void*>(value), &amount_written, sizeof(T));
  }

  template<typename T>
  Error Write(const T& value) {
    return Write(reinterpret_cast<void*>(const_cast<T*>(&value)), sizeof(T));
  }

 private:
  int fd_ = -1;
};

} // namespace roomba

#define CHECK_HANDLE(handle) ERROR_IF_NOT(handle >= 0, "File object is not open")

#endif // ROOMBA_SERIAL_PORT_H_
