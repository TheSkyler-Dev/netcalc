// Netcalc (c) 2025 TheSkyler-Dev Licensed under GNU GPL-v3.0
//restored to previous state after accidental changes to v0.2.0 codebase
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>
#include <string>
#include <array>
#include <sstream>
#include <bitset>
#include <CLI/CLI.hpp>

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

//Function to calculate number of addressable hosts
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

// Function to identify network type
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
    //initialise all
    bool calcAll = false, calcBroadcast = false, calcRange = false, calcNet = false, calcAddressable = false, calcCIDR = false, calcSNM = false;

    app.add_flag("-A", calcAll, "Calculate all network characteristics");
    app.add_flag("-b", calcBroadcast, "Calculate only the broadcast address");
    app.add_flag("-r", calcRange, "Calculate the full network range");
    app.add_flag("-n", calcNet, "Calculate network address");
    app.add_flag("-a", calcAddressable, "Calculate adddressable host range only");
    app.add_flag("-s", calcSNM, "Calculate subnet mask");

    bool identType = false;
    app.add_flag("-i", identType, "Identify network type");

    CLI11_PARSE(app, argc, argv);

    if(!ipAddr.empty() && !subnet.empty() && (calcAll || calcBroadcast || calcRange || calcNet || calcAddressable || calcCIDR)){
        std::cout << "Calculating requested network characteristics for: " << ipAddr << "\n";
    } else if(ipAddr.empty() && subnet.empty()){
        fmt::print(stderr, fmt::fg(fmt::color::crimson), "Error: Short flags (-A, -b, -e, etc.) may only be used behind the IP Address. \n");
        return 1;
    };

    std::bitset<32> ipBin = ipToBits(ipAddr);
    std::bitset<32> subnetBin = subnetToBits(subnet);

    if(calcSNM){
        fmt::print(fmt::fg(fmt::color::steel_blue) | fmt::emphasis::bold, "IP: {}{}\n", ipAddr, subnet);
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Subnet Mask: {}\n", bitsToIP(subnetBin));
    }

    if(calcNet){
        fmt::print(fmt::fg(fmt::color::steel_blue) | fmt::emphasis::bold, "IP: {}{}\n", ipAddr, subnet);
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Network Address: {}\n", bitsToIP(ipBin & subnetBin));
    }

    if(calcRange){
        fmt::print(fmt::fg(fmt::color::steel_blue) | fmt::emphasis::bold, "IP: {}{}\n", ipAddr, subnet);
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Network Range: {} - {}\n", bitsToIP(ipBin & subnetBin), bitsToIP(ipBin | ~subnetBin));
    }

    if(calcAddressable){
        fmt::print(fmt::fg(fmt::color::steel_blue) | fmt::emphasis::bold, "IP: {}{}\n", ipAddr, subnet);

        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Addressable Host Range: {} - {}\n", bitsToIP((ipBin & subnetBin).to_ulong() + 1), bitsToIP((ipBin | ~subnetBin).to_ulong() - 1);
    }

    if(calcBroadcast){
        fmt::print(fmt::fg(fmt::color::steel_blue) | fmt::emphasis::bold, "IP: {}{}\n", ipAddr, subnet);
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Broadcast Address: {}\n", bitsToIP(ipBin | ~subnetBin));
    }

    if(identType){
        std::string networkType = ipIdent(ipAddr);
        fmt::print(fmt::fg(fmt::color::steel_blue) | fmt::emphasis::bold, "IP: {}{}\n", ipAddr, subnet);
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Address type: {}\n", networkType);
    }

    if(calcAll){
        fmt::print(fmt::fg(fmt::color::steel_blue) | fmt::emphasis::bold, "IP: {}{}\n", ipAddr, subnet);
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Address type: {}\n", ipIdent(ipAddr));
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Subnet Mask: {}\n", bitsToIP(subnetBin));
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Network Address: {}\n", bitsToIP(ipBin & subnetBin));
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Network Range: {} - {}\n", bitsToIP(ipBin & subnetBin), bitsToIP(ipBin | ~subnetBin));
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Addressable Host Range: {} - {}\n", bitsToIP((ipBin & subnetBin).to_ulong() + 1), bitsToIP((ipBin | ~subnetBin).to_ulong() - 1);
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Number of Addressable Hosts: {}\n", calcAddressableHosts(subnetBin));
        fmt::print(fmt::fg(fmt::color::light_steel_blue), "Broadcast Address: {}\n", bitsToIP(ipBin | ~subnetBin));
    };
    return 0;
} //162 lines of C++
