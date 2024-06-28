#pragma once

#include <functional>
#include <string>

class FTPUtil {
public:

	static void connectToServer (
		const std::string &host,
		const std::string &user,
		const std::string &password,
		std::function<void (bool succeeded)> callback = nullptr
	);
};