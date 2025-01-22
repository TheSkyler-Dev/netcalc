// Netcalc (c) 2025 TheSkyler-Dev Licensed under GNU GPL-v3.0
#include <iostream>
#include <string>
#include <sstream>
#include <CLI11.hpp>
#include <bitset>

//helper function: IP to Binary notation
std::bitset<32> ipToBits(const std::string& ipAddr){
    std::stringstream ss(ipAddr);
    std::string octet;
    uint32_t ipInt = 0;

    for (int i = 3; i >= 0; --i){
        std::getline(ss, octet, '.');
        ipInt |= (std::stoi(octet) << (i * 8));
    };
    return std::bitset<32>(ipInt);
};

//helper function: Binary notation to IP
std::string bitsToIP(const std::bitset<32>& ipBin){
    uint32_t ipInt = ipBin.to_ulong();
    std::ostringstream res;

    for (int i = 3; i >= 0; --i){
        res << ((ipInt >> (i * 8)) & 0xFF);
        if(i > 0) res << ".";
    };
    return res.str();
};

//main logic
int main(int argc, char** argv){
    CLI::App app{"netcalc - Network Calculator"};
    argv = app.ensure_utf8(argv);

    //basis flags
    std::string calcBasis;
    app.add_option("--broadcast", calcBasis, "Use broadcast address as basis")->check(CLI::IsMember({"--broadcast"}));

    app.add_option("--net", calcBasis, "Use network address as basis")->check(CLI::IsMember({"--net"}));

    app.add_option("--cidr", calcBasis, "Use CIDR address as basis")->check(CLI::IsMember({"--cidr"}));

    //IP address
    std::string ipAddr = "default";
    app.add_option("ip", ipAddr, "IP Address")->check(CLI::ValidIPV4)->required();

    //flags behind IP address
    //initialise all
    bool calcAll = false, calcBroadcast = false, calcRange = false, calcNet = false, calcAddressable = false, calcCIDR = false, calcSNM = false;

    app.add_flag("-A, --all", calcAll, "Calculate all network characteristics");

    app.add_flag("-b, --broadcast", calcBroadcast, "Calculate only the broadcast address");

    app.add_flag("-r, --range", calcRange, "Calculate the full network range");

    app.add_flag("-n, --net", calcNet, "Calculate network address");

    app.add_flag("-a, --addressable", calcAddressable, "Calculate adddressable host range only");

    //app.add_flag("-c, --cidr", calcCIDR, "Calculate CIDR address");

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

    if(!ipAddr.empty() && (calcAll || calcBroadcast || calcRange || calcNet || calcAddressable || calcCIDR)){
        std::cout << "Calculating requested network characteristics for: " << ipAddr << "n";
    } else if(ipAddr.empty()){
        std::cerr << "Error: Short flags (-A, -b, -e, etc.) may only appear behind the IP Address.\n";
        return 1;
    };

    std::bitset<32> ipBin = ipToBits(ipAddr);

    if(showHelp){
        std::cout << app.help() << "\n";
    }

    /*if(calcCIDR){

    }*/

    if(calcSNM){

    }

    if(calcNet){

    }

    if(calcRange){

    }

    if(calcAddressable){

    }

    if(calcBroadcast){

    }

    if(identType){

    }

    if(calcAll){

    };
    return 0;
}    