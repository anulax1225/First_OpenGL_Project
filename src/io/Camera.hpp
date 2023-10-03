#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../../lib/glm/glm.hpp"
#include "../../lib/glm/gtc/matrix_transform.hpp"

enum class CameraDirection {
    NONE = 0,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera  {
    public:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;

        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float speed;
        float zoom;
        float sensitivity;

        Camera(glm::vec3 position);

        void UpdateCameraDirection(double dx, double dy);
        void UpdateCameraPosition(CameraDirection dir, double dt);
        void UpdateCameraZoom(double dy);

        glm::mat4 GetViewMatrix();

    private:
        void updateCameraVectors();    
};

#endif