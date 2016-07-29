#include <InputWrapper.h>
#include <Game.h>
#include <Engine.h>
#include <DL_Debug.h>

int main()
{
	Game game;
	Easy3D::Engine engine({ 1280.f, 720.f }, game);

	engine.Run();

	return 0;
}