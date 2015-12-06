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

static const std::vector<uint8_t> kMarioThemeIntro = {
	// note, duration
	76, 8, // E, 16th
	76, 16, // E, 8th
	76, 24, // E, tied 8th & 16th
	72, 8, // C, 16th
	76, 16, // E, 8th
	79, 16, // G, 8th
	30, 16, // rest, 8th
	67, 16, // G, 8th
};
} // namespace roomba

#endif // ROOMBA_CONFIG_H_
