
#include <string.h>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <vector>
#include <curl/curl.h>
#include "httpClass.cpp"
#include <boost/algorithm/string.hpp>


std::string JSONParser(std::string Val);

class Subject
{

public:
  CURLplusplus client;
  std::string BTC = "";

  std::string ETH = "";

  std::string DOGE = "";

  void init()
  {
    BTC = client.Get("https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT");
    ETH = client.Get("https://api.binance.com/api/v3/ticker/price?symbol=ETHUSDT");
    DOGE = client.Get("https://api.binance.com/api/v3/ticker/price?symbol=DOGEUSDT");
  }

 
  std::string getBTC() const
  {
   
    return JSONParser(BTC);
 
  }

  std::string getETH() const
  { 
   
    return JSONParser(ETH);
  }
  std::string getDOGE() const
  {

    return JSONParser(DOGE);
  }

  void setBTC()
  {

    std::string newBTC = client.Get("https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT");

    if (BTC != newBTC)
    {

      BTC = newBTC;
      sleep(0.5);
      BTCsignal(newBTC);
    }
  }

  void setETH()
  {

    std::string newETH = client.Get("https://api.binance.com/api/v3/ticker/price?symbol=ETHUSDT");

    if (ETH != newETH)
    {

      ETH = newETH;

      sleep(1);
      ETHsignal(ETH);
    }
  }

  void setDOGE()
  {
    std::string newDOGE = client.Get("https://api.binance.com/api/v3/ticker/price?symbol=DOGEUSDT");

    if (DOGE != newDOGE)
    {

      DOGE = newDOGE;
      sleep(0.5);

      DOGEsignal(newDOGE);
    }
  }

  boost::signals2::signal<void(const std::string &btcVal)> BTCsignal;
  boost::signals2::signal<void(const std::string &ethVal)> ETHsignal;
  boost::signals2::signal<void(const std::string &dogeVal)> DOGEsignal;
};


 std::string JSONParser(std::string Val){
    std::vector<std::string> results;

    boost::algorithm::split(results, Val, boost::is_any_of("\""));
    std::string body = results[3]+ " " + results[7];


    return body;
  }
