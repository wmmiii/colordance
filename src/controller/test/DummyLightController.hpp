#ifndef __DUMMY_LIGHT_CONTROLLER_HPP__
#define __DUMMY_LIGHT_CONTROLLER_HPP__

#include "../../color/Color.hpp"
#include "../LightController.hpp"
#include <vector>

/*
 * TODO
 */
class DummyLightController : public LightController {
public:
  DummyLightController(const uint8_t rows, const uint8_t cols);

  void Set(const Lights light, HSV hsv) override;

  uint16_t GetMs() override;

protected:
};

#endif
