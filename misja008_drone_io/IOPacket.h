#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;
class IOPacket{
public:
	enum Direction{N, W, S, E};
	
	string HashStr;
	
	string rawData;
	
	sf::Vector2f position;
	vector<float> distance;
	string dirHash[4];
	
	bool seeWall = false;
	
	void parseRawData();
	bool isGood();
	
	
	void createPoints(vector<sf::Vertex> &points);
	
	IOPacket(string urlHash);
};