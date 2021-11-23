#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <SFML/Network.hpp>
static bool portOpen(const std::string &ipAdd, int port)
{
    if (sf::TcpSocket().connect(ipAdd, port) == sf::Socket::Done)
        return true;
    else
        return false;
}

static std::vector<std::string> split(std::string &input, char delim = ' ')
{
    std::vector<std::string> tokens;
    std::stringstream inp(input);
    std::string parts;
    while (std::getline(inp, parts, delim))
    {
        if (parts.size() > 0)
            tokens.push_back(parts);
    }
    return tokens;
}

static std::vector<int> range(int min, int max)
{
    if (min > max)
    {
        int t = max;
        max = min;
        min = t;
    }
    if (min == max)
        return std::vector<int>(1, min);
    std::vector<int> ports;
    for (int i = min; i <= max; i++)
    {
        ports.push_back(i);
    }
    return ports;
}

static std::vector<int> listOfports(std::string &p)
{
    std::vector<int> ports;
    for (std::string &token : split(p, ','))
    {
        std::vector<std::string> temp = split(token, '-');
        if (temp.size() == 0)
            ports.push_back(stoi(token));
        else if (temp.size() == 1)
            ports.push_back(stoi(temp[0]));
        else if (temp.size() == 2)
        {
            for (int i : range(stoi(temp[0]), stoi(temp[1])))
                ports.push_back(i);
        }
    }
    return ports;
}

int main()
{
    std::string addr;
    std::vector<int> ports;
    std::cout << "IP Address: " << std::flush;
    std::getline(std::cin, addr);
    std::string range;
    std::cout << "Ports range: " << std::flush;
    std::getline(std::cin, range);
    ports = listOfports(range);
    for (auto i = ports.begin(); i != ports.end(); i++)
    {

        if (portOpen(addr, *i))
        {
            std::cout << *i << ": Port open" << std::endl;
        }
        else
        {
            std::cout << *i << ": Cannot connect to port " << std::endl;
        }
    }
    system("pause");
    return 0;
}