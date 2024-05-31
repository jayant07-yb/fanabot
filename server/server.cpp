#include "crow.h"
#include "navigation.h"
#include "main.h"
#include "shmem.h"
#include <iostream>

using namespace std;

FanaBotInfo *botInfo;

void set_navigation(FanaBotTask task)
{
    botInfo->task = task;
}

// Handler for /move endpoint
crow::response handleMove(const crow::request& req) {
    auto body = crow::json::load(req.body);
    if (!body) {
        return crow::response(400, "Invalid JSON");
    }
    crow::json::wvalue response;

    std::string direction = body["DIRECTION"].s();
    int time = body["time"].i();
    FanaBotTask task;
    task.task = TaskType::MOVE;
    task.magnitude = time;
    set_navigation(task);

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
    botInfo = initialize_shared_memory();
    crow::SimpleApp app;

    // Route for /move
    CROW_ROUTE(app, "/move").methods(crow::HTTPMethod::POST)(handleMove);

    // Route for /break
    CROW_ROUTE(app, "/stop").methods(crow::HTTPMethod::POST)(handleBreak);

    app.port(8080).multithreaded().run();
}