#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

void clear_screen() {
    std::cout << "\033[2J\033[H";
}

void render_frame(const std::vector<std::string>& frame) {
    clear_screen();
    for (const auto &l : frame) std::cout << l << "\n";
    std::cout.flush();
}

int main() {
    std::vector<std::string> frame;
    std::string line;

    std::cout << "\033[?25l";

    while (true) {
        frame.clear();
        while (std::getline(std::cin, line)) {
            if (line == "---") break;
            frame.push_back(line);
        }

        if (!frame.empty()) render_frame(frame);

        if (std::cin.eof()) break;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "\033[?25h";
    return 0;
}
