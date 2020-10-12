/**
 * @brief Arduino library for interfacing with the PA1010D GPS module (MTK3333 chipset).
 * @license LGPL 3.0
 */

#ifndef ARDUINO_MTK3333_NMEA_GPRMC_PARSER_H_
#define ARDUINO_MTK3333_NMEA_GPRMC_PARSER_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace nmea
{

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class GPRMC
{

public:

  static bool isGPRMC(char const * nmea);

  static bool parse(char const * gprmc,
                    float & last_fix_utc_s,
                    float & latitude,
                    float & longitude,
                    float & speed,
                    float & course,
                    float & magnetic_variation);

private:

  GPRMC() { }
  GPRMC(GPRMC const &) { }

  enum class ParserState : int
  {
    MessadeId,
    UTCPositionFix,
    Status,
    LatitudeVal,
    LatitudeNS,
    LongitudeVal,
    LongitudeEW,
    SpeedOverGround,
    TrackAngle,
    Date,
    MagneticVariation,
    MagneticVariationEastWest,
    Checksum,
    Done,
    Error
  };

  static ParserState handle_MessadeId                (char const * token);
  static ParserState handle_UTCPositionFix           (char const * token, float & last_fix_utc_s);
  static ParserState handle_Status                   (char const * token);
  static ParserState handle_LatitudeVal              (char const * token, float & latitude);
  static ParserState handle_LatitudeNS               (char const * token, float & latitude);
  static ParserState handle_LongitudeVal             (char const * token, float & longitude);
  static ParserState handle_LongitudeEW              (char const * token, float & longitude);
  static ParserState handle_SpeedOverGround          (char const * token, float & speed);
  static ParserState handle_TrackAngle               (char const * token, float & course);
  static ParserState handle_Date                     (char const * token);
  static ParserState handle_MagneticVariation        (char const * token, float & magnetic_variation);
  static ParserState handle_MagneticVariationEastWest(char const * token, float & magnetic_variation);
  static ParserState handle_Checksum                 (char const * token);

};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* nmea */

#endif /* ARDUINO_MTK3333_NMEA_GPRMC_PARSER_H_ */