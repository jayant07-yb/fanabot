#include "crow.h"
#include "main.h"
#include "navigation.h"

// Handler for /move endpoint
crow::response handleMove(const crow::request& req) {
    auto body = crow::json::load(req.body);
    if (!body) {
        return crow::response(400, "Invalid JSON");
    }
    crow::json::wvalue response;

    std::string direction = body["DIRECTION"].s();
    int time = body["time"].i();
    pthread_t navigation;
    global_navigation.setTime(time);
    if (pthread_create(&naviagtion, NULL, global_navigation.runNavigation, NULL) != 0) {
        std::cerr << "Failed to create location thread" << std::endl;
        response["status"] = "failure";
        response["message"] = "Unable to move";
    } else {
        response["status"] = "success";
        response["message"] = "Move command received";
        response["direction"] = direction;
        response["time"] = time;
    }

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