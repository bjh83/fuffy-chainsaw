#ifndef ROOMBA_ROOMBA_CONTROLLER_FACTORY_H_
#define ROOMBA_ROOMBA_CONTROLLER_FACTORY_H_

#include <memory>
#include "cc/roomba/error.h"
#include "cc/roomba/roomba_controller.h"

namespace roomba {
Error BuildController(std::unique_ptr<RoombaController>* controller);
} // namespace roomba

#endif // ROOMBA_ROOMBA_CONTROLLER_FACTORY_H_
