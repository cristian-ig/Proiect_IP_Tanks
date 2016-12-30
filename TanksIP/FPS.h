#pragma once
#include<SDL.h>
namespace tanks {
	class FPS
	{
	public:
		FPS();
		~FPS();


		void init(float maximumFPS);
		void start();
		float end();
	private:

		void calculate();

		float _fps;
		float _maximumFPS;
		float _frameTime;
		int _startTicks;
	};
}