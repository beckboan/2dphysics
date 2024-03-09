#include "application.h"
#include <unistd.h>

int main(int argc, char *args[]) {

    Application application{"App"};
    application.run();
}
