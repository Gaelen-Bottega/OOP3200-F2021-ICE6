#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>

#include "GameObject.h"
#include "Vector3D.h"


int main()
{
	// map is made up of key-value pairs - in this case the key is a string
	// and the value is a GameObject
	std::map<std::string, GameObject*> gameObjects;

	auto* ship = new GameObject("Ship", 0, 3.0f, 4.0f);
	auto* enemy = new GameObject("Enemy", 1, 10.0f, 20.0f);
	auto* space_station = new GameObject("SpaceStation", 2, 100.0f, 200.0f);

	// Add each object indivitually with -> notation to the accessor 
	gameObjects[ship->GetName()] = ship;
	gameObjects[enemy->GetName()] = enemy;
	gameObjects[space_station->GetName()] = space_station;

	// in Laymans terms for every game_object in gameObjects...loop
	for (const auto& game_object : gameObjects)
	{
		std::cout << "Key  : " << game_object.first << std::endl;
		std::cout << "Value: " << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << game_object.second->ToString() << std::endl;
	}

	auto distance = Vector2D<float>::Distance(gameObjects["Ship"]->GetPosition(), gameObjects["Enemy"]->GetPosition());

	std::cout << "Distance between " << gameObjects["Ship"]->GetName()
		<< " and " << gameObjects["Enemy"]->GetName() << " is: " << std::to_string(distance) << "\n" << std::endl;


	// start output
	std::ofstream outfile("GameObject.txt", std::ios::out);
	outfile << gameObjects["Ship"]->ToFile() << std::endl;
	outfile << gameObjects["Enemy"]->ToFile() << std::endl;
	outfile << gameObjects["SpaceStation"]->ToFile() << std::endl;
	outfile.close();

	std::cout << "-------------------------------------------------------------------------------\n";
	std::cout << " END OF OUTPUT - STARTING INPUT \n";
	std::cout << "-------------------------------------------------------------------------------\n\n";

	std::ifstream infile;
	std::string fileName = "GameObject.txt";

	infile.open(fileName.c_str());

	// If file is open
	if (infile.is_open())
	{
		int id;
		float x, y;
		std::string name;

		while (!infile.fail())
		{
			infile >> id >> name;
			infile.ignore(1, ' ');
			infile.ignore(1, '(');
			infile >> x;
			infile.ignore(1, ',');
			infile.ignore(1, ' ');
			infile >> y;
			infile.ignore(1, ')');

			auto* temp_object = new GameObject(name, id, x, y);

			gameObjects[name + " 2"] = temp_object;
		}
		infile.close();
	}




	// for every game_object in gameObjects...loop
	for (const auto& game_object : gameObjects)
	{
		std::cout << "Key  : " << game_object.first << std::endl;
		std::cout << "Value: " << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << game_object.second->ToString() << std::endl;
	}

	std::cout << "------------------------------------------------------------------------------------------------\n";
	std::cout << " END OF INPUT \n";
	std::cout << "------------------------------------------------------------------------------------------------\n\n";

}
