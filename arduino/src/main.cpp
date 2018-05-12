#include "../../src/controller/BounceEffect.hpp"
#include "../../src/controller/CircleStrobeEffect.hpp"
#include "../../src/controller/ColorShiftEffect.hpp"
#include "../../src/controller/SolidColorEffect.hpp"
#include "../../src/controller/StrobeEffect.hpp"
#include "../../src/controller/ThreeColorEffect.hpp"
#include "../../src/controller/UnevenSwitchStrobeEffect.hpp"
#include "DirectLightController.hpp"
#include "DirectParamController.hpp"
#include "WProgram.h"

// This is some stuff to fix issues with the Teensy library vector
// implementation where
// it throws warnings or fails to link if there is no __throw_bad_alloc()
// or __throw_length_error() functions.

namespace std {
void __throw_bad_alloc() {
  Serial.println("bad_alloc");
  while (1)
    ;
}
void __throw_length_error(char const *e) {
  Serial.print("length_error: ");
  Serial.println(e);
  while (1)
    ;
}
}

extern "C" int main(void) {
  pinMode(13, OUTPUT);

  DirectLightController *lightController = new DirectLightController();
  DirectParamController *paramController = new DirectParamController();
  paramController->Set(Params::kHue0, 120);
  paramController->Set(Params::kTempo, 254);
  paramController->Set(Params::kWidth, 255);
  paramController->Set(Params::kPan, ParamController::kPanNeutral);
  paramController->Set(Params::kTilt, ParamController::kTiltNeutral);
  Effect *effect = new SolidColorEffect(lightController, paramController);

  while (1) {
    effect->Run();

    if (paramController->ScanForChanges(effect) != ParamChanged::kNone) {
      effect->ChooseLights();
    }
    delay(3);
  }
}
