#include "cc/roomba/roomba_controller_factory.h"

#include "cc/roomba/config.h"
#include "cc/roomba/serial_port.h"

namespace roomba {
using std::unique_ptr;

Error BuildController(std::unique_ptr<RoombaController>* controller) {
  unique_ptr<SerialPort> serial_port(new SerialPort());
  CHECK_ERROR(serial_port->Open(kSerialPortPath, SerialPort::WRITE));
  CHECK_ERROR(serial_port->SetBaudRate(B115200));

  controller->reset(new RoombaController(std::move(serial_port)));
  return Error::Success();
}
} // namespace roomba
