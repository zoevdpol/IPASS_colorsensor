#ifndef COLORSENSOR_HPP
#define COLORSENSOR_HPP
/****************************************************************************************************************************
* author ::       Zoë van de Pol
* File ::         colorsensor.hpp
* Date::          29 - 06 - 2022
* copyright:      Zoë van de Pol
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/
/// @file

/// \brief
/// colorsensor class
/// \details
/// colorsensor library for easy interfacing with TCS34725
class colorsensor{
private:
    const uint8_t slaveaddress = 0x29;
    //ADRESSEN REGISTERS KLEUREN
    const uint8_t clearlreg = 0x14;
    const uint8_t clearhreg = 0x15;
    const uint8_t redlreg = 0x16;
    const uint8_t redhreg = 0x17;
    const uint8_t greenlreg = 0x18;
    const uint8_t greenhreg = 0x19;
    const uint8_t bluelreg = 0x1A;
    const uint8_t bluehreg = 0x1B;

    //ADRESSEN
    const uint8_t commandreg =  0x80;     // command + type, command = 1, type = 00
    const uint8_t enablereg = 0x00; 
    const uint8_t ATIMEreg = 0x01;
    const uint8_t controlreg = 0x0F;
    const uint8_t IDreg = 0x12;
    const uint8_t wtimereg = 0x03;
    hwlib::i2c_bus & i2c;



public:
    /// \brief
    /// Constructor for colorsensor object
    colorsensor(hwlib::i2c_bus &i2c);

    /// \brief
   /// write function for colorsensor
   /// \details
   /// function to write to colorsensor using i2c
    void writesensor(uint8_t location, uint8_t databyte);

    /// \brief
   /// read function for colorsensor
   /// \details
   /// function to read from colorcensor using i2c and write function
    uint8_t read(uint8_t location);

    /// \brief
   /// Combines high and low colordata
   /// \details
   /// combines high and low colordata recieved from colordata
    uint16_t combine(uint8_t high, uint8_t low);

    /// \brief
   /// function to recognise colors
   /// \details
   /// function that recognises colors using the read and combine functions
    void recognisecolors();

    /// \brief
   /// function that reads and returns RGB values
   /// \details
   /// this function reads RGB values and placed them in the given array
    void readRGB(uint8_t *results);
      
    
};
#endif //COLORSENSOR_HPP