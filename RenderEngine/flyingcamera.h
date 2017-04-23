#pragma once
#include <memory>

namespace GLES2 {

class Camera;

class FlyingCamera
{
public:
    struct KeySetting{
        int keyForwad;
        int keyBackward;
        int keyLeft;
        int keyRight;
        float rotateSensitivity;
        float slideSensitivity;
    };

    FlyingCamera(std::shared_ptr<Camera> camera, const KeySetting& setting);

public:
    void onViewSize(int width, int height);
    void onKeyRelease(int key);
    void onMouseDown(int x, int y);
    void onMouseMove(int x, int y);

private:
    std::shared_ptr<Camera> m_camera;
    KeySetting m_keySetting;
    int m_viewHeight;
    int m_viewWidth;

    int m_px;
    int m_py;
};

}
