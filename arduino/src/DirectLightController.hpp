#ifndef __DIRECT_LIGHT_CONTROLLER_HPP__
#define __DIRECT_LIGHT_CONTROLLER_HPP__

#include "../../src/color/Color.hpp"
#include "../../src/controller/LightController.hpp"

// From https://github.com/ssilverman/TeensyDMX
#include "../libraries/TeensyDMX/src/TeensyDMX.h"

namespace teensydmx = ::qindesign::teensydmx;

class DirectLightController : public LightController {
 public:
  DirectLightController();

  void Set(const int16_t lightId, HSV hsv) override;
  long GetMs() override;
  void WriteLeds() override;

 private:
  teensydmx::Sender dmx{Serial2};

  /** The number of serial LEDs. */
  const int kNumLeds = 5;
};

#endif
