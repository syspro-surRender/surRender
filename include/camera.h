#ifndef CAMERACLASS
#define CAMERACLASS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera {
private:
  glm::vec3 position;
  glm::quat orientation;

  float rotationSpeed;
  float movementSpeed;
  float aspectRatio;

public:
  Camera(glm::vec3 startPos, float aspectRatio): 
    position(startPos),
    orientation(1.0f, 0.0f, 0.0f, 0.0f),
    movementSpeed(3.0f),
    rotationSpeed(90.0f),
    aspectRatio(aspectRatio)
  {};

  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();

  void setPosition(const glm::vec3& pos);
  glm::vec3 getPosition();

  void rotateYaw(float degrees);
  void rotatePitch(float degrees);

  void move(glm::vec3& vec);

  void moveForward(float deltaTime);
  void moveBackward(float deltaTime);
  void moveRight(float deltaTime);
  void moveLeft(float deltaTime);
  void moveUp(float deltaTime);
  void moveDown(float deltaTime);
};

#endif
