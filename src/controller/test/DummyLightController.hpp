#ifndef __DUMMY_LIGHT_CONTROLLER_HPP__
#define __DUMMY_LIGHT_CONTROLLER_HPP__

#include <vector>
#include "../../color/Color.hpp"
#include "../LightController.hpp"

/*
 * TODO
 */
class DummyLightController : public LightController {
 public:
  DummyLightController(const uint8_t rows, const uint8_t cols);

  void Set(const Lights light, HSV hsv) override;

  uint16_t GetMs() override;

  void Set(const uint16_t lightId, HSV hsv) override;

 protected:
};

#endif