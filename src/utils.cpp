#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace beast = boost::beast;
namespace http = beast::http;

std::string read_file(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filepath);
    }
    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

http::response<http::string_body> handle_request(const http::request<http::string_body>& req) {
    http::response<http::string_body> res;

    res.version(req.version());
    res.keep_alive(false);

    res.set(http::field::server, "http-beastie");
    res.set(http::field::content_type, "text/html");

    if (req.method() == http::verb::get) {
        if (req.target() == "/") {
            try {
                std::string html = read_file("static/index.html");
                res.result(http::status::ok);
                res.body() = html;
            } catch (const std::exception&) {
                res.result(http::status::not_found);
                res.body() = "<h1>404 Not Found</h1>";
            }
        } else if (req.target() == "/mohamed") {
            try {
                std::string bio = read_file("static/mohamed.html");
                res.result(http::status::ok);
                res.body() = bio;
            } catch (const std::exception&) {
                res.result(http::status::not_found);
                res.body() = "<h1>404 Not Found</h1>";
            }
        } else {
            // Any other GET path
            res.result(http::status::not_found);
            res.body() = "<h1 style=\"text-align: center;\">404 Not Found</h1>";
        }
    } else {
        res.result(http::status::method_not_allowed);
        res.set(http::field::allow, "GET");
        res.body() = "<h1 style=\"text-align: center;\">405 Method Not Allowed</h1>";
    }

    res.prepare_payload();
    return res;
}
