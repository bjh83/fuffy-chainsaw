#include "cc/roomba/roomba_controller.h"

#include <unistd.h>

#include <cstdint>

namespace roomba {

using std::unique_ptr;
using std::vector;

RoombaController::RoombaController(unique_ptr<SerialPort> serial_port) 
    : serial_port_(std::move(serial_port)) {}

Error RoombaController::SendCommand(Command command, const vector<uint8_t>& data) {
  CHECK_ERROR(serial_port_->Write<uint8_t>(static_cast<uint8_t>(command)));
  CHECK_ERROR(serial_port_->Write(const_cast<uint8_t*>(data.data()), data.size()));
  return Error::Success();
}
} // namespace roomba
