#include "crow.h"
#include "main.h"

// Handler for /move endpoint
crow::response handleMove(const crow::request& req) {
    auto body = crow::json::load(req.body);
    if (!body) {
        return crow::response(400, "Invalid JSON");
    }

    std::string direction = body["DIRECTION"].s();
    int time = body["time"].i();

    // Perform action based on direction and time
    // ...

    crow::json::wvalue response;
    response["status"] = "success";
    response["message"] = "Move command received";
    response["direction"] = direction;
    response["time"] = time;
    return crow::response{response};
}

// Handler for /break endpoint
crow::response handleBreak(const crow::request& req) {
    // Perform break action
    // ...

    crow::json::wvalue response;
    response["status"] = "success";
    response["message"] = "Break command received";
    return crow::response{response};
}

int runApp() {
    crow::SimpleApp app;

    // Route for /move
    CROW_ROUTE(app, "/move").methods(crow::HTTPMethod::POST)(handleMove);

    // Route for /break
    CROW_ROUTE(app, "/break").methods(crow::HTTPMethod::POST)(handleBreak);

    app.port(8080).multithreaded().run();
}