/// @file http_server.h
/// @brief Http server definition
/// @author Agafonov Aleksey
/// @date 26.04.2021

#ifndef HTTP_SERVER_UTILS_H
#define HTTP_SERVER_UTILS_H

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include <string>

namespace utils
{

inline std::string jsonToString( const rapidjson::Document& json){
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json.Accept(writer);
    return std::string( buffer.GetString() , buffer.GetSize());
}

}

#endif //HTTP_SERVER_UTILS_H