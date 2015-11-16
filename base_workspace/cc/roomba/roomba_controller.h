#ifndef ROOMBA_ROOMBA_CONTROLLER_H_
#define ROOMBA_ROOMBA_CONTROLLER_H_

#include <cstdint>
#include <memory>
#include <vector>
#include "cc/roomba/error.h"
#include "cc/roomba/serial_port.h"

namespace roomba {

class RoombaController {
 public:
  enum class Command : uint8_t {
    START = 128,
    SAFE = 131,
    FULL = 132,
    DEMO = 136,
    DRIVE = 137,
    DRIVE_DIRECT = 145,
    LEDS = 139,
    PLAY_SONG = 141,
  };

  RoombaController(std::unique_ptr<SerialPort> serial_port);

  Error Start() { return SendCommand(Command::START, {}); }

  Error Safe() { return SendCommand(Command::SAFE, {}); }

  Error Full() { return SendCommand(Command::FULL, {}); }

  Error Demo(uint8_t demo_number) {
    return SendCommand(Command::DEMO, {demo_number});
  }

  Error Drive(int16_t velocity, int16_t radius) {
    uint8_t velocity_lsb = static_cast<uint8_t>(velocity);
    uint8_t velocity_msb = static_cast<uint8_t>(velocity >> 8);
    uint8_t radius_lsb = static_cast<uint8_t>(radius);
    uint8_t radius_msb = static_cast<uint8_t>(radius >> 8);
    std::vector<uint8_t> args = {
      velocity_msb, velocity_lsb, radius_msb, radius_lsb
    };
    return SendCommand(Command::DRIVE, args);
  }

  Error PlaySong(uint8_t song_number) {
    return SendCommand(Command::PLAY_SONG, {song_number});
  }

  Error SendCommand(Command command, const std::vector<uint8_t>& data);

 private:
  std::unique_ptr<SerialPort> serial_port_;
};

} // namespace roomba

#endif // ROOMBA_ROOMBA_CONTROLLER_H_
