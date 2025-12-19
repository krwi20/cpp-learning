#include "json.hpp"
#include <iostream>
#include <string>
#include <curl/curl.h>

using json = nlohmann::json;

// Callback function: libcurl writes received data here
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    size_t totalSize = size * nmemb;
    response->append((char *)contents, totalSize);
    return totalSize;
}

std::string fetch_url(const std::string &url)
{
    CURL *curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // 10 sec timeout
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:/msys64/ucrt64/etc/ssl/certs/ca-bundle.crt");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "GitHub-Stats-Fetcher (krwi20)");

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK)
        {
            std::cerr << "Error: " << curl_easy_strerror(res) << "\n";
            return "";
        }
    }
    return response;
}

void print_github_stats(const std::string &username)
{
    std::string url = "https://api.github.com/users/" + username;
    std::cout << "Fetching GitHub stats for: " << username << "\n\n";

    std::string response = fetch_url(url);
    if (response.empty())
    {
        std::cerr << "Failed to fetch data.\n";
        return;
    }

    try
    {
        json data = json::parse(response);

        std::string name = data.value("name", "N/A");
        int public_repos = data.value("public_repos", 0);
        int followers = data.value("followers", 0);
        int following = data.value("following", 0);

        std::cout << "GitHub Profile: " << username << "\n";
        if (name != "N/A")
            std::cout << "Name: " << name << "\n";
        std::cout << "Public Repos: " << public_repos << "\n";
        std::cout << "Followers: " << followers << "\n";
        std::cout << "Following: " << following << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        std::cerr << "Raw response:\n"
                  << response << "\n";
    }
}

int main(int argc, char *argv[])
{
    std::string username;

    if (argc > 1)
    {
        username = argv[1]; // e.g., ./github_stats krwi20
    }
    else
    {
        std::cout << "Enter GitHub username: ";
        std::cin >> username;
    }

    if (username.empty())
    {
        std::cerr << "No username provided.\n";
        return 1;
    }

    print_github_stats(username);
    return 0;
}