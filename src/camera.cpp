#include "camera.h"

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix() {
  return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Camera::setPosition(const glm::vec3& pos) {
  position = pos;
}

void Camera::rotateYaw(float degrees) {
  glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
  front              = glm::vec3(rotation * glm::vec4(front, 0.0f));
  right              = glm::vec3(rotation * glm::vec4(right, 0.0f));
}

void Camera::move(glm::vec3& vec) {
  position += vec;
}

void Camera::moveForward(float deltaTime) {
  float velocity = movementSpeed * deltaTime;
  position += front * velocity;
}

void Camera::moveBackward(float deltaTime) {
  float velocity = movementSpeed * deltaTime;
  position -= front * velocity;
}

void Camera::moveRight(float deltaTime) {
  float velocity = movementSpeed * deltaTime;
  position += right * velocity;
}

void Camera::moveLeft(float deltaTime) {
  float velocity = movementSpeed * deltaTime;
  position -= right * velocity;
}

void Camera::moveUp(float deltaTime) {
  float velocity = movementSpeed * deltaTime;
  position += up * velocity;
}

void Camera::moveDown(float deltaTime) {
  float velocity = movementSpeed * deltaTime;
  position -= up * velocity;
}
