#define SDL_MAIN_HANDLED

#include "application.h"

int main(int argc, char *args[]) {

    Application application{"App"};
    application.run();
    return 0;
}
