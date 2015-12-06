#include "cc/roomba/roomba_controller.h"

#include <unistd.h>

#include <cstdint>

namespace roomba {

using std::unique_ptr;
using std::vector;

namespace {
uint8_t GetMSB(int16_t data) {
  return static_cast<uint8_t>(data >> 8);
}

uint8_t GetLSB(int16_t data) {
  return static_cast<uint8_t>(data);
}

int16_t Get16BitSigned(uint8_t msb, uint8_t lsb) {
  return (static_cast<uint16_t>(msb) << 8) | lsb;
}

bool GetBit(uint8_t byte, int bit) {
  return byte & (0b00000001 << bit);
}
} // namespace

RoombaController::RoombaController(unique_ptr<SerialPort> serial_port) 
    : serial_port_(std::move(serial_port)) {}

Error RoombaController::Start() { return SendCommand(Command::START, {}); }

Error RoombaController::Safe() { return SendCommand(Command::SAFE, {}); }

Error RoombaController::Full() { return SendCommand(Command::FULL, {}); }

Error RoombaController::Drive(int16_t velocity, int16_t radius) {
  std::vector<uint8_t> args = {
    GetMSB(velocity),
    GetLSB(velocity),
    GetMSB(radius),
    GetLSB(radius)
  };
  return SendCommand(Command::DRIVE, args);
}

Error RoombaController::DriveDirect(int16_t left_velocity, int16_t right_velocity) {
  std::vector<uint8_t> args = {
    GetMSB(right_velocity),
    GetLSB(right_velocity),
    GetMSB(left_velocity),
    GetLSB(left_velocity)
  };
  return SendCommand(Command::DRIVE_DIRECT, args);
}

Error RoombaController::SetSong(uint8_t song_number, const std::vector<uint8_t>& song_data) {
  // The data contains a note and duration, so half of it is the number of notes.
  uint8_t song_length = song_data.size() / 2;
  std::vector<uint8_t> data = {song_number, song_length};
  data.insert(data.end(), song_data.begin(), song_data.end());
  return SendCommand(Command::SONG, data);
}

Error RoombaController::PlaySong(uint8_t song_number) {
  return SendCommand(Command::PLAY_SONG, {song_number});
}

Error RoombaController::ReadSensor(PacketID sensor_id,
                                   std::vector<uint8_t>* response) {
  CHECK_ERROR(SendCommand(Command::SENSORS,
                          {static_cast<uint8_t>(sensor_id)}));
  CHECK_ERROR(ReadResponse(response));
  return Error::Success();
}

Error RoombaController::ReadBumpsAndWheelDropsSensor(
    BumpAndWheelDropResponse* response) {
  std::vector<uint8_t> response_vector(1);
  CHECK_ERROR(ReadSensor(PacketID::BUMP_AND_WHEEL_DROP, &response_vector));
  const uint8_t raw_result = response_vector[0];
  response->wheel_drop_caster = GetBit(raw_result, 4);
  response->wheel_drop_left = GetBit(raw_result, 3);
  response->wheel_drop_right = GetBit(raw_result, 2);
  response->bump_left = GetBit(raw_result, 1);
  response->bump_rignt = GetBit(raw_result, 0);
  return Error::Success();
}

Error RoombaController::ReadWall(bool* is_wall_present) {
  return ReadSensorWithBoolResponse(PacketID::WALL, is_wall_present);
}

Error RoombaController::ReadCliffLeft(bool* is_cliff_present) {
  return ReadSensorWithBoolResponse(PacketID::CLIFF_LEFT, is_cliff_present);
}

Error RoombaController::ReadCliffFrontLeft(bool* is_cliff_present) {
  return ReadSensorWithBoolResponse(PacketID::CLIFF_FRONT_LEFT,
                                    is_cliff_present);
}

Error RoombaController::ReadCliffFrontRight(bool* is_cliff_present) {
  return ReadSensorWithBoolResponse(PacketID::CLIFF_FRONT_RIGHT,
                                    is_cliff_present);
}

Error RoombaController::ReadCliffRight(bool* is_cliff_present) {
  return ReadSensorWithBoolResponse(PacketID::CLIFF_RIGHT, is_cliff_present);
}

Error RoombaController::ReadVirtualWall(bool* is_wall_present) {
  return ReadSensorWithBoolResponse(PacketID::VIRTUAL_WALL, is_wall_present);
}

Error RoombaController::ReadDistance(int16_t* distance) {
  vector<uint8_t> response_vector(2);
  CHECK_ERROR(ReadSensor(PacketID::DISTANCE, &response_vector));
  *distance = Get16BitSigned(response_vector[0], response_vector[1]);
  return Error::Success();
}

Error RoombaController::ReadAngle(int16_t* degrees) {
  vector<uint8_t> response_vector(2);
  CHECK_ERROR(ReadSensor(PacketID::ANGLE, &response_vector));
  *degrees = Get16BitSigned(response_vector[0], response_vector[1]);
  return Error::Success();
}

Error RoombaController::SendCommand(Command command,
                                    const vector<uint8_t>& data) {
  CHECK_ERROR(serial_port_->Write<uint8_t>(static_cast<uint8_t>(command)));
  CHECK_ERROR(serial_port_->Write(const_cast<uint8_t*>(data.data()),
                                  data.size()));
  return Error::Success();
}

Error RoombaController::ReadResponse(vector<uint8_t>* response) {
  size_t amount_read;
  CHECK_ERROR(serial_port_->Read(response->data(), 
                                 &amount_read, 
                                 response->size()));
  ERROR_IF(amount_read != response->size(), "Did not read expected message.");
  return Error::Success();
}

Error RoombaController::ReadSensorWithBoolResponse(PacketID sensor_id,
                                                   bool* response) {
  std::vector<uint8_t> response_vector(1);
  CHECK_ERROR(ReadSensor(sensor_id, &response_vector));
  *response = response_vector[0];
  return Error::Success();
}
} // namespace roomba
