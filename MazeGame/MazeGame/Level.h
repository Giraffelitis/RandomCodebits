#pragma once
#include <string>
#include <vector>

using std::string;

class PlaceableActor;

class Level
{
	char* m_pLevelData;
	int m_height;
	int m_width;
	
public:
	Level();
	~Level();

	bool Load(string levelName, int* playerX, int* playerY);
	void Draw();
	PlaceableActor* UpdateActors(int x, int y);
	std::vector<PlaceableActor*> m_pActors;

	bool IsSpace(int x, int y);
	bool IsWall(int x, int y);

	char PickupKey(int x, int y);
	char OpenDoor(int x, int y);

	int GetHeight() { return m_height; }
	int GetWidth() { return m_width; }

	static constexpr char WAL = (char)219;

private:
	bool Convert(int* playerX, int* playerY);
	int GetIndexFromCoordinates(int x, int y);
};