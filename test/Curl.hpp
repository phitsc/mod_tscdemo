#pragma once

#include <curl/curl.h>

#include <string>

class Curl
{
public:
    Curl()
    {
        curl_global_init(CURL_GLOBAL_ALL);
        m_handle = curl_easy_init();

        curl_easy_setopt(m_handle, CURLOPT_WRITEFUNCTION, &curlWriteData);
    }

    std::string get(const std::string& url) const
    {
        std::string result;

        curl_easy_setopt(m_handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(m_handle, CURLOPT_WRITEDATA, &result);

        if (curl_easy_perform(m_handle) == CURLE_OK)
        {
            return result;
        }
        else
        {
            // should throw an exception here
            return "";
        }
    }

    ~Curl()
    {
        curl_easy_cleanup(m_handle);
        curl_global_cleanup();
    }

private:
    static size_t curlWriteData(void* buffer, size_t size, size_t nmemb, void* userp)
    {
        std::string* result = (std::string*)userp;
        (*result) += std::string((const char*)buffer, size * nmemb);

        return size * nmemb;
    }

    void* m_handle;
};

