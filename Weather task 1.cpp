#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;
const int MAX_LOCATIONS = 50; // Location size 

class Location // main class location 
{
public:
	//Atributes
    string name;
    double latitude;
    double longitude;

    //Constructor
    Location() : name(""), latitude(0), longitude(0) {}

    //Perimerterized constructor
    Location(string n, double lat, double lon) : name(n), latitude(lat), longitude(lon) {}

    // Function for displaying data
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
        if (index >= 0 && index < locationCount)
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
    WeatherForecastingSystem(const string& key) : apiKey(key), baseUrl("https://openweathermap.org/") {} // Instead of meteo I am using open weather map and its api key to fetch weather location

    string fetchForecast(double latitude, double longitude) 
	{
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl) 
		{
            string url = baseUrl + "?latitude=" + to_string(latitude) + "&longitude=" + to_string(longitude) +
                         "&hourly=temperature_2m,wind_speed_10m&current_weather=true&apikey=" + apiKey;
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }

    void displayForecast(const string& forecastData) {
        cout << "Forecast Data: " << forecastData << endl;
    }
};

int main()
 {
    // Initialize the location manager
    LocationManager locManager;
    locManager.addLocation("San Francisco", 37.7749, -122.4194);
    locManager.addLocation("New York", 40.7128, -74.0060);
    locManager.addLocation("Los Angeles", 34.0522, -118.2437);
    locManager.addLocation("Chicago", 41.8781, -87.6298);
    locManager.addLocation("Houston", 29.7604, -95.3698);
    locManager.addLocation("Phoenix", 33.4484, -112.0740);
    locManager.addLocation("Philadelphia", 39.9526, -75.1652);
    locManager.addLocation("San Antonio", 29.4241, -98.4936);
    locManager.addLocation("San Diego", 32.7157, -117.1611);
    locManager.addLocation("Dallas", 32.7767, -96.7970);
    locManager.addLocation("San Jose", 37.3382, -121.8863);
    locManager.addLocation("Austin", 30.2672, -97.7431);
    locManager.addLocation("Jacksonville", 30.3322, -81.6557);
    locManager.addLocation("Fort Worth", 32.7555, -97.3308);
    locManager.addLocation("Columbus", 39.9612, -82.9988);
    locManager.addLocation("Charlotte", 35.2271, -80.8431);
    locManager.addLocation("San Francisco", 37.7749, -122.4194);
    locManager.addLocation("Indianapolis", 39.7684, -86.1581);
    locManager.addLocation("Seattle", 47.6062, -122.3321);
    locManager.addLocation("Denver", 39.7392, -104.9903);
    locManager.addLocation("Washington", 38.9072, -77.0369);
    locManager.addLocation("Boston", 42.3601, -71.0589);
    locManager.addLocation("El Paso", 31.7619, -106.4850);
    locManager.addLocation("Nashville", 36.1627, -86.7816);
    locManager.addLocation("Detroit", 42.3314, -83.0458);
    locManager.addLocation("Oklahoma City", 35.4676, -97.5164);
    locManager.addLocation("Portland", 45.5152, -122.6784);
    locManager.addLocation("Las Vegas", 36.1699, -115.1398);
    locManager.addLocation("Memphis", 35.1495, -90.0490);
    locManager.addLocation("Louisville", 38.2527, -85.7585);
    locManager.addLocation("Baltimore", 39.2904, -76.6122);
    locManager.addLocation("Milwaukee", 43.0389, -87.9065);
    locManager.addLocation("Albuquerque", 35.0844, -106.6504);
    locManager.addLocation("Tucson", 32.2226, -110.9747);
    locManager.addLocation("Fresno", 36.7378, -119.7871);
    locManager.addLocation("Sacramento", 38.5816, -121.4944);
    locManager.addLocation("Kansas City", 39.0997, -94.5786);
    locManager.addLocation("Mesa", 33.4152, -111.8315);
    locManager.addLocation("Atlanta", 33.7490, -84.3880);
    locManager.addLocation("Omaha", 41.2565, -95.9345);
    locManager.addLocation("Raleigh", 35.7796, -78.6382);
    locManager.addLocation("Miami", 25.7617, -80.1918);
    locManager.addLocation("Long Beach", 33.7701, -118.1937);
    locManager.addLocation("Virginia Beach", 36.8529, -75.9780);
    locManager.addLocation("Oakland", 37.8044, -122.2711);
    locManager.addLocation("Minneapolis", 44.9778, -93.2650);
    locManager.addLocation("Tulsa", 36.1539, -95.9928);
    locManager.addLocation("Arlington", 32.7357, -97.1081);
    

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
    } 
	else
	 {
        cout << "No locations available for weather forecast." << endl;
    }

    return 0;
}
