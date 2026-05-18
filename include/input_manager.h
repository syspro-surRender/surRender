#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include "camera.h"
#include "display_manager.h"
#include "scene_manager.h"

struct InputManager {
  InputManager(const DisplayManager&, SceneManager&);
  ~InputManager();

  void processInput(bool&);

private:
  const DisplayManager& displayManager;
  Camera& camera;
};

#endif
