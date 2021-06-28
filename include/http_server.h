/// @file http_server.h
/// @brief Http server definition
/// @author Agafonov Aleksey
/// @date 21.04.2021


#ifndef HTTP_SERVER_HTTP_SERVER_H
#define HTTP_SERVER_HTTP_SERVER_H

#include <cstdint>
#include <vector>
#include <memory>
#include <map>

#include <boost/asio.hpp>
#include <http_server/include/worker.h>
#include <boost/beast/http.hpp>
#include <boost/beast.hpp>

namespace http_server
{
namespace http = boost::beast::http;
using namespace boost::beast::http;

/// @brief Class for http - server
class HttpServer {

public:
    /// @brief < method > < target >
    Controllers controlUrls;

public:

    /// @param port port for listening
    explicit HttpServer(uint16_t port);

    /// @brief Run server
    void Run();

private:
    boost::asio::io_context context{1};
    std::unique_ptr<Worker> worker = nullptr;
    uint16_t port_;
};



}

#endif //HTTP_SERVER_HTTP_SERVER_H
