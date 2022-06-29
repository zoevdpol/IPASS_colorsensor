#include "hwlib.hpp"
#include "colorsensor.hpp"
#include "leds.hpp"



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
       
       hwlib::wait_ms(250);
  }
}
