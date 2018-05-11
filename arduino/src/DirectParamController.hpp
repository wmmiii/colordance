#ifndef __DIRECT_PARAM_CONTROLLER_HPP__
#define __DIRECT_PARAM_CONTROLLER_HPP__

#include <map>
#include "../../src/controller/Effect.hpp"
#include "../../src/controller/ParamController.hpp"
#include "WProgram.h"

enum class ParamChanged {
  /** No params changed */
  kNone,
  /** A param changed that affects which lights are selected */
  kChooseLights,
  /** A param changed, but not one that affects light selection */
  kOther,
};

/**
 * Reads params the controls connected to this teensy.
 *
 * TODO: actually do that
 */
class DirectParamController : public ParamController {
 public:
  DirectParamController();

  uint16_t Get(Params param) override;

  void Set(Params param, uint16_t val) override;

  ParamChanged ScanForChanges(Effect *effect);

 private:
  std::map<const Params, uint16_t> params;

  /** Maps from param to the pot pin */
  const std::map<const Params, const int> potParamMap = {
      {Params::kWidth, 14},
      {Params::kPan, 16},
      {Params::kTilt, 23},
      {Params::kTempo, 17},
  };

  // Pins
  const int kWidthPin = A2;
};

#endif