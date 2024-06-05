#pragma once
#include <map>

enum CommandType {
    MOVE,
    ROTATE,
    STOP
};

class WheelCommands {
    CommandType type;

};

typedef std::map<std::pair<int, int>, vector
class RouteMap {
    std::map<std::pair<int, int>, Route> routeMap;
}