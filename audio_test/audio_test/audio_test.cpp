// audio_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
int main()
{
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	SoundBuffer buffer;
	buffer.loadFromFile("../Bear.wav");
	SoundBuffer buffer2;
	buffer2.loadFromFile("../Wind2.wav");

	std::cout << buffer.getSampleCount() << std::endl << buffer.getSampleRate() << std::endl << buffer.getChannelCount() << std::endl << buffer.getDuration().asSeconds() << std::endl;
	std::cout << buffer2.getSampleCount() << std::endl << buffer2.getSampleRate() << std::endl << buffer2.getChannelCount() << std::endl << buffer2.getDuration().asSeconds() << std::endl;


	Sound sound;

	const Int16 *samples1 = buffer.getSamples();
	int count1 = buffer.getSampleCount();

	const Int16 *samples2 = buffer2.getSamples();
	int count2 = buffer2.getSampleCount();

	int count3 = std::min(buffer.getSampleCount(), buffer2.getSampleCount());
	Int16 *samples3 = new Int16[count3];

	int sample_rate = std::min(buffer.getSampleRate(), buffer2.getSampleRate());

	for (int i = 0; i < buffer.getSampleCount() / 2 && i < buffer2.getSampleCount() / 2; i += 2)
	{
		samples3[i] = (samples1[i] + samples2[i])/2;
		samples3[i+1] = (samples1[i+1] + samples2[i+1])/2;
	}

	SoundBuffer buffer3;
	buffer3.loadFromSamples((const sf::Int16*)samples3, count3, 2, sample_rate);

	sound.setBuffer(buffer3);
	sound.play();
	
	sound.setBuffer(buffer);
	sound.play();
	/*while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/

	getchar();
	return 0;
}