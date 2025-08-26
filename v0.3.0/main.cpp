// Netcalc (c) 2025 TheSkyler-Dev Licensed under GNU GPL-v3.0
//#include <iostream>
//#include <print>
#include <iostream>
#include <cstdint>  // For uint32_t
#include <string>
#include <array>
#include <sstream>
#include <bitset>
#include <CLI/CLI.hpp>

// ANSI escape codes for formatting
const std::string RESET      = "\033[0m";
// const std::string FG_BLACK   = "\033[30m";
const std::string FG_RED     = "\033[31m";
const std::string FG_GREEN   = "\033[32m";
// const std::string FG_YELLOW  = "\033[33m";
const std::string FG_BLUE    = "\033[34m";
// const std::string FG_MAGENTA = "\033[35m";
const std::string FG_CYAN    = "\033[36m";
const std::string FG_WHITE   = "\033[37m";
const std::string BOLD       = "\033[1m";

//helper function: IP to Binary notation
// Converts an IPv4 address from string format to a 32-bit binary representation
std::bitset<32> ipToBits(const std::string& ipAddr){
    std::stringstream ss(ipAddr);
    std::string octet;
    uint32_t ipInt = 0;

    for (int i = 3; i >= 0; --i){
        std::getline(ss, octet, '.');
        ipInt |= (std::stoi(octet) << (i * 8));
    }
    return std::bitset<32>(ipInt);
}

//convert CIDR subnet to binary
std::bitset<32> subnetToBits(const std::string& subnet){
    int prefixLength = std::stoi(subnet.substr(1));
    uint32_t subnetInt = (0xFFFFFFFF << (32 - prefixLength)) & 0xFFFFFFFF;
    return std::bitset<32>(subnetInt);
}

//helper function: Binary notation to IP
// Converts a 32-bit binary representation to an IPv4 address in string format
std::string bitsToIP(const std::bitset<32>& ipBin){
    uint32_t ipInt = ipBin.to_ulong();
    std::ostringstream res;

    for (int i = 3; i >= 0; --i){
        res << ((ipInt >> (i * 8)) & 0xFF);
        if(i > 0) res << ".";
    }
    return res.str();
}

//Function to calculate the number of addressable hosts
int calcAddressableHosts(const std::bitset<32>& subnetBin){
    int prefixLength = subnetBin.count();
    return (1 << (32 - prefixLength)) - 2;
}
// Define IP ranges
const std::array<std::pair<uint32_t, uint32_t>, 3> PRIVATE_RANGES = {{
    {ipToBits("10.0.0.0").to_ulong(), ipToBits("10.255.255.255").to_ulong()},
    {ipToBits("172.16.0.0").to_ulong(), ipToBits("172.31.255.255").to_ulong()},
    {ipToBits("192.168.0.0").to_ulong(), ipToBits("192.168.255.255").to_ulong()}
}};

const std::pair<uint32_t, uint32_t> APIPA_RANGE = {
    ipToBits("169.254.0.0").to_ulong(), ipToBits("169.254.255.255").to_ulong()
};

// Function to check if IP is within a range
bool isInRange(uint32_t ip, const std::pair<uint32_t, uint32_t>& range) {
    return ip >= range.first && ip <= range.second;
}

// Function to identify the network type
std::string ipIdent(const std::string& ipAddr) {
    uint32_t ipInt = ipToBits(ipAddr).to_ulong();

    for (const auto& range : PRIVATE_RANGES) {
        if (isInRange(ipInt, range)) {
            return "Private";
        }
    }

    if (isInRange(ipInt, APIPA_RANGE)) {
        return "APIPA";
    }

    return "Public";
}

