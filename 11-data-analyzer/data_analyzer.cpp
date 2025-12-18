#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <numeric>
#include <algorithm>

std::vector<std::string> split(const std::string &line, char delimiter)
{
    std::vector<std::string> parts; // This will hold the results
    std::stringstream ss(line);     // Turn the string into a "stream" (like a file)
    std::string part;               // Temporary place to store one piece

    // Keep reading from the stream, splitting at 'delimiter' (e.g., ',')
    while (std::getline(ss, part, delimiter))
    {
        parts.push_back(part); // Add each piece to the list
    }

    return parts; // Give back the list of pieces
}

using Record = std::map<std::string, std::string>;
using Dataset = std::vector<Record>;

Dataset load_csv(const std::string &filename)
{
    Dataset data;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Could not open file: " << filename << "\n";
        return data;
    }

    std::string line;

    // Read header (first line)
    std::getline(file, line);
    auto headers = split(line, ',');

    // Read each data row
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        auto values = split(line, ',');

        // Skip rows that don't match header count
        if (values.size() != headers.size())
            continue;

        // Build a Record: header[i] -> values[i]
        Record record;
        for (size_t i = 0; i < headers.size(); ++i)
        {
            record[headers[i]] = values[i];
        }
        data.push_back(record);
    }

    file.close();
    return data;
}

int total_sales(const Dataset &data)
{
    return std::accumulate(data.begin(), data.end(), 0, [](int sum, const Record &record)
                           { return sum + std::stoi(record.at("Sales")); });
}

std::string top_region(const Dataset &data)
{
    if (data.empty())
    {
        return "N/A";
    }

    auto it = std::max_element(data.begin(), data.end(), [](const Record &a, const Record &b)
                               {
                                   int salesA = std::stoi(a.at("Sales"));
                                   int salesB = std::stoi(b.at("Sales"));
                                   return salesA < salesB; // true means "a comes before b" -> so b is bigger
                               });
    return it->at("Region");
}

Dataset filter_by_product(const Dataset &data, const std::string &product)
{
    Dataset result;
    std::copy_if(data.begin(), data.end(), std::back_inserter(result), [&product](const Record &record)
                 { return record.at("Product") == product; });
    return result;
}

int main()
{

    auto data = load_csv("sales.csv");
    std::cout << "Loaded " << data.size() << " records.\n";

    for (const auto &record : data)
    {
        std::cout << "Region: " << record.at("Region") << ", Product: " << record.at("Product") << ", Sales: " << record.at("Sales") << "\n";
    }

    std::cout << "Total Sales: $" << total_sales(data) << "\n";
    std::cout << "Top Region: " << top_region(data) << "\n";

    std::cout << "\nWidget Sales:\n";
    auto widgetSales = filter_by_product(data, "Widget");
    for (const auto &record : widgetSales)
    {
        std::cout << "- " << record.at("Region")
                  << ": $" << record.at("Sales") << "\n";
    }

    return 0;
}