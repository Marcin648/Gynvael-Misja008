#include <IOPacket.h>
#include <SFML/Network.hpp>

#include <sstream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <thread>

IOPacket::IOPacket(string urlHash){
	HashStr = urlHash;
	
	fstream file;
	file.open(".\\cache\\" + urlHash, ios::in);
	
	if(file.good()){
		#ifdef DEBUG
		cout << "cached: " << urlHash << endl;
		#endif
		string line;
		while(getline(file, line)){
			rawData += line + "\n";
		}
	}else{
		sf::Http::Request request("/misja008_drone_io/scans/" + urlHash, sf::Http::Request::Get);
		sf::Http http("http://gynvael.coldwind.pl");
		sf::Http::Response response;
		
		do{
			response = http.sendRequest(request);
			
			if(response.getStatus() == sf::Http::Response::Ok){
				break;
			}
			
			cout << "request failed: " << urlHash << endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			
		}while(true);

		if (response.getStatus() == sf::Http::Response::Ok)
		{
			#ifdef DEBUG
			cout << "request OK: " << urlHash << endl;
			#endif
			rawData = response.getBody();
			
			//cache
			file.open(".\\cache\\" + urlHash, ios::out);
			if(file.good()){
				file << rawData;
			}else{
				cout << "open file failed: " << urlHash << endl;
			}
			file.close();
			
		}
		else
		{
			cout << "request failed: " << urlHash << endl;
		}
	}
	parseRawData();
}

void IOPacket::parseRawData(){
	stringstream rawDataStream(rawData);
	#ifdef DEBUG
	cout << "Parse: " << HashStr << ":" << endl;
	#endif
	string version;
	getline(rawDataStream, version);
	
	#ifdef DEBUG
	cout << "\tVersion: " << version << endl;
	#endif
	
	rawDataStream >> position.x >> position.y;
	#ifdef DEBUG
	cout << "\tPosition: " << position.x << " " << position.y << endl;
	#endif
	
	for(int i = 0; i < 36; i++){
		float dis;
		if(rawDataStream >> dis){
			distance.push_back(dis);
		}else{
			rawDataStream.clear();
			string unknown;
			getline(rawDataStream, unknown);
			if(unknown == "inf"){
				distance.push_back(INFINITY);
			}else{
					cout << "UNKNOWN LIDAR: " << unknown << endl;
				distance.push_back(INFINITY);
			}
		}
		#ifdef DEBUG
		cout << "\tLIDAR: " << distance.back() << endl;
		#endif
	}
	
	string dir;
	while(rawDataStream >> dir){
		if(dir == "MOVE_EAST:"){
			rawDataStream >> dirHash[Direction::E];
			#ifdef DEBUG
			cout << '\t' << dir << " " << dirHash[Direction::E] << endl;
			#endif
		}else if(dir == "MOVE_WEST:"){
			rawDataStream >> dirHash[Direction::W];
			#ifdef DEBUG
			cout << '\t' << dir << " " << dirHash[Direction::W] << endl;
			#endif
		}else if(dir == "MOVE_SOUTH:"){
			rawDataStream >> dirHash[Direction::S];
			#ifdef DEBUG
			cout << '\t' << dir << " " << dirHash[Direction::S] << endl;
			#endif
		}else if(dir == "MOVE_NORTH:"){
			rawDataStream >> dirHash[Direction::N];
			#ifdef DEBUG
			cout << '\t' << dir << " " << dirHash[Direction::N] << endl;
			#endif
		}else if(dir == "possible"){
			continue;
		}else{
			cout << "UNKNOWN DIR: " << dir << endl;
		}
	}
	for(int i = 0; i < 4; i++){
		if(dirHash[i] == "not"){
			seeWall = true;
			break;
		}
	}
}

bool IOPacket::isGood(){
	if(distance.size() != 36 ||
	   dirHash[Direction::N].empty() ||
	   dirHash[Direction::W].empty() ||
	   dirHash[Direction::S].empty() ||
	   dirHash[Direction::E].empty()){
		return false;
	} 
	
	return true;
}

void IOPacket::createPoints(vector<sf::Vertex> &points){
	
	for(unsigned int i = 0; i < distance.size(); i++){
		
		if(distance.at(i) == INFINITY){
			continue;
		}
		
		float a = (i*10.f)* M_PI / 180.0f ;
		float y = cosf(a) * distance.at(i);
		float x = sinf(a) * distance.at(i);
		
		sf::Vertex point;
		point.color = sf::Color(255, 255, 255);
		point.position = sf::Vector2f(position.x + x, position.y - y);

		points.push_back(point);
		
	}
}