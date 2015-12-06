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
    DRIVE = 137,
    DRIVE_DIRECT = 145,
    LEDS = 139,
    SONG = 140,
    PLAY_SONG = 141,
    SENSORS = 142,
  };

  enum class PacketID : uint8_t {
    BUMP_AND_WHEEL_DROP = 7,
    WALL = 8,
    CLIFF_LEFT = 9,
    CLIFF_FRONT_LEFT = 10,
    CLIFF_FRONT_RIGHT = 11,
    CLIFF_RIGHT = 12,
    VIRTUAL_WALL = 13,
    DISTANCE = 19,
    ANGLE = 20,
    IS_SONG_PLAYING = 37,
  };

  struct BumpAndWheelDropResponse {
    bool wheel_drop_caster;
    bool wheel_drop_left;
    bool wheel_drop_right;
    bool bump_left;
    bool bump_rignt;
  };

  RoombaController(std::unique_ptr<SerialPort> serial_port);

  Error Start();

  Error Safe();

  Error Full();

  Error Drive(int16_t velocity, int16_t radius);

  Error DriveDirect(int16_t left_velocity, int16_t right_velocity);

  Error SetSong(uint8_t song_number, const std::vector<uint8_t>& song_data);

  Error PlaySong(uint8_t song_number);

  Error ReadSensor(PacketID sensor_id, std::vector<uint8_t>* response);

  Error ReadBumpsAndWheelDropsSensor(BumpAndWheelDropResponse* response);

  Error ReadWall(bool* is_wall_present);

  Error ReadCliffLeft(bool* is_cliff_present);

  Error ReadCliffFrontLeft(bool* is_cliff_present);

  Error ReadCliffFrontRight(bool* is_cliff_present);

  Error ReadCliffRight(bool* is_cliff_present);

  Error ReadVirtualWall(bool* is_wall_present);

  Error IsSongPlaying(bool* is_song_playing);

  Error ReadDistance(int16_t* distance);

  Error ReadAngle(int16_t* degrees);

  Error SendCommand(Command command, const std::vector<uint8_t>& data);

  Error ReadResponse(std::vector<uint8_t>* response);

 private:
  std::unique_ptr<SerialPort> serial_port_;

  Error ReadSensorWithBoolResponse(PacketID sensor_id, bool* response);
};

} // namespace roomba

#endif // ROOMBA_ROOMBA_CONTROLLER_H_
