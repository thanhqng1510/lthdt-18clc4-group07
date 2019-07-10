#pragma once

enum class LOG_IN_KEY {
	EMAIL = 0,
	USERNAME = 1
};

class MainMenu {
private:
	// Log in with username or email
	static void LogIn(LOG_IN_KEY key);
	static void CreateAccount();

private:
	unsigned int m_option;

public:
	inline MainMenu() : m_option(0) {}

public:
	// Show all option available and ask for user's input
	void Process();
};
