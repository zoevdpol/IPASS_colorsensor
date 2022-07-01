#include "hwlib.hpp"
#include "colorsensor.hpp"

/****************************************************************************************************************************
* author ::       Zoë van de Pol
* File ::         colorsensor.cpp
* Date::          29 - 06 - 2022
* copyright:      Zoë van de Pol
*
*  Distributed under the Boost Software License, Version 1.0.
* (See accompanying file LICENSE_1_0.txt or copy at
* http://www.boost.org/LICENSE_1_0.txt)
*******************************************************************************************************************************/

colorsensor::colorsensor(hwlib::i2c_bus & i2c) :
i2c(i2c) {}

void colorsensor::writesensor(uint8_t registeraddress, uint8_t databyte){
	{hwlib::i2c_write_transaction wtrans = i2c.write(slaveaddress);
	wtrans.write(registeraddress + commandreg);
	wtrans.write(databyte);}
}

uint8_t colorsensor::read(uint8_t registeraddress){
	uint8_t results[1];
    {hwlib::i2c_write_transaction wtrans = i2c.write(slaveaddress);
    wtrans.write(registeraddress + commandreg);}
	{hwlib::i2c_read_transaction rtrans = i2c.read(slaveaddress);
	rtrans.read(results, 1);}
	return results[0];
}

//functie om de 2 bytes te combineren naar een getal van 16 bits, combineert high en low
uint16_t colorsensor::combine(uint8_t high, uint8_t low){
    uint16_t conjunction = high;
    conjunction <<= 8;
    conjunction += low;
    return conjunction;
}   
//vergelijkt waardes van kleuren en herkent een kleur
void colorsensor::recognisecolors(){
    //write(controlreg, 0x11);
    writesensor(enablereg, 0x03);
    //rood
    uint8_t redlow = read(redlreg);
    uint8_t redhigh = read(redhreg);
    uint8_t reddata =  combine(redlow, redhigh);
    
    //groen
    uint8_t greenlow = read(greenlreg);
    uint8_t greenhigh = read(greenhreg);  
    uint8_t greendata = combine(greenlow, greenhigh);
    
    //blauw
    uint8_t bluelow = read(bluelreg); 
    uint8_t bluehigh= read(bluehreg); 
    uint8_t bluedata = combine(bluelow, bluehigh);
    
    //data printen
    /*hwlib::cout << "blauw:" << "   "<< bluedata << hwlib::endl;
    hwlib::cout << "rood:" << "    " << reddata << hwlib::endl;
    hwlib::cout << "green:" << "   "<< greendata << hwlib::endl;
    hwlib::cout<<hwlib::endl;*/
    
    //resultaat kleur printen
    /*if(reddata > bluedata && reddata > greendata){
        hwlib::cout << "kleur is rood" << hwlib::endl;
    }
    if(bluedata > reddata && bluedata > greendata){
        hwlib::cout << "kleur is blauw" << hwlib::endl;
    }
    if(greendata > reddata && greendata > bluedata){
        hwlib::cout << "kleur is groen"  << hwlib::endl;
    }*/
}



void colorsensor::readRGB(uint8_t *results){
   
    writesensor(controlreg, 0x11);
    writesensor(enablereg, 0x03);
    //rood
    uint8_t redlow = read(redlreg);
    uint8_t redhigh = read(redhreg);
    results[0] =  combine(redlow, redhigh);
    
    //groen
    uint8_t greenlow = read(greenlreg);
    uint8_t greenhigh = read(greenhreg);  
    results[1] = combine(greenlow, greenhigh);
    
    //blauw
    uint8_t bluelow = read(bluelreg); 
    uint8_t bluehigh= read(bluehreg); 
    results[2]= combine(bluelow, bluehigh);
    
}

