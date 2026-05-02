#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    float rotationSpeed;
    float movementSpeed;

public:
    Camera(glm::vec3 startPos)
    : position(startPos)
    , front(0.0f, 0.0f, -1.0f)
    , right(1.0f, 0.0f, 0.0f)
    , up(0.0f, 1.0f, 0.0f)
    , movementSpeed(3.0f)
    {};

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(float aspectRatio);
    
    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition();

    void setDirection(const glm::vec3& dir);
    glm::vec3 getDirection();

    void rotateYaw(float degrees);

    void move(glm::vec3& vec);

    void moveForward(float deltaTime);
    void moveBackward(float deltaTime);
    void moveRight(float deltaTime);
    void moveLeft(float deltaTime);
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
};
