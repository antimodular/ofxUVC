#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <regex>

#ifdef TARGET_OSX //sorry linux and windows folks this is macOS only

#define __OFX_UVC_PROBER__

namespace ofxUVCProber{
    namespace detail{
        inline std::string exec(const char* cmd) {
            std::array<char, 128> buffer;
            std::string result;
            std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
            if (!pipe) throw std::runtime_error("popen() failed!");
            while (!feof(pipe.get())) {
                if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
                    result += buffer.data();
            }
            return result;
        }
    }
    inline std::vector<std::tuple<std::string,int,int,std::string>> getList(){

        std::string ret = detail::exec((char*)"system_profiler SPCameraDataType");
        std::cout<<ret<<std::endl;

        std::regex reCam (" {4}(.*?):\n\n {6}(.*?)VendorID_(.*?) ProductID_(.*?)\n {6}Unique ID: (.*?)\n");
        std::smatch mCam;

        std::vector<std::tuple<std::string,int,int,std::string>> result;

        while (std::regex_search (ret, mCam, reCam)){

            std::string camInfo = mCam[0];

            string name = mCam[1];
            int vendID = std::stoi (mCam[3],nullptr,0);
            int prodID = std::stoi (mCam[4],nullptr,0);
            string uniqID = mCam[5];

            std::cout   <<  "Name = "<<name
                        <<", VendorID = "<<vendID
                        <<", ProductID = "<<prodID
                        <<", UniqueID = "<<uniqID<<std::endl;

            auto tup = std::make_tuple(name,vendID,prodID,uniqID);
            result.push_back(tup);

            ret = mCam.suffix().str();
        }
        return result;
    }
    inline std::tuple<int,int> getVendorIDAndProductIDByDeviceIndex(int i){
        auto cams = getList();
        if (cams.size() <= i){
            std::cout<<"[ERROR] Requested device is not available!"<<std::endl;
            return make_tuple(-1,-1);
        }
        return make_tuple(std::get<1>(cams[i]),std::get<2>(cams[i]));
    }
    inline std::tuple<int,int> getFirstVendorIDAndProductID(){
        return getVendorIDAndProductIDByDeviceIndex(0);
    }
    inline std::vector<std::string> getDeviceNameList(){
        auto cams = getList();
        vector<std::string> result;
        for (int i = 0; i < cams.size(); i++){
            result.push_back(std::get<0>(cams[i]));
        }
        return result;
    }
    inline std::tuple<int,int> getVendorIDAndProductIDByDeviceName(std::string s){
        auto cams = getList();
        for (int i = 0; i < cams.size(); i++){
            if (std::get<0>(cams[i]) == s){
                return make_tuple(std::get<1>(cams[i]),std::get<2>(cams[i]));
            }
        }
    }
}

#endif
