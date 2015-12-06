#ifndef ROOMBA_CONFIG_H_
#define ROOMBA_CONFIG_H_

#include <string>

#ifdef __linux__
#define SERIAL_PATH "/dev/ttyUSB0"
#elif __APPLE__
#define SERIAL_PATH "/dev/cu.usbserial-DA017LYP"
#endif

namespace roomba {

static const std::string kSerialPortPath = SERIAL_PATH;
} // namespace roomba

#endif // ROOMBA_CONFIG_H_
