#include "camera.h"

namespace Tmpl8
{
    int cam_offset_x = 0;
    int cam_offset_y = 0;

    void Camera::setCamPos(int x, int y)
    {
        cam_offset_x = x;
        cam_offset_y = y;
    }

    void Camera::camShake()
    {
        // TODO
    }
};