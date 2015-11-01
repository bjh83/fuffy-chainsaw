#include "cc/roomba/error.h"

namespace roomba {

Error CreateError(std::string message, int line_number, std::string file_name) {
  return Error(false, 
               file_name + ":" + std::to_string(line_number) + "] " + message);
}

Error CreateError(const Error& error, int line_number, std::string file_name) {
  std::string outer_message = 
      "Error originated at: \n    " + error.error_message();
  return CreateError(outer_message, line_number, file_name);
}

} // namespace roomba
