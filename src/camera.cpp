#include "camera.h"

glm::mat4 Camera::getViewMatrix() {
  glm::vec3 front = orientation * glm::vec3(0,0,-1);
  glm::vec3 up    = orientation * glm::vec3(0,1,0);
  return glm::lookAt(position, position + front, up);
}


glm::mat4 Camera::getProjectionMatrix() {
  return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Camera::setPosition(const glm::vec3& pos) {
  position = pos;
}

void Camera::rotateYaw(float degrees) {
  glm::quat q = glm::angleAxis(glm::radians(degrees), glm::vec3(0,1,0));
  orientation = glm::normalize(q * orientation);
}

void Camera::rotatePitch(float degrees) {
  glm::vec3 right = orientation * glm::vec3(1,0,0);
  glm::quat q = glm::angleAxis(glm::radians(degrees), right);
  orientation = glm::normalize(q * orientation);
}

void Camera::move(glm::vec3& vec) {
  position += vec;
}

void Camera::moveForward(float deltaTime) {
  glm::vec3 front = orientation * glm::vec3(0,0,-1);
  float velocity = movementSpeed * deltaTime;
  position += front * velocity;
}

void Camera::moveBackward(float deltaTime) {
  glm::vec3 front = orientation * glm::vec3(0,0,-1);
  float velocity = movementSpeed * deltaTime;
  position -= front * velocity;
}

void Camera::moveRight(float deltaTime) {
  glm::vec3 right = orientation * glm::vec3(1,0,0);
  float velocity = movementSpeed * deltaTime;
  position += right * velocity;
}

void Camera::moveLeft(float deltaTime) {
  glm::vec3 right = orientation * glm::vec3(1,0,0);
  float velocity = movementSpeed * deltaTime;
  position -= right * velocity;
}

void Camera::moveUp(float deltaTime) {
  glm::vec3 up    = orientation * glm::vec3(0,1,0);
  float velocity = movementSpeed * deltaTime;
  position += up * velocity;
}

void Camera::moveDown(float deltaTime) {
  glm::vec3 up    = orientation * glm::vec3(0,1,0);
  float velocity = movementSpeed * deltaTime;
  position -= up * velocity;
}
