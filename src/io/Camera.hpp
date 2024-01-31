#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        float Speed;
        Camera(glm::vec3 position);
        //Modifiers
        void UpdateCameraDirection(double dx, double dy);
        void UpdateCameraPosition(CameraDirection dir, double dt);
        void SetZoom(double dy);
        void SetSensitivity(float sensi);
        //Assesors
        float GetZoom();
        float GetSensitvity();
        glm::vec3 GetPosition();
        glm::vec3 GetFront();
        glm::mat4 GetViewMatrix();

    private:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;

        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float zoom;
        float sensitivity;
        void updateCameraVectors();    
};

#endif