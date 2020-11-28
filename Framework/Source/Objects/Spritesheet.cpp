#include "Framework.h"
#include "Spritesheet.h"

fw::Spritesheet::Spritesheet(char* fileloc)
{
    char* jsonFile = fw::LoadCompleteFile(fileloc, nullptr);

    m_doc.Parse(jsonFile);

    delete[] jsonFile;

    m_Width = m_doc["Width"].GetInt();
    m_Height = m_doc["Height"].GetInt();

    for (unsigned int i = 0; i < m_doc["Sprites"].Size(); i++)
    {
        std::string SpriteName = m_doc["Sprites"][i]["Name"].GetString();
        int OffsetX = m_doc["Sprites"][i]["X"].GetInt();
        int OffsetY = m_doc["Sprites"][i]["Y"].GetInt();
        int ScaleX = m_doc["Sprites"][i]["W"].GetInt();
        int ScaleY = m_doc["Sprites"][i]["H"].GetInt();

        Sprite* temp = new Sprite(SpriteName, OffsetX, OffsetY, ScaleX, ScaleY);

        m_Sprites.push_back(temp);
    }
}

fw::Spritesheet::~Spritesheet()
{
    for (int i = 0; i < m_Sprites.size(); i++)
    {
        delete m_Sprites[i];
    }
}

fw::Sprite* fw::Spritesheet::GetSpriteInfo(std::string spriteName)
{
    for (int i = 0; i < m_Sprites.size(); i++)
    {
        if (m_Sprites[i]->m_SpriteName == spriteName)
        {
            return m_Sprites[i];
        }
    }

    return nullptr;
}
