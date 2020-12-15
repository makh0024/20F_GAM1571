#pragma once
class Tilemap;

class Bomb : public fw::GameObject
{
public:
	Bomb(float x, float y, std::string Name, fw::Mesh* Mesh, fw::ShaderProgram* Shader, fw::vec4 color, fw::GameCore* pGameCore, fw::vec2 playerScale, Tilemap* pTilemap);
	~Bomb();

	void Update(float deltaTime);

	void Explode();

	void SetIsActive(bool active);
	bool m_isActive;
	float timer;
	int explodedtiles[9];
	bool hasexploded = false;
protected:

private:	
	fw::Texture* m_pTexture = nullptr;
	fw::vec2 m_UVScale = fw::vec2(1, 1);
	fw::vec2 m_UVOffset = fw::vec2(0, 0);
	Tilemap* m_pTilemap;

};