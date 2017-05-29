#include <windows.h>
#include <InputWrapper.h>
#include <RTS_Game.h>
#include <Engine.h>
#include <DL_Debug.h>

int main()
{
	RTS_Game game;
	Magma::Engine engine({ 1280.f, 720.f }, game);

	engine.Run();

	return 0;
}