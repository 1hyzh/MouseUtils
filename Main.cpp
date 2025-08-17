#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>
#include <atomic>
#include <sstream>

std::atomic<bool> running(true); // Shared flag between threads

void monitorMouse()
{
    POINT lastPos = { 0, 0 };
    GetCursorPos(&lastPos);

    while (running) {
        POINT currentPos;

        if (GetCursorPos(&currentPos)) {
            if (lastPos.x != currentPos.x || lastPos.y != currentPos.y) {
                std::cout << currentPos.x << ", " << currentPos.y << std::endl << ">";
                lastPos = currentPos;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void inputHandler()
{
    std::string line;

    std::cout << "Type coordinates like: `500 300` to move the mouse.\n";
    std::cout << "Type `exit` to stop.\n";
    std::cout << "Type `?` or `help` to see available actions.\n";

    while (running) {
        std::getline(std::cin, line);
        
        if (line == "?") {
            std::cout << "<x> <y> to move the mouse there." << std::endl << "center: center the mouse" << std::endl << "exit\n" << ">";
        }
        
        if (line == "help") {
            std::cout << "<x> <y> to move the mouse there." << std::endl << "center: center the mouse" << std::endl << "exit\n" << ">";
        }

        if (line == "center") {
            SetCursorPos(500000, 500000);
            POINT maxPos;
            GetCursorPos(&maxPos);
            POINT centerPos;
            centerPos.x = maxPos.x / 2;
            centerPos.y = maxPos.y / 2;
            SetCursorPos(centerPos.x, centerPos.y);
        }
        if (line == "exit") {
            running = false;
            break;
        }

        int x, y;
        std::istringstream iss(line);
        if (iss >> x >> y) {
            SetCursorPos(x, y);
            std::cout << "Moved mouse to: " << x << ", " << y << std::endl;
        }
        else {
            
        }
    }
}

int main()
{
    std::thread mouseThread(monitorMouse);   // Thread to monitor mouse movement
    std::thread inputThread(inputHandler);   // Thread to handle user input

    mouseThread.join();
    inputThread.join();

    std::cout << "Program exited." << std::endl;
    return 0;
}
