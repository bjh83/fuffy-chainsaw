#ifndef ROOMBA_ROOMBA_CONTROLLER_H_
#define ROOMBA_ROOMBA_CONTROLLER_H_

#include <cstdint>
#include <memory>
#include "cc/roomba/error.h"
#include "cc/roomba/serial_port.h"

namespace roomba {

class RoombaController {
 public:
  enum class Command : uint8_t {
    START = 128,
  };

  RoombaController(std::unique_ptr<SerialPort> serial_port);

  Error SendCommand(Command command);

 private:
  std::unique_ptr<SerialPort> serial_port_;
};

} // namespace roomba

#endif // ROOMBA_ROOMBA_CONTROLLER_H_
