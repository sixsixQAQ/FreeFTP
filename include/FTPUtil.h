#pragma once

#include <functional>
#include <string>

class FTPUtil {
public:
	FTPUtil(const std::string& host, const std::string& user, const std::string& password);
	void connectToServer(
		std::function<void(bool succeeded)> callback = nullptr
	) const;

	void listFile(
		const std::string& path,
		std::function<void(bool succeeded, const std::vector<std::string>& result)>callback = nullptr
	)const;

	void listFileNameOnly(
		const std::string& path,
		std::function<void(bool succeeded, const std::vector<std::string>& result)>callback = nullptr
	)const;

private:
	const std::string m_host = "";
	const std::string m_user = "";
	const std::string m_password = "";
};