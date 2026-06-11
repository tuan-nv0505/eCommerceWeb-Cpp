//
// Created by Nguyễn Tuấn on 07/06/2026.
//

#include <drogon/drogon.h>
#include "app_configs/ApplicationContext.h"

#include <fstream>


#define PORT 5555
#define CONFIG_FILE "../config.json"
#define BANNER_FILE "../banner.txt"

void run()
{
   std::ifstream file(BANNER_FILE);
   if (file.is_open())
   {
       std::string line;
       while (std::getline(file, line))
       {
           std::cout << line << "\n";
       }
       std::cout << "\n";
   }

   ApplicationContext::getInstance().init();

   drogon::app().addListener("0.0.0.0", PORT);
   drogon::app().loadConfigFile(CONFIG_FILE);
   //drogon::app().loadConfigFile("../config.yaml");
   LOG_INFO << "C++ server is running on http://localhost:" << PORT;
   drogon::app().run();
}

int main()
{
   run();
   
   return 0;
}