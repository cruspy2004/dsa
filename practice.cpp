#include <iostream>
#define MAX 100 // Maximum patients allowed

int main(int argc, char* argv[]) {
    std::cout << "You passed " << argc - 1 << " arguments:\n";

    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i << ": " << argv[i] << std::endl;
    }

    return 0;
}
