#include "cc/roomba/roomba_controller.h"

#include <cstdint>

namespace roomba {

using std::unique_ptr;

RoombaController::RoombaController(unique_ptr<SerialPort> serial_port) 
    : serial_port_(std::move(serial_port)) {}

Error RoombaController::SendCommand(Command command) {
  return serial_port_->Write<uint8_t>(static_cast<uint8_t>(command));
}
} // namespace roomba
