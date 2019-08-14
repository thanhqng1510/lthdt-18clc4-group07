#pragma once

enum class LOG_IN_KEY {
	EMAIL = 0,
	USERNAME = 1
};

class MainMenu {
private:
	static void LogIn(LOG_IN_KEY key);
	static void CreateAccount();

public:
	static void GetOptionInput(unsigned int& option);

private:
	unsigned int m_option;

public:
	MainMenu();

public:
	void Show();
};
