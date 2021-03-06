#include "ColorShiftAndStrobeEffect.hpp"
#include "LightController.hpp"

ColorShiftAndStrobeEffect::ColorShiftAndStrobeEffect(
    LightController *lightController, ParamController *paramController)
    : Effect(lightController, paramController) {
  // Choose lights
  ChooseLights();
  hsvAdvance = paramController->GetScaled(Params::kTempo, 0, 10);
}

void ColorShiftAndStrobeEffect::DoRun() {
  for (int16_t i = 0; i < lightIds.size(); i++) {
    if (lightsOn) {
      lightController->Set(lightIds[i], {hsv.h + i * hsvShift, hsv.s, hsv.v});
    } else {
      lightController->Set(lightIds[i], {0, 0, 0});
    }
  }

  hsv.h += hsvAdvance;

  SleepMs(paramController->GetScaled(Params::kTempo, 1000, 75));
  lightsOn = !lightsOn;
}

void ColorShiftAndStrobeEffect::BeatDetected() { hsv.h += 60; }

void ColorShiftAndStrobeEffect::ParamChanged(Params param) {
  switch (param) {
    case Params::kTempo:
      hsvAdvance = paramController->GetScaled(Params::kTempo, 0, 10);
      // hsvAdvance = 0;
      break;

    // TODO: handle other cases
    case Params::kHue0:
    case Params::kHue1:
    case Params::kHue2:
    case Params::kWidth:
    case Params::kPan:
    case Params::kTilt:
      break;
  }
}

void ColorShiftAndStrobeEffect::ChooseLights() {
  // Keep track of the lights that were on before, and turn them off if they're
  // no longer selected.
  std::vector<int16_t> oldLightIds = lightIds;

  lightIds = lightController->GetLightsFromParams(paramController);
  hsvShift = 180 / lightIds.size();
  // hsvShift = 2;

  TurnOffUnusedLights(oldLightIds, lightIds);
}
