#include "Resources/TextureHolder.hpp"
#include "Utility/Logger.hpp"
#include "Utility/Enviroment.hpp"
// JSON OBJECTs
JsonObject::JsonObject(json JSON) : m_Json(JSON) {}

const ObjectInfo JsonObject::GetInfo()
{
    json JSON = m_Json[""];
    // sf::Vector2f Position = {}
}

TextureHolder::TextureHolder() {};
TextureHolder::~TextureHolder() {};

void TextureHolder::LoadDirectory()
{
    if (m_SelectedDirectory.empty())
    {
        LOG_ERROR("Selected directory is empty. Cannot load texture.");
        throw "Not properly used.";
    }
    std::filesystem::path Path(m_SelectedDirectory);

    if (!std::filesystem::is_directory(Path))
    {
        LOG_ERROR("Selected path is not a directory: {}", m_SelectedDirectory);
        throw "Directory not exist " + m_SelectedDirectory;
    }

    for (auto File : std::filesystem::directory_iterator(Path))
    {
        std::string FilePath = File.path().extension().string();
        if (FilePath == Enviroment::ImageTextureExtention)
        {
            LOG_DEBUG("Loading texture file: {}", File.path().string());
            LoadFile(File.path().string());
        }
        if (FilePath == Enviroment::FormatTextureExtention)
        {
            LOG_DEBUG("Loading texture file: {}", File.path().string());
            LoadJsonFile(File.path().string());
        }
    }
}

bool TextureHolder::LoadFile(const std::string &TexturePath)
{
    std::unique_ptr<sf::Texture> Texture = std::make_unique<sf::Texture>();
    std::filesystem::path Path(TexturePath);
    if (!Texture->loadFromFile(Path))
    {
        LOG_ERROR("Failed to load texture from file: {}", Path.string());
        return false;
    }
    AddTexture(Path.filename().string(), std::move(Texture));
    return true;
}

bool TextureHolder::LoadJsonFile(const std::string &JsonPath)
{
    std::ifstream JsonFile(JsonPath);
    if (!JsonFile.is_open())
    {
        LOG_ERROR("Failed to load texture from file: {}", JsonPath);
        return false;
    }
    json JSON;
    JsonFile >> JSON;
    JsonFile.close();

    return true;
}

bool TextureHolder::AddTexture(const std::string &TextureName, std::unique_ptr<sf::Texture> Texture)
{
    auto InsertedTexture = m_TextureMap.insert(std::make_pair(TextureName, std::move(Texture)));
    if (!InsertedTexture.second)
    {
        LOG_ERROR("Texture {} already exists in the map.", TextureName);
        throw "Cannot insert texture " + TextureName;
    }
    return true;
}

bool TextureHolder::AddJson(const std::string &JsonName, JsonObject JSON)
{
    auto InsertedJson = m_JsonMap.insert(std::make_pair(JsonName, JSON));
    if (!InsertedJson.second)
    {
        LOG_ERROR("Texture {} already exists in the map.", JsonName);
        throw "Cannot insert texture " + JsonName;
    }
    return true;
}

const sf::Texture &TextureHolder::GetTexture(std::string TextureName) const
{
    auto SelectTexture = m_TextureMap.find(TextureName);
    assert(SelectTexture != m_TextureMap.end());
    return *SelectTexture->second;
};