#include "ThreeColorEffect.hpp"
#include <iostream>
#include "LightController.hpp"

ThreeColorEffect::ThreeColorEffect(LightController *lightController,
                                   ParamController *paramController)
    : Effect(lightController, paramController) {
  ChooseLights();
}

void ThreeColorEffect::BeatDetected() {}

void ThreeColorEffect::DoRun() {
  lightController->Set(light1, hsv1);
  lightController->Set(light2, hsv2);
  lightController->Set(light3, hsv3);
}

void ThreeColorEffect::ParamChanged(Params param) {
  switch (param) {
    case Params::kHue0:
      hsv1.h = paramController->Get(Params::kHue0);
      break;

    case Params::kHue1:
      hsv2.h = paramController->Get(Params::kHue1);
      break;

    case Params::kHue2:
      hsv3.h = paramController->Get(Params::kHue2);
      break;

    // TODO: handle other cases
    case Params::kWidth:
    case Params::kPan:
    case Params::kTilt:
    case Params::kTempo:
      break;
  }
}

void ThreeColorEffect::ChooseLights() {
  // Keep track of the lights that were on before, and turn them off if they're
  // no longer selected.
  std::vector<uint16_t> oldLightIds = {light1, light2, light3};
  std::vector<uint16_t> lightIds =
      lightController->GetLights(paramController, 1, 3)[0];
  TurnOffUnusedLights(oldLightIds, lightIds);

  light1 = lightIds[0];
  light2 = lightIds[1];
  light3 = lightIds[2];
}