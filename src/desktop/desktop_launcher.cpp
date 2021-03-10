#define GLEW_STATIC

#include "../lib/include/configuration.h"
#include "../lib/include/application.h"
#include "../core/include/minecraft.h"

int main(int argc, char* args[]) {
	auto* config = new Configuration("Minecraft", 960, 480);

	auto* app = new Application(new Minecraft(), config);

	delete app;
	return 0;
}