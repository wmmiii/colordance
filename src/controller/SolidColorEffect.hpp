#ifndef __SOLID_COLOR_EFFECT_HPP__
#define __SOLID_COLOR_EFFECT_HPP__

#include "Effect.hpp"
#include "LightController.hpp"

class SolidColorEffect : public Effect {
public:
  SolidColorEffect(LightController *controller);

  /* Called periodically to perform the effect. */
  void run() override;

private:
  HSV hsv1 = {HUE_RED, 255, 255};
  HSV hsv2 = {HUE_GREEN, 255, 255};
  HSV hsv3 = {HUE_BLUE, 255, 255};
};

#endif
