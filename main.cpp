#include "hwlib.hpp"
#include "colorsensor.hpp"
#include "leds.hpp"

/****************************************************************************************************************************
* author ::       Zoë van de Pol
* File ::         main.hpp
* Date::          29 - 06 - 2022
* copyright:      Zoë van de Pol
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/
int testcase(colorsensor & c){
    uint8_t results[3];
    for(;;) {
        c.readRGB(results);
        hwlib::cout << "reddata test:" << " " << results[0] << hwlib::endl;
        hwlib::cout << "groendata test:" << " " << results[1] << hwlib::endl;
        hwlib::cout << "bluedata test:" << " " << results[2] << hwlib::endl;
        hwlib::cout << "\n" << hwlib::endl;
        hwlib::wait_ms(800);
    }
}
int main(){
    
  auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
  auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
  hwlib::i2c_bus_bit_banged_scl_sda bus(scl, sda);
  colorsensor colorsensor1(bus);
  ledStrip ipassstrip(8, hwlib::target::pins::d6);
  ipassstrip.initialise();
  uint8_t results[3];
  
  for (;;){
       colorsensor1.recognisecolors();
       colorsensor1.readRGB(results);
       ipassstrip.changeLedRGB(1, results[0], results[1], results[2]);
       ipassstrip.changeLedRGB(2, results[0], results[1], results[2]);
       ipassstrip.changeLedRGB(3, results[0], results[1], results[2]);
       ipassstrip.changeLedRGB(4, results[0], results[1], results[2]);
       ipassstrip.changeLedRGB(5, results[0], results[1], results[2]);
       ipassstrip.changeLedRGB(6, results[0], results[1], results[2]);
       ipassstrip.changeLedRGB(7, results[0], results[1], results[2]);
       ipassstrip.changeLedRGB(8, results[0], results[1], results[2]);
       ipassstrip.write();
//       testcase(colorsensor1);
       
       hwlib::wait_ms(250);
  }
}
