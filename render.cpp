#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

constexpr int FRAME_DELAY = 10;

class CrashProt {
public:
    CrashProt() { std::cout << "\033[?25l"; }
    ~CrashProt() { std::cout << "\033[?25h" << std::flush; }
};

inline void clear_screen() { std::cout << "\033[H"; }

inline void render_frame(const std::vector<std::string>& frame) {
    clear_screen();
    for (const auto& line : frame)
        std::cout << line << '\n';
    std::cout.flush();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    CrashProt cursor;
    std::vector<std::string> frame;
    frame.reserve(100); // I know its overkill...

    std::string line;

    while (true) {
        frame.clear();

        while (std::getline(std::cin, line)) {
            if (line == "---") break;
            frame.push_back(std::move(line));
        }

        if (!frame.empty())
            render_frame(frame);

        if (std::cin.eof())
            break;

        if (FRAME_DELAY > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
    }
    return 0;
}
