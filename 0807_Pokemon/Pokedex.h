#pragma once

class Pokedex
{
private:
	std::vector<PokedexData> m_pokemonList;

private:
	Pokedex();
	~Pokedex();
	void SavePokemon();
	void LoadPokemon();

public:
	static Pokedex& GetInstance()
	{
		static Pokedex Instance;
		return Instance;
	}

	void Init();
	PokedexData GetPokemonData(short _number);
};

#define POKEDEX Pokedex::GetInstance()