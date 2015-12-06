#include <iostream>
#include <memory>
#include "cc/roomba/roomba_controller.h"
#include "cc/roomba/roomba_controller_factory.h"
#include "cc/roomba/config.h"

#include <unistd.h>

using std::unique_ptr;
using roomba::RoombaController;
using roomba::BuildController;
using roomba::Error;
using roomba::kMarioThemeIntro;

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
  error = controller->SetSong(0, kMarioThemeIntro);
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
  error = controller->PlaySong(0);
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  // Turn in place clockwise.
  error = controller->DriveDirect(250, -250);
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  usleep(150 * 1000);
  error = controller->DriveDirect(-250, 250);
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  usleep(150 * 1000);
  error = controller->DriveDirect(250, 250);
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  usleep(450 * 1000);
  error = controller->DriveDirect(-250, -250);
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  usleep(800 * 1000);
  error = controller->DriveDirect(250, 250);
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  usleep(200 * 1000);
  error = controller->Start();
  if (!error) {
    std::cout << error.error_message() << std::endl;
    return -1;
  }
  sleep(1);
  return 0;
}
