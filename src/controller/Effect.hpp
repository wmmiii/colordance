#ifndef __EFFECT_HPP__
#define __EFFECT_HPP__

// Note: this needs to be before the <cmath> include, because Arduino includes
// an abs macro that clobbers the std::abs. Putting a break after this import
// prevents clang-format from reordering it.
#ifdef ARDUINO
#include "WProgram.h"
#endif

#include "LightController.hpp"
#include "ParamController.hpp"

class Effect {
 public:
  Effect(LightController *lightController, ParamController *paramController);

  /*
   * Called periodically to perform the effect. This is called by the main
   * loop. Subclasses implement DoRun, below. DoRun contains the
   * effect-specific code. This method contains glue code and calls DoRun. This
   * allows e.g. for an effect to ask to be run every certain number of
   * milliseconds.
   */
  void Run();

  /*
   * Called when a music beat is detected (or is manually triggered by the
   * control surface).
   */
  virtual void BeatDetected() = 0;

  // TODO: decide whether both ChooseLights and ParamChanged should exist -
  // they seem redundant.

  /*
   * Called by the main controller when a param that affects which lights are
   * chosen is changed. This tells the effect that it should re-select lights.
   */
  virtual void ChooseLights(){};

  /*
   * Called by the main controller when any param is changed.
   */
  virtual void ParamChanged(Params param){};

  /**
   * Applies the current state of all params by calling ParamChanged for all
   * parameters.
   */
  void ReloadParams();

  /**
   * Sets the used params to "appropriate" random values. This shouldn't choose
   * anything too harsh (like a high-tempo strobe).
   */
  virtual void RandomizeParams(){};

 protected:
  /* Effect-specific code. Must be overriden by subclasses. */
  virtual void DoRun() = 0;

  void TurnOffUnusedLights(const std::vector<int16_t> &oldLightIds,
                           const std::vector<int16_t> &currentLightIds);

  /*
   * Sleeps this effect for the specified number of milliseconds. DoRun won't be
   * called until this elapses.
   */
  void SleepMs(long ms);

  /* Controls the output lights. */
  LightController *const lightController;

  /* Keeps track of effect parameters. */
  ParamController *const paramController;

 private:
  /* When to call DoRun again. Used for SleepMs. */
  long runAtMs = 0;
};

#endif
