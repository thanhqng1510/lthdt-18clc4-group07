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
	void Process();
};
