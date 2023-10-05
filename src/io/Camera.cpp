#include "Camera.hpp"

Camera::Camera(glm::vec3 position) {
    this->cameraPos = position;
    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->yaw = -90.0f;
    this->pitch = 0.0f;
    this->Speed = 2.5f;
    this->zoom = 45.0f;
    this->cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    this->sensitivity = 0.1f;
    this->updateCameraVectors();
}

void Camera::UpdateCameraDirection(double dx, double dy) {
    this->yaw += dx * this->sensitivity;
    this->pitch += dy * this->sensitivity;
    //Bound the pitch because it shouldn't more or less then 89.9 to -89.9 degres
    this->pitch = this->pitch > 89.9f ? 89.9f : this->pitch;
    this->pitch = this->pitch < -89.9f ? -89.9f : this->pitch;
    this->updateCameraVectors();
}

void Camera::UpdateCameraPosition(CameraDirection dir, double dt) {
    float velocity = (float)dt * this->Speed;

    switch(dir) {
        case CameraDirection::FORWARD:
            this->cameraPos += this->cameraFront * velocity;
            break;
        case CameraDirection::BACKWARD:
            this->cameraPos -= this->cameraFront * velocity;
            break;
        case CameraDirection::RIGHT:
            this->cameraPos += this->cameraRight * velocity;
            break;
        case CameraDirection::LEFT:
            this->cameraPos -= this->cameraRight * velocity;
            break;
        case CameraDirection::UP:
            this->cameraPos += this->cameraUp * velocity;
            break;
        case CameraDirection::DOWN:
            this->cameraPos -= this->cameraUp * velocity;
            break;
        case CameraDirection::NONE:
            break;
    }
}

void Camera::SetZoom(double dy) {
    if(this->zoom >= 1.0f && this->zoom <= 45.0f) {
        this->zoom -= dy;
    }
    else if (this->zoom < 1.0f) {
        this->zoom = 1.0f; 
    }
    else {
        this->zoom = 45.0f;
    }
}

float Camera::GetZoom() {
    return this->zoom; 
}

void Camera::SetSensitivity(float sensi) {
    this->sensitivity = sensi;
}

float Camera::GetSensitvity() {
    return this->sensitivity;
}

glm::vec3 Camera::GetPosition() {
    return glm::vec3(this->cameraPos);
}

glm::vec3 Camera::GetFront() {
    return glm::vec3(this->cameraFront);
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::updateCameraVectors() {
    glm::vec3 direction;
    //Finds the front of the camera with the pitch angle and yaw angle
    //The pitch describes the angle on x, y and z axes
    //The yaw describes the angle on the x and z axes
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->cameraFront = glm::normalize(direction);
    //The cross produit finds a vector perpendicular to the two others
    this->cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    this->cameraUp = glm::normalize(glm::cross(this->cameraRight, this->cameraFront));

}  