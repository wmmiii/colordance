#include "StrobeEffect.hpp"
#include "LightController.hpp"

StrobeEffect::StrobeEffect(LightController *lightController,
                           ParamController *paramController)
    : Effect(lightController, paramController) {
  hsv.h = paramController->Get(Params::kHue0);
  ChooseLights();
}

void StrobeEffect::DoRun() {
  currentLight++;
  if (currentLight >= lightIds.size()) {
    currentLight = 0;
  }

  HSV adjustedHsv = hsv;
  adjustedHsv.h += hueAdjust * currentLight;
  lightController->Set(lightIds[currentLight], adjustedHsv);

  if (currentLight == 0) {
    if (lightIds.size() > 1) {
      lightController->Set(lightIds[lightIds.size() - 1], {0, 0, 0});
    }
  } else {
    lightController->Set(lightIds[currentLight - 1], {0, 0, 0});
  }

  hsv.h += 10;
  SleepMs(paramController->GetScaled(Params::kTempo, 1000, 75));
}

void StrobeEffect::ChooseLights() {
  // Keep track of the lights that were on before, and turn them off if they're
  // no longer selected.
  std::vector<int16_t> oldLightIds = lightIds;

  lightIds = lightController->GetLightsFromParams(paramController);
  hueAdjust = 320 / lightIds.size();
  TurnOffUnusedLights(oldLightIds, lightIds);
}

void StrobeEffect::BeatDetected() {
  hsv.h += 30;
  DoRun();
}
