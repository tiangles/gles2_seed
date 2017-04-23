#include "flyingcamera.h"
#include "camera.h"
#include "vec.h"

using namespace GLES2;

FlyingCamera::FlyingCamera(std::shared_ptr<Camera> camera, const FlyingCamera::KeySetting &setting)
    :m_camera(camera)
    ,m_keySetting(setting)
    ,m_viewHeight(1)
    ,m_viewWidth(1)
{

}

void FlyingCamera::onViewSize(int width, int height)
{
    m_viewWidth = width;
    m_viewHeight = height;
    m_px = m_viewWidth/2;
    m_py = m_viewHeight/2;
}

void FlyingCamera::onKeyRelease(int key)
{
    vec3 dm;
    if(key == m_keySetting.keyForwad)
        dm.z = -m_keySetting.slideSensitivity;
    if(key == m_keySetting.keyBackward)
        dm.z = m_keySetting.slideSensitivity;
    if(key == m_keySetting.keyLeft)
        dm.x = -m_keySetting.slideSensitivity;
    if(key == m_keySetting.keyRight)
        dm.x = m_keySetting.slideSensitivity;

    m_camera->slide(dm);
}

void FlyingCamera::onMouseDown(int x, int y){
    m_px = x;
    m_py = y;
}

void FlyingCamera::onMouseMove(int x, int y)
{
    float dx = (x-m_px);
    float dy = (y-m_py);
    if(dx != 0){
        m_camera->rotate(vec3(0, 1, 0), dx*m_keySetting.rotateSensitivity);
    }
    if(dy != 0){
        m_camera->pitch(dy*m_keySetting.rotateSensitivity);
    }

    m_px = x;
    m_py = y;
}
