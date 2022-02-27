
#include <string.h>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include "signalClass.cpp"

Subject s;

struct BTCObserver
{

  void OnNotice(const std::string &btcVal) const
  {
    sleep(1);

    std::cout << s.getBTC() << std::endl;
  }
};

struct ETHObserver
{

  std::vector<std::tuple<std::string, std::string, std::string>> people;

  void OnNotice(const std::string &ethVal) const
  {
    sleep(1);

    std::cout << s.getETH() << std::endl;
  }
};

struct DOGEObserver
{

  void OnNotice(const std::string &dogeVal) const
  {
    sleep(1);

    std::cout << s.getDOGE() << std::endl;
  }
};

int main(int argc, char *argv[])
{

  s.init();

  BTCObserver btc;
  ETHObserver eth;
  DOGEObserver doge;

  s.BTCsignal.connect(
      boost::bind(
          &BTCObserver::OnNotice,
          &btc,
          _1));

  s.ETHsignal.connect(
      boost::bind(
          &ETHObserver::OnNotice,
          &eth,
          _1));

  s.DOGEsignal.connect(
      boost::bind(
          &DOGEObserver::OnNotice,
          &doge,
          _1));

  while (true)
  {

    s.setBTC();

    s.setETH();

    s.setDOGE();

    sleep(2);
  }

  s.BTCsignal.disconnect(
      boost::bind(
          &BTCObserver::OnNotice,
          &btc,
          _1));

  s.ETHsignal.disconnect(
      boost::bind(
          &ETHObserver::OnNotice,
          &eth,
          _1));

  s.DOGEsignal.disconnect(
      boost::bind(
          &DOGEObserver::OnNotice,
          &doge,
          _1));

  sleep(500);

  return 0;
}