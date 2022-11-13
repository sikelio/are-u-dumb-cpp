#include <iostream>
#include "Window.h"

using namespace std;

int main() {
	cout << "Creation of the GUI" << endl;

	Window* pWindow = new Window();

	bool running = true;

	while (running) {
		if (!pWindow->ProcessMessage()) {
			cout << "Closing of the GUI" << endl;
			running = false;
		}

		Sleep(10);
	}

	delete pWindow;

	return 0;
}