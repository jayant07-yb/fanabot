#pragma once
#include <map>

enum CommandType {
    MOVE,
    ROTATE_LEFT,
    ROTATE_RIGHT,
    STOP
};

class WheelCommands {
    CommandType type;
};

typedef std::map<std::pair<int, int>, vector
class RouteMap {
    std::map<std::pair<int, int>, Route> routeMap;
}