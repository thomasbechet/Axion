layout(std140, binding = SGC_CAMERA_UBO_BINDING_POINT) uniform Camera
{
    mat4 camera_projection;
    mat4 camera_view;
    mat4 inv_camera_projection;
};