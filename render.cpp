#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

constexpr int FRAME_DELAY = 50;

class CrashProt {
public:
    CrashProt() { std::cout << "\033[?25l"; }
    ~CrashProt() { std::cout << "\033[?25h" << std::flush; }
};

void clear_screen() {
    std::cout << "\033[H";
}

void render_frame(const std::vector<std::string>& frame) {
    clear_screen();
    for (const auto& line : frame)
        std::cout << line << "\n";
    std::cout.flush();
}

int main() {
    CrashProt cursor;
    std::vector<std::string> frame;
    std::string line;

    while (true) {
        frame.clear();
        while (std::getline(std::cin, line)) {
            if (line == "---") break;
            frame.push_back(line);
        }

        if (!frame.empty()) render_frame(frame);
        if (std::cin.eof()) break;

        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
    }
    return 0;
}
