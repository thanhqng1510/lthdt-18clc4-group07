#pragma once

class MainMenu {
private:
	unsigned int m_option;

private:
	static void LogIn();
	static void CreateAccount();

public:
	MainMenu();
	~MainMenu() = default;

public:
	// Show all option available and ask for user's input
	void Process();
};
