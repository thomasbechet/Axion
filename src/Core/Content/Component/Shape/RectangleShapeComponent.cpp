#include <Core/Content/Component/Shape/RectangleShapeComponent.hpp>

#include <Core/Asset/AssetModule.ipp>
#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

RectangleShapeComponent::RectangleShapeComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{
    setMinX(parseNumber(json, "minx"));
    setMaxX(parseNumber(json, "maxx"));
    setMinY(parseNumber(json, "miny"));
    setMaxY(parseNumber(json, "maxy"));
    setMinZ(parseNumber(json, "minz"));
    setMaxZ(parseNumber(json, "maxz"));

    

    try
    {
        auto jXMin = json.find("xmin");
        if(jXMin != json.end() && jXMin->is_number())
            setMinX(jXMin->get<float>());
    }
    catch(...) {}

    try
    {
        auto jXMax = json.find("xmax");
        if(jXMax != json.end() && jXMax->is_number())
            setMaxX(jXMax->get<float>());
    }
    catch(...) {}

        

        auto jYMin = json.find("ymin");
        if(jYMin != json.end() && jYMin->is_number())
            setMinY(jYMin->get<float>());

        auto jYMax = json.find("ymax");
        if(jYMax != json.end() && jYMax->is_number())
            setMaxY(jYMax->get<float>());

        auto jZMin = json.find("zmin");
        if(jZMin != json.end() && jZMin->is_number())
            setMinZ(jZMin->get<float>());

        auto jZMax = json.find("zmax");
        if(jZMax != json.end() && jZMax->is_number())
            setMaxZ(jZMax->get<float>());

        auto 
    }
    catch(...) {}
}
RectangleShapeComponent::RectangleShapeComponent(const Entity& entity,
        float xMin, float xMax,
        float yMin, float yMax,
        float zMin, float zMax,
        bool smooth,
        float factor
    ) :
    Rectangle(
        xMin, xMax,
        yMin, yMax,
        zMin, zMax
    ),
    transform(entity.getComponent<TransformComponent>()),
    m_coordinateFactor(factor)
{
    //Mesh
    m_mesh = Engine::renderer().createMesh(
        Rectangle::vertices(
            m_xMin, m_xMax,
            m_yMin, m_yMax,
            m_zMin, m_zMax,
            m_coordinateFactor
        )
    );

    //Staticmesh
    m_staticmesh = Engine::renderer().createStaticmesh();
    m_staticmesh->setTransform(&transform);
    m_staticmesh->setMesh(m_mesh);
    m_material = Engine::asset().get<Material>(Material::Default);
    m_staticmesh->setMaterial(m_material->getHandle());
}
RectangleShapeComponent::~RectangleShapeComponent()
{
    Engine::renderer().destroyStaticmesh(m_staticmesh);
    Engine::renderer().destroyMesh(m_mesh);
}

void RectangleShapeComponent::setMaterial(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->setMaterial(nullptr);
}
void RectangleShapeComponent::setMaterial(const std::string& name) noexcept
{
    setMaterial(Engine::asset().get<Material>(name));
}
void RectangleShapeComponent::setMaterial(Reference<Material> material) noexcept
{
    if(material)
    {
        m_material.reset();
        m_material = material;

        m_staticmesh->setMaterial(m_material->getHandle());
    }
    else
    {
        setMaterial(nullptr);
    }   
}

void RectangleShapeComponent::setCoordinateFactor(float factor) noexcept
{
    m_coordinateFactor = factor;
}

void RectangleShapeComponent::generate() noexcept
{
    m_mesh->update(Rectangle::vertices(
        m_xMin, m_xMax,
        m_yMin, m_yMax,
        m_zMin, m_zMax,
        m_coordinateFactor
    ));
}

float RectangleShapeComponent::parseNumber(const Json& json, const std::string& name) noexcept
{
    try
    {
        auto value = json.find(name);
        if(value != json.end() && value->is_number())
            return value->get<float>();
    }
    catch(...)
    {
        Engine::logger().log("Failed to parse value '" + name + "'", Severity::Warning);
        return 0.0f;
    }
}