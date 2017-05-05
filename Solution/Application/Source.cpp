#include <windows.h>
#include <InputWrapper.h>
//#include <Game.h>
#include <Engine.h>
#include <DL_Debug.h>
#include <Game_RTS.h>

int main()
{
	//Game game;
	Game_RTS game;
	Magma::Engine engine({ 1280.f, 720.f }, game);

	engine.Run();

	return 0;
}