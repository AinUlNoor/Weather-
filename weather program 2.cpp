#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;
const int MAX_LOCATIONS = 50;

class Location
 {
public:
    string name;
    double latitude;
    double longitude;

    Location() : name(""), latitude(0), longitude(0) {}
    Location(string n, double lat, double lon) : name(n), latitude(lat), longitude(lon) {}

    void print() const
	 {
        cout << name << " (Lat: " << latitude << ", Lon: " << longitude << ")" << endl;
    }
};

class LocationManager 
{
private:
    Location locations[MAX_LOCATIONS];
    int locationCount;

public:
    LocationManager() : locationCount(0) {}

    void addLocation(const string& name, double latitude, double longitude)
	 {
        if (locationCount < MAX_LOCATIONS)
		 {
            locations[locationCount++] = Location(name, latitude, longitude);
        } 
		else 
		{
            cout << "Location list is full!" << endl;
        }
    }

    void removeLocation(const string& name) 
	{
        for (int i = 0; i < locationCount; ++i)
		 {
            if (locations[i].name == name)
			 {
                for (int j = i; j < locationCount - 1; ++j)
				 {
                    locations[j] = locations[j + 1];
                }
                --locationCount;
                break;
            }
        }
    }

    void listLocations() const 
	{
        for (int i = 0; i < locationCount; ++i) 
		{
            locations[i].print();
        }
    }

    Location* getLocation(int index)
	 {
        if (index >= 0 && index < locationCount)\
		 {
            return &locations[index];
        } 
		else
		 {
            return nullptr;
        }
    }

    int getLocationCount() const 
	{
        return locationCount;
    }
};

class WeatherVariable
 {
public:
    string name;
    double value;

    WeatherVariable(string n, double v) : name(n), value(v) {}
};

class WeatherVariableManager
 {
private:
    vector<WeatherVariable> variables;

public:
    void addVariable(const string& name, double value)
	 {
        variables.push_back(WeatherVariable(name, value));
    }

    void removeVariable(const string& name) 
	{
        variables.erase(remove_if(variables.begin(), variables.end(), [&](const WeatherVariable& var) { return var.name == name; }), variables.end());
    }

    void listVariables() const
	 {
        for (const auto& var : variables) {
            cout << var.name << ": " << var.value << endl;
        }
    }
};

class WeatherForecastingSystem 
{
private:
    string apiKey;
    string baseUrl;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s)
	 {
        size_t totalSize = size * nmemb;
        s->append((char*)contents, totalSize);
        return totalSize;
    }

public:
    WeatherForecastingSystem(const string& key) : apiKey(key), baseUrl("https://api.openweathermap.org/data/2.5/weather") {}

    string fetchForecast(double latitude, double longitude
	) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl)
		 {
            string url = baseUrl + "?lat=" + to_string(latitude) + "&lon=" + to_string(longitude) +
                         "&units=metric&appid=" + apiKey;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }


    void displayForecast(const string& forecastData)
	 {
        auto jsonData = json::parse(forecastData);
        cout << "Weather Forecast for " << jsonData["name"] << ":\n";
        cout << "Temperature: " << jsonData["main"]["temp"] << "°C\n";
        cout << "Weather: " << jsonData["weather"][0]["description"] << endl;
    }

    void exportToCSV(const string& filename, const string& data)
	 {
        ofstream file(filename);
        file << data;
        file.close();
    }

    void exportToJSON(const string& filename, const string& data) 
	{
        auto jsonData = json::parse(data);
        ofstream file(filename);
        file << jsonData.dump(4);
        file.close();
    }
};

class HistoricalWeatherSystem 
{
private:
    string apiKey;
    string baseUrl;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
        size_t totalSize = size * nmemb;
        s->append((char*)contents, totalSize);
        return totalSize;
    }

public:
    HistoricalWeatherSystem(const string& key) : apiKey(key), baseUrl("https://api.openweathermap.org/data/2.5/onecall/timemachine") {}

    string fetchHistoricalWeather(double latitude, double longitude, time_t timestamp) 
	{
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl) 
		{
            string url = baseUrl + "?lat=" + to_string(latitude) + "&lon=" + to_string(longitude) +
                         "&dt=" + to_string(timestamp) + "&units=metric&appid=" + apiKey;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }

    void displayHistoricalWeather(const string& historicalData) 
	{
        auto jsonData = json::parse(historicalData);
        cout << "Historical Weather Data:\n";
        cout << "Temperature: " << jsonData["current"]["temp"] << "°C\n";
        cout << "Weather: " << jsonData["current"]["weather"][0]["description"] << endl;
    }

    void exportToCSV(const string& filename, const string& data)
	 {
        ofstream file(filename);
        file << data;
        file.close();
    }

    void exportToJSON(const string& filename, const string& data) 
	{
        auto jsonData = json::parse(data);
        ofstream file(filename);
        file << jsonData.dump(4);
        file.close();
    }
};

int main()
 {
    // Initialize the location manager
    LocationManager locManager;
    locManager.addLocation("San Francisco", 37.7749, -122.4194);
    locManager.addLocation("New York", 40.7128, -74.0060);
    locManager.addLocation("Los Angeles", 34.0522, -118.2437);

    // List all locations
    cout << "Locations:" << endl;
    locManager.listLocations();

    string apiKey = "e38f50f36824b6c330111ced5ecd0770";  //API key
    WeatherForecastingSystem weatherSystem(apiKey);

    // Fetch and display weather forecast for a location
    if (locManager.getLocationCount() > 0) 
	{
        Location* loc = locManager.getLocation(0);
        string forecastData = weatherSystem.fetchForecast(loc->latitude, loc->longitude);
        weatherSystem.displayForecast(forecastData);

        // Export weather data
        weatherSystem.exportToCSV("weather.csv", forecastData);
        weatherSystem.exportToJSON("weather.json", forecastData);
    }
	 else
	  {
        cout << "No locations available for weather forecast." << endl;
    }

    // Historical weather data
    HistoricalWeatherSystem historicalSystem(apiKey);
    time_t timestamp = time(0) - 86400 * 7; // 1 week ago
    if (locManager.getLocationCount() > 0)
	 {
        Location* loc = locManager.getLocation(0);
        string historicalData = historicalSystem.fetchHistoricalWeather(loc->latitude, loc->longitude, timestamp);
        historicalSystem.displayHistoricalWeather(historicalData);

        // Export historical weather data
        historicalSystem.exportToCSV("historical_weather.csv", historicalData);
        historicalSystem.exportToJSON("historical_weather.json", historicalData);
    } 
	else 
	{
        cout << "No locations available for historical weather data." << endl;
    }

    return 0;
}
