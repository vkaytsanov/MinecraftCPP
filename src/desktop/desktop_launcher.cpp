
#include "../lib/include/configuration.h"
#include "../lib/include/application.h"
#include "../core/include/playground.h"

int main(int argc, char* args[]) {
	auto* config = new Configuration("OpenGL App", 960, 480);

	auto* app = new Application(new Playground(), config);

	delete app;
	return 0;
}