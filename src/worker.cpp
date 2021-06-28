#include <http_server/include/worker.h>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>

#include <rapidjson/rapidjson.h>


namespace http_server
{

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

Worker::Worker(tcp::acceptor &acceptor, Controllers & controllers) : acceptor_(acceptor), controllers_(controllers){}

void Worker::Start()
{
    Accept();
}

void Worker::Accept() {
    socket = tcp::socket {acceptor_.get_executor()};
    buffer.consume(buffer.size());
    request = http::request<http::dynamic_body>();
    response = http::response<http::dynamic_body>();
    acceptor_.async_accept(
                socket,
                [this]( beast::error_code ec){
                    if ( ec ){
                        std::cerr << "Failed to accept " << ec.message() << std::endl;
                        Accept();
                    }else{
                        ReadRequest();
                    }
                });
}

void Worker::ReadRequest() {
    http::async_read(
                socket, buffer, request,
                [this](beast::error_code ec , std::size_t){
                    if ( ec ){
                        std::cerr << "Failed to read " << ec.message() << std::endl;
                        Accept();
                    }else{
                        std::cout << std::string (request.target()) << std::endl;
                        ProcessRequest();
                    }
                }
            );
}

void Worker::ProcessRequest() {
    response.keep_alive(request.keep_alive());
    response.set(http::field::server, "Test boost server");
    auto it = controllers_.find(std::string(request.target()));
    if ( it != controllers_.end()){
        auto targetIt = it->second.find( request.method() );
        if ( targetIt != it->second.end()){
            response.result(http::status::ok);
            targetIt->second(request, response);
        }else{
            beast::ostream( response.body()) << "METHOD NOT ALLOWED 405";
            response.result( http::status::method_not_allowed );
        }
    }else{
        response.result( http::status::not_found );
        beast::ostream( response.body()) << "NOT FOUND ERROR 404";
    }
    SendResponse();
}

void Worker::SendResponse() {
    response.prepare_payload();
    http::async_write(
                socket, response,
                [this]( beast::error_code ec, std::size_t ){
                    socket.shutdown(tcp::socket::shutdown_send, ec);
                    socket.close();
                    Accept();
                });
}


}

