//
//  main.cpp
//  Challenge
//
//  Created by vamshikrishna vanam on 30/04/24.
//

#include <iostream>
#include "httplib.h"
#include "json.hpp"
#include "string.h"
#include "map"
#include "iterator"
#include "cmdparser.hpp"
using json = nlohmann::json;
using namespace std;
using namespace httplib;


struct Light {
    string id;
    string name;
    string room;
    unsigned int brightness;
    string on;
    Light() : id(""), name(""), room(""), brightness(0), on("") {}
};
map<string, Light> getInitialLightsState(Client& client, json& lightsJson);
void monitorLightChanges(Client& client, map<string, Light>& initialLightsState);
Light getLightDetails(Client& client, string& id);
bool isEmpty(Light& light);

int main(int argc, char* argv[])
{
    Client client("http://localhost:8080");
    json lightsJson;
    map<string, Light> initalLightsState = getInitialLightsState(client, lightsJson);
    cout << lightsJson.dump(4) << endl;
    while (1) {
        monitorLightChanges(client, initalLightsState);
    }
    
}


Light getLightDetails(Client& client, string& id){
    Light light;
    auto res = client.Get("/lights/" + id);
    if(res && res->status == 200){
        try {
            auto lightJson = json::parse(res->body);
            if(lightJson.contains("name"))
                light.name = lightJson["name"];
            if(lightJson.contains("room"))
                light.room = lightJson["room"];
            if(lightJson.contains("on"))
                light.on = lightJson["on"] ? "true" : "false";
            if(lightJson.contains("brightness"))
                light.brightness = lightJson["brightness"];
            float convertedBrightness = light.brightness * 0.392;
            light.brightness = convertedBrightness;
        } catch (exception e) {
            cerr << "Error: parsing unsucessful " << e.what() << endl;
        }
    }
    return light;
}

map<string, Light> getInitialLightsState(Client& client, json& lightsJson) {
    map<string, Light> initialLightsState;
    auto res = client.Get("/lights");
    if (res && res->status == 200) {
        auto initialLightsJson = json::parse(res->body);
        if(!initialLightsJson.empty()){
            lightsJson = initialLightsJson;
        }
        for (const auto& lightJson : lightsJson) {
            string id = lightJson["id"];
            Light light = getLightDetails(client,id);
            initialLightsState[id] = light;
        }
    }
    else {
        std::cout << "Unable to fetch initial Light state " << std::endl;
        std::cout << "Please try again later " << std::endl;
        exit(1);
    }
    return initialLightsState;
}

bool isEmpty(Light& light) {
        return light.id.empty() && light.name.empty() && light.room.empty() && light.brightness == 0 && light.on.empty();
    }

void monitorLightChanges(Client& client, map<string, Light>& initialLightsState){
    auto res = client.Get("/lights");
    map<string, Light> currentLightsState;
    if (res && res->status == 200) {
        auto lightsJson = json::parse(res->body);
        for (const auto& lightJson : lightsJson) {
            string id = lightJson["id"];
            Light currentLight = getLightDetails(client, id);
            if(!(isEmpty(currentLight))){
                currentLightsState[id] = currentLight;
            }
        }
    }
    for (auto it = currentLightsState.begin(); it != currentLightsState.end(); it++) {
        string id = it->first;
        Light currentLight = it->second;
        if (initialLightsState.find(id) != initialLightsState.end()) {
            Light initialLight = initialLightsState[id];
            if (initialLight.brightness != currentLight.brightness) {
                json newJsonData;
                newJsonData["id"] = id;
                newJsonData["brightness"] = currentLight.brightness;
                cout << newJsonData.dump(4) << endl;
            }
            if (initialLight.on != currentLight.on) {
                json newJsonData;
                newJsonData["id"] = id;
                newJsonData["on"] = currentLight.on;
                cout << newJsonData.dump(4) << endl;
            }
            if (initialLight.name != currentLight.name) {
                json newJsonData;
                newJsonData["id"] = id;
                newJsonData["name"] = currentLight.name;
                cout << newJsonData.dump(4) << endl;
            }
            if (initialLight.room != currentLight.room) {
                json newJsonData;
                newJsonData["id"] = id;
                newJsonData["room"] = currentLight.room;
                cout << newJsonData.dump(4) << endl;
            }
        }
        else {
            json newJsonData;
            newJsonData["id"] = id;
            newJsonData["name"] = currentLight.name;
            newJsonData["room"] = currentLight.room;
            newJsonData["brightness"] = currentLight.brightness;
            newJsonData["on"] = currentLight.on;
            cout << newJsonData.dump(4) << endl;
        }
    }

    for (auto it = initialLightsState.begin(); it != initialLightsState.end(); it++) {
        string id = it->first;
        Light initialLight = it->second;
        if (!(currentLightsState.find(id) != currentLightsState.end())) {
            cout << initialLight.name << " (" << id << ") has been removed" << endl;
        }
    }
    initialLightsState = currentLightsState;
}
