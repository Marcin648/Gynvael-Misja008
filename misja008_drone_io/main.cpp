#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <iomanip>

#include <SFML/Graphics.hpp>
#include <IOPacket.h>


void viewRecalc(sf::View &view, sf::RenderWindow &window, vector<sf::Vertex> &points){
	sf::Vector2f maxView = view.getSize();
	for(unsigned int i = 0; i < points.size(); i++){
		maxView.x = max(maxView.x, points.at(i).position.x);
		maxView.y = max(maxView.y, points.at(i).position.y);
	}
	
	sf::Vector2f newView;
	
	if((window.getSize().y * maxView.x) / maxView.y > window.getSize().x){  //aspect ratio 16:9
		newView.x = maxView.x;
		newView.y = (maxView.x * 9.f)/16.f;
	}else{
		newView.x = (maxView.y * 16.f)/9.f;
		newView.y = maxView.y;
	}
	view.setSize(newView);
	view.setCenter(newView / 2.0f);
	window.setView(view);
}

int main(int argc, char **argv)
{
	cout << argv[1] << endl;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "misja008_drone_io");
	//window.setFramerateLimit(60);

	sf::View view(sf::FloatRect(0, 0, 1, 1));
	
	vector<sf::Vertex> points;
	IOPacket packet("68eb1a7625837e38d55c54dc99257a17.txt");
	packet.createPoints(points);
	
	viewRecalc(view, window, points);
	
	set<string> visited;
	
	stack<string> ckStack;
	//queue<string> ckStack;
	
	sf::Texture droneTex;
	if (!droneTex.loadFromFile("drone.png"))
	{
		cout << "load texture drone.png failed" << endl;
		droneTex.create(250, 250);
	}
	
	sf::Sprite drone;
	drone.setPosition(packet.position);
	drone.setTexture(droneTex);
	drone.setScale(0.07f, 0.07f);
	drone.setOrigin(droneTex.getSize().x/2.0f,
					droneTex.getSize().y/2.0f);
	
	
	sf::Font font;
	font.loadFromFile("Roboto-Regular.ttf");
	
	sf::Text droneModeText("DRONE: MANUAL", font);
	droneModeText.setFillColor(sf::Color::Green);
	droneModeText.setCharacterSize(12);
	
	bool explore = false;
	uint64_t frameCounter = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
			if (event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Up && !explore){
					if(packet.dirHash[IOPacket::Direction::N] != "not"){
						packet = IOPacket(packet.dirHash[IOPacket::Direction::N]);
						packet.createPoints(points);
					}
					
				}
				if(event.key.code == sf::Keyboard::Down && !explore){
					if(packet.dirHash[IOPacket::Direction::S] != "not"){
						packet = IOPacket(packet.dirHash[IOPacket::Direction::S]);
						packet.createPoints(points);
					}
				}
				if(event.key.code == sf::Keyboard::Right && !explore){
					if(packet.dirHash[IOPacket::Direction::E] != "not"){
						packet = IOPacket(packet.dirHash[IOPacket::Direction::E]);
						packet.createPoints(points);
					}
				}
				if(event.key.code == sf::Keyboard::Left && !explore){
					if(packet.dirHash[IOPacket::Direction::W] != "not"){
						packet = IOPacket(packet.dirHash[IOPacket::Direction::W]);
						packet.createPoints(points);
					}
				}
				if(event.key.code == sf::Keyboard::E){
					explore = !explore;
					if(explore){
						droneModeText.setString("DRONE: AUTOPILOT");
						while(!ckStack.empty()) ckStack.pop();
						ckStack.push(packet.HashStr);
					}else{
						droneModeText.setString("DRONE: MANUAL");
					}
				}
				
				if(event.key.code == sf::Keyboard::S){
					stringstream fileName;
					fileName << "screen\\" << setfill('0') << setw(20) << frameCounter << ".bmp";
					sf::Texture screenShot;
					screenShot.create(window.getSize().x, window.getSize().y);
					screenShot.update(window);
					screenShot.copyToImage().saveToFile(fileName.str());
				}
				
				viewRecalc(view, window, points);
				drone.setPosition(packet.position);
			}
        }
		
		if(explore){
			
			visited.insert(packet.HashStr); 
			
			/* ckStack list operations */
			
			if(packet.seeWall){ //if wall is near then check neighbours
				for(int i = 0; i < 4; i++){ //add know neighbours
					if(packet.dirHash[i] != "not"){
						ckStack.push(packet.dirHash[i]);
					}
				}
				
				//add other neighbours
				if(packet.dirHash[IOPacket::Direction::N] != "not"){ 
					IOPacket n(packet.dirHash[IOPacket::Direction::N]);
					if(n.dirHash[IOPacket::Direction::E] != "not"){
						ckStack.push(n.dirHash[IOPacket::Direction::E]);  // add NE
					}
					if(n.dirHash[IOPacket::Direction::W] != "not"){
						ckStack.push(n.dirHash[IOPacket::Direction::W]); // add NW
					}
				}
				
				if(packet.dirHash[IOPacket::Direction::S] != "not"){
					IOPacket s(packet.dirHash[IOPacket::Direction::S]);
					if(s.dirHash[IOPacket::Direction::E] != "not"){ 
						ckStack.push(s.dirHash[IOPacket::Direction::E]); // add SE
					}
					if(s.dirHash[IOPacket::Direction::W] != "not"){
						ckStack.push(s.dirHash[IOPacket::Direction::W]); // add SW
					}
				}
				
				if(packet.dirHash[IOPacket::Direction::W] != "not"){
					IOPacket w(packet.dirHash[IOPacket::Direction::W]);
					if(w.dirHash[IOPacket::Direction::N] != "not"){
						ckStack.push(w.dirHash[IOPacket::Direction::N]); // add NW
					}
					if(w.dirHash[IOPacket::Direction::S] != "not"){
						ckStack.push(w.dirHash[IOPacket::Direction::S]); // add SW
					}
				}
				
				if(packet.dirHash[IOPacket::Direction::E] != "not"){
					IOPacket e(packet.dirHash[IOPacket::Direction::E]);
					if(e.dirHash[IOPacket::Direction::N] != "not"){
						ckStack.push(e.dirHash[IOPacket::Direction::N]); // add NE
					}
					if(e.dirHash[IOPacket::Direction::S] != "not"){
						ckStack.push(e.dirHash[IOPacket::Direction::S]); // add SE
					}
				}
				
			}
			
			/* pocket operation */
			
			packet.createPoints(points);
			viewRecalc(view, window, points);
			drone.setPosition(packet.position);
			
			/* set new pocket */
			
			
			while(!ckStack.empty() && visited.count(ckStack.top()) > 0){ //pop visited location
				ckStack.pop();
			}
			
			if(ckStack.empty()){ //stop explore if ckStack empty
				explore = false;
				droneModeText.setString("DRONE: MANUAL");
				continue;
			}
			
			packet = IOPacket(ckStack.top());
			
		}
		
        window.clear(sf::Color::Black);
		
		
		for(unsigned int i = 0; i < points.size(); i++){
			window.draw(&points.at(i), 1, sf::Points);
		}
		
		
		#ifdef DEBUG
		size_t visited_size = visited.size();
		size_t ckStack_size = ckStack.size();
		#endif
		
		
		window.draw(drone);
		
		window.setView(window.getDefaultView());
		window.draw(droneModeText);
		window.setView(view);
		
        window.display();
		
		frameCounter++;
	}
	
    return 0;
}