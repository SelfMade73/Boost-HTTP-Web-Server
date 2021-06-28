/// @file worker.h
/// @brief Handler for http connection
/// @author Agafonov Aleksey
/// @date 24.04.2021


#ifndef HTTP_SERVER_WORKER_H
#define HTTP_SERVER_WORKER_H

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core/flat_buffer.hpp>


namespace http_server
{
using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

using Controllers = std::map<std::string, std::map<http::verb,
        std::function<void(http::request<http::dynamic_body>&,http::response<http::dynamic_body>& )>>>;


/// @brief Class handles http connection
class Worker {
public:
    Worker ( const Worker& other) = delete;
    Worker& operator=(const Worker& other ) = delete;

    explicit Worker( tcp::acceptor& acceptor, Controllers& controllers );

    /// @brief Run http connection processing
    void Start();

private:
    /// @brief Wait for client
    void Accept();

    /// @brief Read request from client
    void ReadRequest();

    /// @brief Process request from client
    /// @details Checks method , target
    void ProcessRequest();

    /// @brief Send response to client
    void SendResponse();

private:
    Controllers& controllers_;
    tcp::acceptor& acceptor_;
    tcp::socket socket{acceptor_.get_executor()};
    http::request<http::dynamic_body> request;
    http::response<http::dynamic_body> response;
    boost::beast::flat_buffer buffer{8192};
};

}

#endif //HTTP_SERVER_WORKER_H
