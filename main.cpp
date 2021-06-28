#include <http_server/include/http_server.h>
#include <http_server/include/utils.h>

int main() {
    using namespace http_server;
    http_server::HttpServer server( 8090);

    server.controlUrls["/api/v1/get"][http::verb::get] = [](auto& req , auto& res){
        req.set( http::field::content_type, "text/html");
        boost::beast::ostream(res.body()) <<
        R"(<html><head><style>body{  background-color: #ede7f6 ;}h1 {text-align:center; color: #512da8;}
            </style></head><body><h1>BOOST REST SERVER</h1></body></html>)";
    };

    server.controlUrls["/api/v1/echo-post"][http::verb::post] = [](auto& req , auto& res){
        boost::beast::ostream(res.body()) << boost::beast::buffers_to_string(req.body().data());
    };

    server.controlUrls["/api/v1/user-agent"][http::verb::get] = [](auto& req , auto& res){
        rapidjson::Document json;
        json.SetObject();
        json.AddMember( "client", req.at( http::field::user_agent).to_string(), json.GetAllocator() );
        req.set( http::field::content_type, "application/json");
        boost::beast::ostream(res.body()) << utils::jsonToString(json);
    };

    server.Run();
    return 0;
}
