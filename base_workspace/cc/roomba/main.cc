#include <iostream>
#include <memory>
#include "cc/roomba/roomba_controller.h"
#include "cc/roomba/roomba_controller_factory.h"

#include <unistd.h>

using std::unique_ptr;
using roomba::RoombaController;
using roomba::BuildController;
using roomba::Error;

int main() {
  unique_ptr<RoombaController> controller;
  Error error = BuildController(&controller);
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  error = controller->Start();
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  sleep(1);
  error = controller->Safe();
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  sleep(1);
  // Turn in place clockwise.
  error = controller->DriveDirect(250, -250);
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  sleep(1);
  error = controller->Start();
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  sleep(1);
  return 0;
}
