#ifndef GPS_UBLOXPVT_h
#define GPS_UBLOXPVT_h

#include <inttypes.h>

#define UBX_MAXPAYLOAD 100

class GPS_UBLOXPVT_Class
{
  private:
    // Internal variables
	uint8_t ck_a;     // Packet checksum
	uint8_t ck_b;
	uint8_t UBX_step;
	uint8_t UBX_class;
	uint8_t UBX_id;
	uint8_t UBX_payload_length_hi;
	uint8_t UBX_payload_length_lo;
	uint8_t UBX_payload_counter;
	uint8_t UBX_buffer[UBX_MAXPAYLOAD];
	uint8_t UBX_ck_a;
	uint8_t UBX_ck_b;
	long GPS_timer;
	long UBX_ecefVZ;
	void parse_ubx_gps();
	void ubx_checksum(unsigned char ubx_data);
	long join_4_bytes(unsigned char Buffer[]);
	short join_2_bytes(unsigned char Buffer[]);


  public:
    // Methods
	GPS_UBLOXPVT_Class();
	void Init();
	void Read();
    // Properties
	long Time;          //GPS Millisecond Time of Week
	short Year;
	int8_t Month;
	int8_t Day;
	int8_t Hour;
	int8_t Min;
	int8_t Sec;
	int8_t numSV;
	long Lattitude;     // Geographic coordinates
	long Longitude;
	long Altitude;
	long Ground_Speed;
	long Speed_3d;      //Speed (3-D)
	long Ground_Course;
	uint8_t NumSats;      // Number of visible satelites
	uint8_t Fix;        // 1:GPS FIX   0:No FIX (normal logic)
	uint8_t NewData;    // 1:New GPS Data
	uint8_t PrintErrors; // 1: To Print GPS Errors (for debug)
	
};

extern GPS_UBLOXPVT_Class GPS;

#endif