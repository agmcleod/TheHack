#include "Texture.h"
#include "json/json.h"
#include <iostream>
#include <fstream>
#include "ResolvePath.h"

void Texture::cleanup() {
    for (auto region : regions) {
        delete region;
    }
}

Region * Texture::getRegion(const std::string &name) {
    Region *theRegion = nullptr;
    for (auto region : regions) {
        if (region->name == name) {
            theRegion = region;
        }
    }
    return theRegion;
}

GLuint Texture::getTextureId() {
	return textureId;
}
float Texture::getWidth() {
	return width;
}
float Texture::getHeight() {
	return height;
}

void Texture::readRegionsFromFile(const std::string &fileName) {
    Json::Value root;
    std::ifstream jsonDoc(resourcePath() + fileName, std::ifstream::binary);
    
    jsonDoc >> root;
    
    Json::Value frames = root["frames"];
    Json::Value::Members frameNames = frames.getMemberNames();
    for (auto frame : frameNames) {
        Json::Value frameObject = frames[frame];
        Json::Value frameDetails = frameObject["frame"];
        
        Region *region = new Region();
        region->name = frame;
        region->pos = sf::Vector2f(frameDetails["x"].asInt(), frameDetails["y"].asInt());
        region->width = frameDetails["w"].asInt();
        region->height = frameDetails["h"].asInt();
        regions.push_back(region);
    }
}