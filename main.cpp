#include <iostream>

#include "boost/filesystem.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
//#include <boost/asio/ssl/error.hpp>
//#include <boost/asio/ssl/stream.hpp>

namespace fs = boost::filesystem;
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
//namespace ssl = net::ssl;
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

const std::string config_dir = "aaa";

void dir_walk(const std::string& d) {
    if (!fs::is_directory(d))
        fs::create_directory(d);

    for (auto &x : fs::directory_iterator(d)) {
        std::cout << x.path() << std::endl;
    }
}

/* https://www.boost.org/doc/libs/1_70_0/libs/beast/doc/html/beast/examples.html */
int main() {
    std::cout << "Welcome HTTP" << std::endl;

    // dir_walk(config_dir);

    net::io_context ioc;

    tcp::resolver  resolver(ioc);
    beast::tcp_stream stream(ioc);

    auto const results = resolver.resolve("localhost", "3000");
    stream.connect(results);

    http::request<http::string_body> req{http::verb::post, "/ctap/init", 11};
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    http::write(stream, req);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> resp;
    http::read(stream, buffer, resp);

    std::cout << resp << std::endl;

    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec) {
        std::cout << "err : " << ec << std::endl;
    }

    return 0;
}
