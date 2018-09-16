#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Player = 0,
			Player2 = 1,
			Tileset,
			BG,
			Particles,
			Lazers,
			Lazers2,
			BlueHeart,
			RedHeart,
			Count
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Player:    return "blue.png";
		case eTexture::Player2:    return "red.png";
		case eTexture::Tileset:   return "tileset.png";
		case eTexture::BlueHeart:   return "blueheart.png";
		case eTexture::RedHeart:   return "redheart.png";
		case eTexture::BG:		  return "bg.png";
		case eTexture::Particles: return "particles.png";
		case eTexture::Lazers:		  return "BLUE100GOOD.png";
		case eTexture::Lazers2:		  return "RED100GOOD.png";
		default:       return "UnknownTexType";
		}
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	static sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture)
	{
		switch (texture)
		{
		case  GameEngine::eTexture::Player:  return sf::Vector2f(100.f, 46.f);
		case  GameEngine::eTexture::Player2:  return sf::Vector2f(100.f, 46.f);
		case  GameEngine::eTexture::Tileset: return sf::Vector2f(32.f, 32.f);
		case  GameEngine::eTexture::BlueHeart: return sf::Vector2f(820.f, 820.f);
		case  GameEngine::eTexture::RedHeart: return sf::Vector2f(820.f, 820.f);
		case  GameEngine::eTexture::BG:	     return sf::Vector2f(1500.f, 1500.f);
		case  GameEngine::eTexture::Particles: return sf::Vector2f(31.f, 32.f);
		case  GameEngine::eTexture::Lazers: return sf::Vector2f(18.f, 18.f);
		case  GameEngine::eTexture::Lazers2: return sf::Vector2f(18.f, 18.f);
		default:							 return sf::Vector2f(-1.f, -1.f);
		}
	}
}

