#ifndef RTC_RAY
#define RTC_RAY

#include "newPrimitives.h"
#include <string>

class Ray {

    public:
        Ray();
        Ray(glm::vec4 origin, glm::vec4 direction);

        glm::vec4 position(float time);
        std::string debugString();

        inline glm::vec4 origin() { return m_origin; }
        inline glm::vec4 direction() { return m_direction; }
        void setOrigin(glm::vec4 origin);
        void setDirection(glm::vec4 direction);
    
    private:
        glm::vec4 m_origin;
        glm::vec4 m_direction;
};

Ray transformRay(Ray &ray, glm::mat4 &matrix);

#endif