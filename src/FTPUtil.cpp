#include "FTPUtil.h"

#include "StrUtil.hpp"

#include <curl/curl.h>
#include <curl/easy.h>

FTPUtil::FTPUtil (const std::string &host, const std::string &user, const std::string &password) :
	m_host (host), m_user (user), m_password (password)
{
}

namespace ResultDeal {
size_t
strcat (void *ptr, size_t size, size_t nmemb, void *str)
{
	std::string *dest = static_cast<std::string *> (str);
	dest->append (static_cast<char *> (ptr), size * nmemb);
	return size * nmemb;
}

size_t
doNothing (void *ptr, size_t size, size_t nmemb, void *stream)
{
	(void)ptr;
	(void)size;
	(void)nmemb;
	(void)stream;
	return size * nmemb;
}

} // namespace ResultDeal

void
FTPUtil::connectToServer (std::function<void (bool succeeded)> callback) const
{
	CURL *curl = curl_easy_init();
	curl_easy_setopt (curl, CURLOPT_URL, m_host.c_str());
	curl_easy_setopt (curl, CURLOPT_USERNAME, m_user.c_str());
	curl_easy_setopt (curl, CURLOPT_PASSWORD, m_password.c_str());
	curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, ResultDeal::doNothing);
	curl_easy_setopt (curl, CURLOPT_WRITEDATA, NULL);

	CURLcode ret   = curl_easy_perform (curl);
	bool succeeded = ret == CURLE_OK;
	if (callback) {
		callback (succeeded);
	}
	curl_easy_cleanup (curl);
}

void
FTPUtil::listFile (
	const std::string &path, std::function<void (bool succeeded, const std::vector<std::string> &result)> callback
) const
{
	std::string filesInfo;
	CURL *curl			 = curl_easy_init();
	std::string fullPath = m_host;
	if (!path.empty()) {
		fullPath += "/" + path + "/";
	}
	curl_easy_setopt (curl, CURLOPT_URL, fullPath.c_str());
	curl_easy_setopt (curl, CURLOPT_USERNAME, m_user.c_str());
	curl_easy_setopt (curl, CURLOPT_PASSWORD, m_password.c_str());
	curl_easy_setopt (curl, CURLOPT_CUSTOMREQUEST, "LIST");
	curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, ResultDeal::strcat);
	curl_easy_setopt (curl, CURLOPT_WRITEDATA, &filesInfo);

	CURLcode ret   = curl_easy_perform (curl);
	bool succeeded = ret == CURLE_OK;
	if (callback) {
		auto result = StrUtil::split (filesInfo, "\r\n", true, true);
		callback (succeeded, result);
	}
	curl_easy_cleanup (curl);
}

void
FTPUtil::listFileNameOnly (
	const std::string &path, std::function<void (bool succeeded, const std::vector<std::string> &result)> callback
) const
{
	std::string fileNames;
	CURL *curl			 = curl_easy_init();
	std::string fullPath = m_host;
	if (!path.empty()) {
		fullPath += "/" + path + "/";
	}

	curl_easy_setopt (curl, CURLOPT_URL, fullPath.c_str());
	curl_easy_setopt (curl, CURLOPT_USERNAME, m_user.c_str());
	curl_easy_setopt (curl, CURLOPT_PASSWORD, m_password.c_str());
	curl_easy_setopt (curl, CURLOPT_CUSTOMREQUEST, "NLST");
	curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, ResultDeal::strcat);
	curl_easy_setopt (curl, CURLOPT_WRITEDATA, &fileNames);

	CURLcode ret   = curl_easy_perform (curl);
	bool succeeded = ret == CURLE_OK;
	if (callback) {
		auto result = StrUtil::split (fileNames, "\r\n", true, true);
		callback (succeeded, result);
	}
	curl_easy_cleanup (curl);
}
