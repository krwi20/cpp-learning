#include <iostream>
#include <string>
#include <curl/curl.h>

// Callback function: libcurl writes received data here
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

std::string fetch_url(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); // 10 sec timeout
        curl_easy_setopt(curl, CURLOPT_CAINFO, "C:/msys64/ucrt64/etc/ssl/certs/ca-bundle.crt");

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << "\n";
            return "";
        }
    }
    return response;
}

std::string extract_json_value(const std::string& json, const std::string& key) {
    // build the pattern we are looking for key:
    std::string pattern = "\"" + key + "\":\"";

    size_t start = json.find(pattern);
    if (start == std::string::npos) {
        return ""; // key not found
    }

    // move past the pattern to the start of the value
    start += pattern.length();

    // find the closing quote
    size_t end = json.find("\"", start);
    if (end == std::string::npos) {
        return ""; // no closing quote
    }

    // extract substring between start and end
    return json.substr(start, end - start);
}

int main() {
    std::string url = "https://official-joke-api.appspot.com/random_joke";
    std::cout << "Fetching a joke...\n\n";

    std::string json = fetch_url(url);
    if (json.empty()) {
        std::cerr << "Failed to fetch joke.\n";
        return 1;
    }

    // Extract fields
    std::string setup = extract_json_value(json, "setup");
    std::string punchline = extract_json_value(json, "punchline");

    if (setup.empty() || punchline.empty()) {
        std::cerr << "Failed to parse joke from JSON:\n" << json << "\n";
        return 1;
    }

    // Print the joke nicely
    std::cout << "Joke:\n";
    std::cout << setup << "\n";
    std::cout << punchline << "\n\n";

    return 0;
}