//main logic
int main(int argc, char** argv){
    CLI::App app{"netcalc - Network Calculator"};
    argv = app.ensure_utf8(argv);

    //IP address
    std::string ipAddr = "default";
    app.add_option("ip", ipAddr, "IP Address")->check(CLI::ValidIPV4)->required();
    std::string subnet = "/def";
    app.add_option("--sn", subnet, "CIDR subnet identifier")->required();

    //flags behind IP address
    //initialize all
    bool calcAll = false, calcBroadcast = false, calcRange = false, calcNet = false, calcAddressable = false, calcSNM = false;

    app.add_flag("-A", calcAll, "Calculate all network characteristics");
    app.add_flag("-b", calcBroadcast, "Calculate only the broadcast address");
    app.add_flag("-r", calcRange, "Calculate the full network range");
    app.add_flag("-n", calcNet, "Calculate network address");
    app.add_flag("-a", calcAddressable, "Calculate addressable host range only");
    app.add_flag("-s", calcSNM, "Calculate subnet mask");

    bool identType = false;
    app.add_flag("-i", identType, "Identify network type");

    CLI11_PARSE(app, argc, argv);

    if(!ipAddr.empty() && !subnet.empty() && (calcAll || calcBroadcast || calcRange || calcNet || calcAddressable)){
        std::cout << std::format("{}Calculating requested network characteristics for: {}{}\n", FG_GREEN, ipAddr, RESET);
    } else if(ipAddr.empty() && subnet.empty()){
        std::cout << std::format("{}{}Error: Short flags are disallowed before the IP address.{}\n", FG_RED, BOLD, RESET);
    }

    std::bitset<32> ipBin = ipToBits(ipAddr);
    std::bitset<32> subnetBin = subnetToBits(subnet);

    if(calcSNM){
        std::cout << std::format("{}{}IP: {}{}{}\n", FG_CYAN, BOLD, ipAddr, subnet, RESET);
        std::cout << std::format("{}Subnet Mask: {}{}\n", FG_WHITE, bitsToIP(subnetBin), RESET);
    }

    if(calcNet){
        std::cout << std::format("{}{}IP: {}{}{}\n", FG_CYAN, BOLD, ipAddr, subnet, RESET);
        std::cout << std::format("{}Network Address: {}{}\n", FG_WHITE,  bitsToIP(ipBin & subnetBin), RESET);
    }

    if(calcRange){
        std::cout << std::format("{}{}IP: {}{}{}\n", FG_CYAN, BOLD, ipAddr, subnet, RESET);
        std::cout << std::format("{}Network Range: {} - {}{}", FG_WHITE, bitsToIP(ipBin & subnetBin), bitsToIP(ipBin | ~subnetBin), RESET);
    }

    if(calcAddressable){
        std::cout << std::format("{}{}IP: {}{}{}\n", FG_CYAN, BOLD, ipAddr, subnet, RESET);
        std::cout << std::format("{}Addressable Host Range: {} - {}{}", FG_WHITE, bitsToIP((ipBin & subnetBin).to_ulong() + 1), bitsToIP(ipBin | ~subnetBin - 1), RESET);
    }

    if(calcBroadcast){
        std::cout << std::format("{}{}IP: {}{}{}\n", FG_CYAN, BOLD, ipAddr, subnet, RESET);
        std::cout << std::format("{}Broadcast Address: {}{}\n", FG_WHITE, bitsToIP(ipBin | ~subnetBin), RESET);
    }

    if(identType){
        std::string networkType = ipIdent(ipAddr);
        std::cout << std::format("{}{}IP: {}{}{}\n", FG_CYAN, BOLD, ipAddr, subnet, RESET);
        std::cout << std::format("{}Subnet Mask: {}{}\n", FG_WHITE, bitsToIP(subnetBin), RESET);
    }

    if(calcAll){
        std::cout << std::format("{}{}IP: {}{}{}\n", FG_CYAN, BOLD, ipAddr, subnet, RESET);
        std::string networkType = ipIdent(ipAddr);
        std::cout << std::format("{}Address type: {}{}\n", FG_WHITE, networkType, RESET);
        std::cout << std::format("{}Subnet Mask: {}{}\n", FG_WHITE, bitsToIP(subnetBin), RESET);
        std::cout << std::format("{}Network Address: {}{}\n", FG_WHITE, bitsToIP(ipBin & subnetBin), RESET);
        std::cout << std::format("{}Network Range: {} - {}{}\n", FG_WHITE, bitsToIP(ipBin & subnetBin), bitsToIP(ipBin | ~subnetBin), RESET);
        std::cout << std::format("{}Addressable Host Range: {} - {}{}\n", FG_WHITE, bitsToIP((ipBin & subnetBin).to_ulong() + 1), bitsToIP(ipBin | ~subnetBin - 1), RESET);
        std::cout << std::format("{}Number of Addressable Hosts: {}{}\n", FG_BLUE, calcAddressableHosts(subnetBin - 1), RESET);
        std::cout << std::format("{}Broadcast Address: {}{}\n", FG_WHITE, bitsToIP(ipBin | ~subnetBin), RESET);
    }
    return 0;
} //174 lines of C++