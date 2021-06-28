#include <http_server/include/http_server.h>
#include <iostream>

namespace http_server
{

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;


HttpServer::HttpServer( uint16_t port )  : port_(port){
}

void HttpServer::Run() {
    try {
        tcp::acceptor acceptor ( context, { tcp::v4(), port_ });
        worker = std::make_unique<Worker>(acceptor, controlUrls);
        worker->Start();
        context.run();
    } catch ( const std::exception& e) {
        std::cerr << "ERROR : " << e.what() << std::endl;
    }
}


}