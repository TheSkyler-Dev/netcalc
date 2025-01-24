// Netcalc (c) 2025 TheSkyler-Dev Licensed under GNU GPL-v3.0
#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <bitset>
#include <CLI11.hpp>

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
    return res.str();
    }
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

    //basis flags
    std::string calcBasis;
    app.add_option("--broadcast", calcBasis, "Use broadcast address as basis")->check(CLI::IsMember({"--broadcast"}));

    app.add_option("--net", calcBasis, "Use network address as basis")->check(CLI::IsMember({"--net"}));

    //IP address
    std::string ipAddr = "default";
    app.add_option("ip", ipAddr, "IP Address")->check(CLI::ValidIPV4)->required();
    std::string subnet = "/def";
    app.add_option("sn", subnet, "CIDR subnet identifier")->required();

    //flags behind IP address
    //initialise all
    bool calcAll = false, calcBroadcast = false, calcRange = false, calcNet = false, calcAddressable = false, calcCIDR = false, calcSNM = false;

    app.add_flag("-A, --all", calcAll, "Calculate all network characteristics");

    app.add_flag("-b, --broadcast", calcBroadcast, "Calculate only the broadcast address");

    app.add_flag("-r, --range", calcRange, "Calculate the full network range");

    app.add_flag("-n, --net", calcNet, "Calculate network address");

    app.add_flag("-a, --addressable", calcAddressable, "Calculate adddressable host range only");

    app.add_flag("-s, --snm", calcSNM, "Calculate subnet mask");

    bool identType = false;
    app.add_flag("-i, --ident", identType, "Identify network type");

    bool showHelp = false;
    app.add_flag("-h, --help", showHelp, "Display help/list valid flags and usage");

    CLI11_PARSE(app, argc, argv);

    if(!calcBasis.empty() && !ipAddr.empty()){
        std::cout << "Using basis: " << calcBasis << " for IP: " << ipAddr << "\n";
    } else if(!calcBasis.empty()){
        std::cerr << "Error: Disallowed option, only --broadcast, --net and --cidr are allowed before the IP address.\n";
        return 1;
    };

    if(!ipAddr.empty() && !subnet.empty() && (calcAll || calcBroadcast || calcRange || calcNet || calcAddressable || calcCIDR)){
        std::cout << "Calculating requested network characteristics for: " << ipAddr << "n";
    } else if(ipAddr.empty() && subnet.empty()){
        std::cerr << "Error: Short flags (-A, -b, -e, etc.) may only appear behind the IP Address.\n";
        return 1;
    };

    std::bitset<32> ipBin = ipToBits(ipAddr);
    std::bitset<32> subnetBin = subnetToBits(subnet);

    if(showHelp){
        std::cout << app.help() << "\n";
        }

        if(calcSNM){
            std::cout << "IP: " << ipAddr << subnet << "\n";
            std::cout << "Subnet Mask: " << bitsToIP(subnetBin) << "\n";
        }

        if(calcNet){
            std::cout << "IP: " << ipAddr << subnet << "\n";
            std::cout << "Network Address: " << bitsToIP(ipBin & subnetBin) << "\n";
        }

        if(calcRange){
            std::cout << "IP: " << ipAddr << subnet << "\n";
            std::cout << "Netwok Range: " << bitsToIP(ipBin & subnetBin) << " - " << bitsToIP(ipBin / ~subnetBin) << "\n";
        }

        if(calcAddressable){
            std::cout << "IP: " << ipAddr << subnet << "\n";
            std::cout << "Addressable Host Range: " << bitsToIP((ipBin & subnetBin) + 1) << " - " << bitsToIP(ipBin | ~subnetBin) << "\n";
        }

        if(calcBroadcast){
            std::cout << "IP: " << ipAddr << subnet << "\n";
            std::cout << "Broadcast Address: " << bitsToIP(ipBin | ~subnetBin) << "\n";
        }

        if(identType){
        std::string networkType = ipIdent(ipAddr);
        std::cout << "IP: " << ipAddr << subnet << '\n';
        std::cout << "Address type: " << networkType << "\n";
    }

    if(calcAll){
        std::cout << "IP: " << ipAddr << subnet << "\n";
        std::cout << "Address type:" << ipIdent(ipAddr) << "\n";
        std::cout << "Subnet Mask: " << bitsToIP(subnetBin) << "\n";
        std::cout << "Network Address: " << bitsToIP(ipBin & subnetBin) << "\n";
        std::cout << "Network Range: " << bitsToIP(ipBin & subnetBin) << " - " << bitsToIP(ipBin | ~subnetBin) << "\n";
        std::cout << "Addressable Host Range: " << bitsToIP(ipBin & subnetBin) + 1 << " - " << bitsToIP(ipBin | ~subnetBin) << "\n";
        std::cout << "Broadcast Address: " << bitsToIP(ipBin | ~subnetBin) << "\n";
    };
    return 0;
} //179 lines of C++