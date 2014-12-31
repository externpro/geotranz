#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "engine.h"
#include "strtoval.h"
#include "strndup.h"

#define Lat_String 1
#define Long_String 2

int leading_zeros = 0;
char Lat_Long_Sep = ' ';
Range Long_Range = _180_180;
long Lat_Long_Prec = Tenth_of_Second;

void Show_Leading_Zeros(int lz)
{
  leading_zeros = lz;
}

void Set_Separator(char sep)
{
  Lat_Long_Sep = sep;
}

void Set_Long_Range(Range range)
{
  Long_Range = range;
}

char Get_Separator()
{
  return (Lat_Long_Sep);
}

Range Get_Long_Range()
{
  return (Long_Range);
}

void Set_Lat_Long_Precision(long precis)
{
  Lat_Long_Prec = precis;
}


SVC_Status String_to_Projection(const char *str, Coordinate_Type *val)
{
  SVC_Status error_Code = SVC_Success;
  /* Note: any name that is a substring of another name must come before that name */
  if (strstr("GEODETIC", str))
  {
    *val = Geodetic;
  }
  else if (strstr("GEOREF", str))
  {
    *val = GEOREF;
  }
  else if (strstr("GEOCENTRIC", str))
  {
    *val = Geocentric;
  }
  else if (strstr("LOCAL CARTESIAN", str))
  {
    *val = Local_Cartesian;
  }
  else if (strstr("MILITARY GRID REFERENCE SYSTEM (MGRS)", str))
  {
    *val = MGRS;
  }
  else if (strstr("UNITED STATES NATIONAL GRID (USNG)", str))
  {
    *val = USNG;
  }
  else if (strstr("MERCATOR", str))
  {
    *val = Mercator;
  }
  else if (strstr("OBLIQUE MERCATOR", str))
  {
    *val = Oblique_Mercator;
  }
  else if (strstr("TRANSVERSE MERCATOR", str))
  {
    *val = Transverse_Mercator;
  }
  else if (strstr("UNIVERSAL TRANSVERSE MERCATOR (UTM)", str))
  {
    *val = UTM;
  }
  else if (strstr("STEREOGRAPHIC", str))
  {
    *val = Stereographic;
  }
  else if (strstr("POLAR STEREOGRAPHIC", str))
  {
    *val = Polar_Stereo;
  }
  else if (strstr("UNIVERSAL POLAR STEREOGRAPHIC (UPS)", str))
  {
    *val = UPS;
  }
  else if (strstr("ALBERS EQUAL AREA CONIC", str))
  {
    *val = Albers_Equal_Area_Conic;
  }
  else if (strstr("AZIMUTHAL EQUIDISTANT", str))
  {
    *val = Azimuthal_Equidistant;
  }
  else if (strstr("BONNE", str))
  {
    *val = Bonne;
  }
  else if (strstr("BRITISH NATIONAL GRID (BNG)", str))
  {
    *val = BNG;
  }
  else if (strstr("CASSINI", str))
  {
    *val = Cassini;
  }
  else if (strstr("ECKERT IV", str))
  {
    *val = Eckert4;
  }
  else if (strstr("ECKERT VI", str))
  {
    *val = Eckert6;
  }
  else if (strstr("EQUIDISTANT CYLINDRICAL", str))
  {
    *val = Equidistant_Cylindrical;
  }
  else if (strstr("GLOBAL AREA REFERENCE SYSTEM (GARS)", str))
  {
    *val = GARS;
  }
  else if (strstr("GNOMONIC", str))
  {
    *val = Gnomonic;
  }
  else if ((strstr("LAMBERT CONFORMAL CONIC", str)) ||
           (strstr("LAMBERT CONFORMAL CONIC (2 PARALLEL)", str)))
  {
    *val = Lambert_Conformal_Conic_2;
  }
  else if (strstr("LAMBERT CONFORMAL CONIC (1 PARALLEL)", str))
  {
    *val = Lambert_Conformal_Conic_1;
  }
  else if (strstr("MILLER CYLINDRICAL", str))
  {
    *val = Miller_Cylindrical;
  }
  else if (strstr("MOLLWEIDE", str))
  {
    *val = Mollweide;
  }
  else if ((strstr("NEY'S (MODIFIED LAMBERT CONFORMAL CONIC)", str)) ||
           (strstr("NEYS (MODIFIED LAMBERT CONFORMAL CONIC)", str)))
  {
    *val = Neys;
  }
  else if (strstr("NEW ZEALAND MAP GRID (NZMG)", str))
  {
    *val = NZMG;
  }
  else if (strstr("ORTHOGRAPHIC", str))
  {
    *val = Orthographic;
  }
  else if (strstr("POLYCONIC", str))
  {
    *val = Polyconic;
  }
  else if (strstr("SINUSOIDAL", str))
  {
    *val = Sinusoidal;
  }
  else if (strstr("CYLINDRICAL EQUAL AREA", str))
  {
    *val = Cylindrical_Equal_Area;
  }
  else if (strstr("TRANSVERSE CYLINDRICAL EQUAL AREA", str))
  {
    *val = Transverse_Cylindrical_Equal_Area;
  }
  else if (strstr("VAN DER GRINTEN", str))
  {
    *val = Van_der_Grinten;
  }
  else
  {
    error_Code = SVC_Invalid_Projection_String;
  }

  return error_Code;
}


SVC_Status Projection_to_String(const Coordinate_Type val, char str[32])
{
  SVC_Status error_Code = SVC_Success;

  switch (val)
  {
  case Geodetic:
    {
      strcpy(str, "Geodetic");
      break;
    }
  case GEOREF:
    {
      strcpy(str, "GEOREF");
      break;
    }
  case Geocentric:
    {
      strcpy(str, "Geocentric");
      break;
    }
  case Local_Cartesian:
    {
      strcpy(str, "Local Cartesian");
      break;
    }
  case MGRS:
    {
      strcpy(str, "Military Grid Reference System (MGRS)");
      break;
    }
  case USNG:
    {
      strcpy(str, "United States National Grid (USNG)");
      break;
    }
  case UTM:
    {
      strcpy(str, "Universal Transverse Mercator (UTM)");
      break;
    }
  case UPS:
    {
      strcpy(str, "Universal Polar Stereographic (UPS)");
      break;
    }
  case Albers_Equal_Area_Conic:
    {
      strcpy(str, "Albers Equal Area Conic");
      break;
    }
  case Azimuthal_Equidistant:
    {
      strcpy(str, "Azimuthal Equidistant");
      break;
    }
  case BNG:
    {
      strcpy(str, "British National Grid (BNG)");
      break;
    }
  case Bonne:
    {
      strcpy(str, "Bonne");
      break;
    }
  case Cassini:
    {
      strcpy(str, "Cassini");
      break;
    }
  case Cylindrical_Equal_Area:
    {
      strcpy(str, "Cylindrical Equal Area");
      break;
    }
  case Eckert4:
    {
      strcpy(str, "Eckert IV");
      break;
    }
  case Eckert6:
    {
      strcpy(str, "Eckert VI");
      break;
    }
  case Equidistant_Cylindrical:
    {
      strcpy(str, "Equidistant Cylindrical");
      break;
    }
  case GARS:
    {
      strcpy(str, "Global Area Reference System (GARS)");
      break;
    }
  case Gnomonic:
    {
      strcpy(str, "Gnomonic");
      break;
    }
  case Lambert_Conformal_Conic_1:
    {
      strcpy(str, "Lambert Conformal Conic (1 parallel)");
      break;
    }
  case Lambert_Conformal_Conic_2:
    {
      strcpy(str, "Lambert Conformal Conic (2 parallel)");
      break;
    }
  case Mercator:
    {
      strcpy(str, "Mercator");
      break;
    }
  case Miller_Cylindrical:
    {
      strcpy(str, "Miller Cylindrical");
      break;
    }
  case Mollweide:
    {
      strcpy(str, "Mollweide");
      break;
    }
  case Neys:
    {
      strcpy(str, "Ney's (Modified Lambert Conformal Conic)");
      break;
    }
  case NZMG:
    {
      strcpy(str, "New Zealand Map Grid (NZMG)");
      break;
    }
  case Oblique_Mercator:
    {
      strcpy(str, "Oblique Mercator");
      break;
    }
  case Orthographic:
    {
      strcpy(str, "Orthographic");
      break;
    }
  case Polar_Stereo:
    {
      strcpy(str, "Polar Stereographic");
      break;
    }
  case Polyconic:
    {
      strcpy(str, "Polyconic");
      break;
    }
  case Sinusoidal:
    {
      strcpy(str, "Sinusoidal");
      break;
    }
  case Stereographic:
    {
      strcpy(str, "Stereographic");
      break;
    }
  case Transverse_Mercator:
    {
      strcpy(str, "Transverse Mercator");
      break;
    }
  case Transverse_Cylindrical_Equal_Area:
    {
      strcpy(str, "Transverse Cylindrical Equal Area");
      break;
    }
  case Van_der_Grinten:
    {
      strcpy(str, "Van der Grinten");
      break;
    }
  default:
    error_Code = SVC_Invalid_Projection_Value;
    break;
  }

  return error_Code;
}


double Round_Meter(const double Value)
/*
 *  The function Round Meter rounds the specified value, in meters, according to
 *  the current precision level.
 *  Value         : Value to be rounded                                 (input)
 */
{ /* Round_Meter */
  double avalue;
  double divisor = 1.0;
  double fraction;
  double ivalue;
  double result;
  long ival = 0;
  long sign = 1;
  switch (Lat_Long_Prec)
  {
  case Degree:
    {
      divisor = 100000.0;
      break;
    }
  case Ten_Minutes:
    {
      divisor = 10000.0;
      break;
    }
  case Minute:
    {
      divisor = 1000.0;
      break;
    }
  case Ten_Seconds:
    {
      divisor = 100.0;
      break;
    }
  case Second:
    {
      divisor = 10.0;
      break;
    }
  case Tenth_of_Second:
    {
      divisor = 1.0;
      break;
    }
  case Hundredth_of_Second:
    {
      divisor = 0.1;
      break;
    }
  case Thousandth_of_Second:
    {
      divisor = 0.01;
      break;
    }
  case Ten_Thousandth_of_Second:
    {
      divisor = 0.001;
      break;
    }
  }
  if (Value < 0.0)
    sign = -1;
  avalue = fabs (Value / divisor);
  fraction = modf (avalue, &ivalue);
  ival = (long)(ivalue);
  if ((fraction > 0.5) || ((fraction == 0.5) && (ival%2 == 1)))
    ivalue++;
  result = (double)(ivalue * divisor * sign);
  return ( result );
} /* Round_Meter */


SVC_Status Meter_to_String(const double meters, char str[15])
{
  SVC_Status error_Code = SVC_Success;

  double meter_Value = Round_Meter(meters);

  if (Lat_Long_Prec > 4)
    if (sprintf(str, "%1.*lf",(int)(Lat_Long_Prec - 5), meter_Value) <= 0)
      error_Code = SVC_Meter_to_String;
    else
      error_Code = SVC_Success;
  else
    if (sprintf(str, "%1.0lf", meter_Value) <= 0)
      error_Code = SVC_Meter_to_String;
    else
      error_Code = SVC_Success;

  return error_Code;
}


SVC_Status Long_Meter_to_String(const double meters, char str[15])
{
  SVC_Status error_Code = SVC_Success;

  double meter_Value = Round_Meter(meters);

  if (Lat_Long_Prec > 4)
    if (sprintf(str, "%1.*lf",(int)(Lat_Long_Prec - 5), meter_Value) <= 0)
      error_Code = SVC_Meter_to_String;
    else
      error_Code = SVC_Success;
  else
    if (sprintf(str, "%1.0lf", meter_Value) <= 0)
      error_Code = SVC_Meter_to_String;
    else
      error_Code = SVC_Success;

  return error_Code;
}


SVC_Status String_to_Double(const char *str, double *val)
{
  char *placeholder = NULL;
  SVC_Status error_Code = SVC_Success;

  *val = 0;
  if (Valid_Number(str))
  {
    *val = strtod(str,&placeholder);
    return (error_Code);
  }
  else
    return (SVC_Error);
}


long Valid_Number(const char *str)
{
  int i = 0;
  long valid = 1;
  int length;
  int deci = 0;

  if (str)
  {
    length = strlen(str);
    if ((i<length) && ((str[i] == '-') || (str[i] == '+')))
      i ++;
    while (valid && (i < length))
    {
      if (!isdigit(str[i]))
      {
        if ((str[i] == '.') && !deci)
        {
          i++;
          deci = 1;
        }
        else
          valid = 0;
      }
      else
        i++;
    }
  }
  return (valid);
}


SVC_Status String_to_Long(const char *str, long *val)
{
  long return_Parameter = 0;
  char *placeholder = NULL;
  SVC_Status error_Code = SVC_Success;

  if (str && strlen(str))
  {
    return_Parameter = strtol(str, &placeholder, 10);
  }

  if ((return_Parameter == 0) && (placeholder == str))
  {
    error_Code = SVC_String_to_Long;
  }

  *val = return_Parameter;
  return error_Code;
}


long Valid_Coord(char *str, long Type)
{
  long Decimal = false;
  long Signed = false;
  long Separators = 0;
  long Valid = true;
  long Length;
  long Pos = 0;

  if (str != NULL)
  {
    Length = strlen(str);
    if ((Pos<Length) && ((str[Pos] == '-') || (str[Pos] == '+')))
    {
      Signed = true;
      Pos ++;
    }
    while ((Pos < Length) && Valid)
    {
      if (str[Pos] == '.')
      {
        if (Decimal)
          Valid = false;
        else
        {
          Decimal = true;
          Pos++;
        }
      }
      else if (isdigit(str[Pos]))
      {
        Pos++;
      }
      else if ((str[Pos] == ' ') || (str[Pos] == '/') || (str[Pos] == ':'))
      {
        if (Separators >= 3)
          Valid = false;
        else
        {
          Pos++;
          Separators++;
        }
      }
      else if (isalpha(str[Pos]))
      {
        str[Pos] = (char)toupper(str[Pos]);
        if ((((str[Pos] == 'N') || (str[Pos] == 'S')) && (Type == Lat_String))
            || (((str[Pos] == 'W') || (str[Pos] == 'E')) && (Type == Long_String)))
        {
          if (Signed)
            Valid = false;
          Pos++;
          if (Pos != Length)
            Valid = false;
        }
        else
          Valid = false;
      }
      else
        Valid = false;
    }
  }
  return (Valid);
}


SVC_Status String_to_Longitude(const char *str, double *val)
{
  SVC_Status error_Code = SVC_Success;

  double degrees = 0.0;
  double minutes = 0.0;
  double seconds = 0.0;
  long sign = 1;
  char *reference_Pointer;
  char *parse_String;
  char *next_Str = 0;
  /* Longitudes may have the following format :

     PDDD/MM/SS.FFH
     PDDD/MM.FFFFH
     PDDD.FFFFFFH

     where these are defined as follows
     P = optional plus/minus
     D = degrees (up to three places)
     M = minutes (up to two places)
     S = seconds (up to two places)
     F = floating-point precision (up to 6 places)
     H = optional hemisphere (NSEW)
     / = separator character, one of ':' , '/' , ' '
  */
  if (strlen(str))
  {
    reference_Pointer = strdup_(str);
    parse_String = reference_Pointer;
    if (Valid_Coord(reference_Pointer,Long_String))
    {
      if (parse_String[0] == '-')
      {
        sign = -1;
      }

      next_Str = strtok(parse_String, ":/ ");

      if (next_Str != NULL)
      {
        degrees = atof(next_Str);
      }

      next_Str = strtok(NULL, ":/ ");

      if (next_Str != NULL)
      {
        minutes = atof(next_Str);
      }

      next_Str = strtok(NULL, ":/ ");

      if (next_Str != NULL)
      {
        seconds = atof(next_Str);
      }

      if ((strchr(str, 'N') != NULL) ||
          (strchr(str, 'S') != NULL))
      {
        error_Code = SVC_Inappropriate_Hemisphere;
      }

      if (((next_Str = strchr(str, 'E')) != NULL)
          || ((next_Str = strchr(str, 'e')) != NULL))
      {
        if (sign == -1)
        {
          error_Code = SVC_Sign_and_Hemisphere;
        }

        if (next_Str[1] != '\0')
        {
          error_Code = SVC_Misplaced_Hemisphere;
        }
      }

      if (((next_Str = strchr(str, 'W')) != NULL)
          || ((next_Str = strchr(str, 'w')) != NULL))
      {
        if (sign == -1)
        {
          error_Code = SVC_Sign_and_Hemisphere;
        }

        if (next_Str[1] == '\0')
        {
          sign = -1;
        }
        else
        {
          error_Code = SVC_Misplaced_Hemisphere;
        }
      }

      if (seconds >= 60 || seconds < 0)
      {
        error_Code = SVC_Seconds_out_of_Bounds;
      }

      if (minutes >= 60 || minutes < 0)
      {
        error_Code = SVC_Minutes_out_of_Bounds;
      }

      if ((degrees == -180 || degrees == 360) &&
          ((minutes != 0) || (seconds != 0)))
      {
        error_Code = SVC_Minutes_or_Seconds_Overflow;
      }

      /* Convert DMS to fractional degrees */
      *val = ( fabs(degrees) + (minutes / 60.0) + (seconds / 3600.0) ) * sign;

      /* Convert longitude to be between -180 and 180 */
			if (*val > 180)
				*val -= 360;

      if ((*val > 360) || (*val < -180))
      {
        error_Code = SVC_Degrees_out_of_Bounds;
      }

      if (error_Code != SVC_Success)
      {
        *val = 0;
      }
    }
    else
      error_Code = SVC_Error;

    free(reference_Pointer);
  }
  return error_Code;
}/* String_to_Longitude */


SVC_Status Longitude_to_String(const double in_longitude, char str[15],
                               boole use_NSEW, boole use_Minutes, boole use_Seconds)
{/* Longitude_to_String */
  double degrees = 0.0;
  double longitude;
  char degrees_As_String[15];
  long starting_Index = 0;
  long ending_Index = 13;
  SVC_Status error_Code = SVC_Success;

  longitude = in_longitude;
  if ((longitude > -0.00000001) && (longitude < 0.00000001))
  {
    longitude = 0.0;
  }
  strcpy(degrees_As_String,"              ");
  switch (Long_Range)
  {
  case _180_180:
    {
      if (longitude > 180)
        degrees = fabs(longitude - 360);
      else
        degrees = fabs(longitude);
      break;
    }
  case _0_360:
    {
      if (longitude < 0)
        degrees = longitude + 360;
      else
        degrees = longitude;
      break;
    }
  }
  Degrees_to_String(degrees, &degrees_As_String[1], use_Minutes, use_Seconds, Long_String);
  ending_Index = strlen(&degrees_As_String[1]) + 1;
  starting_Index = 1;
  switch (Long_Range)
  {
  case _180_180:
    {
      if (use_NSEW)
      {
        if ((longitude > 180) || (longitude < 0))
          degrees_As_String[ending_Index] = 'W';
        else
          degrees_As_String[ending_Index] = 'E';
      }
      else
      {
        if ((longitude > 180) || (longitude < 0))
        {
          degrees_As_String[0] = '-';
          starting_Index = 0;
        }
      }
      break;
    }
  case _0_360:
    {
      if (use_NSEW)
        degrees_As_String[ending_Index] = 'E';
      break;
    }
  }
  degrees_As_String[ending_Index+1] = '\0';
  strcpy(str, &degrees_As_String[starting_Index]);
  return error_Code;
}


void Round_DMS(double *val, long place)
{
  double temp;
  double fraction;
  double int_temp;

  temp = *val * pow(10,place);

  fraction = modf(temp, &int_temp);
  if (((temp - int_temp) > 0.5) ||
      (((temp - int_temp) == 0.5) && (fmod(int_temp,2.0) == 1.0)))
    *val = (int_temp + 1.0) / pow(10,place);
  else
    *val = int_temp / pow(10,place);
}


void Degrees_to_String(double degrees, char *str, boole use_Minutes, boole use_Seconds, long Type)
{
  double minutes = 0.0;
  double seconds = 0.0;
  long integer_Degrees = 0;
  long integer_Minutes = 0;
  long integer_Seconds = 0;
  int j;

  if ((!use_Minutes) || (Lat_Long_Prec == 0))
  { /* Decimal Degrees */
    Round_DMS(&degrees, Lat_Long_Prec);
    if(leading_zeros)
    {
      if(Type == Lat_String)
        if(fabs(degrees) < 10)
          sprintf(str,"0%1.*lf",(int)Lat_Long_Prec,degrees);
        else
          sprintf(str,"%1.*lf",(int)Lat_Long_Prec,degrees);
      else
        if(fabs(degrees) < 10)
          sprintf(str,"00%1.*lf",(int)Lat_Long_Prec,degrees);
        else if(fabs(degrees) < 100)
          sprintf(str,"0%1.*lf",(int)Lat_Long_Prec,degrees);
        else
          sprintf(str,"%1.*lf",(int)Lat_Long_Prec,degrees);
    }
    else
      sprintf(str,"%1.*lf",(int)Lat_Long_Prec,degrees);
  }
  else if ((use_Minutes && !use_Seconds) || (Lat_Long_Prec <= 2))
  { /* Degrees & Minutes */
    integer_Degrees = (long)degrees;
    minutes = (degrees - integer_Degrees) * 60.0;
    Round_DMS(&minutes, Lat_Long_Prec - 2);
    integer_Minutes = (long)minutes;
    if (integer_Minutes >= 60)
    {
      integer_Minutes -= 60;
      integer_Degrees += 1;
    }
    if (Lat_Long_Prec <= 2)
    {
      if(leading_zeros)
      {
        if(Type == Lat_String)
          if(fabs(degrees) < 10)
            j = sprintf(str,"0%ld%c",integer_Degrees,Lat_Long_Sep);
          else
            j = sprintf(str,"%ld%c",integer_Degrees,Lat_Long_Sep);
        else
          if(fabs(degrees) < 10)
            j = sprintf(str,"00%ld%c",integer_Degrees,Lat_Long_Sep);
          else if(fabs(degrees) < 100)
            j = sprintf(str,"0%ld%c",integer_Degrees,Lat_Long_Sep);
          else
            j = sprintf(str,"%ld%c",integer_Degrees,Lat_Long_Sep);

        if(integer_Minutes < 10)
          j += sprintf(str + j,"0%ld",integer_Minutes);
        else
          j += sprintf(str + j,"%ld",integer_Minutes);
      }
      else
        sprintf(str,"%ld%c%ld",integer_Degrees,Lat_Long_Sep,integer_Minutes);
    }
    else
    {
      if (minutes >= 60)
        minutes -= 60;
      if(leading_zeros)
      {
        if(Type == Lat_String)
          if(fabs(degrees) < 10)
            j = sprintf(str,"0%ld%c",integer_Degrees,Lat_Long_Sep);
          else
            j = sprintf(str,"%ld%c",integer_Degrees,Lat_Long_Sep);
        else
          if(fabs(degrees) < 10)
            j = sprintf(str,"00%ld%c",integer_Degrees,Lat_Long_Sep);
          else if(fabs(degrees) < 100)
            j = sprintf(str,"0%ld%c",integer_Degrees,Lat_Long_Sep);
          else
            j = sprintf(str,"%ld%c",integer_Degrees,Lat_Long_Sep);

        if(integer_Minutes < 10)
          j += sprintf(str + j,"0%1.*lf",(int)Lat_Long_Prec-2,minutes);
        else
          j += sprintf(str + j,"%1.*lf",(int)Lat_Long_Prec-2,minutes);
      }
      else
        sprintf(str,"%ld%c%1.*lf",integer_Degrees,Lat_Long_Sep,(int)Lat_Long_Prec-2,minutes);
    }
  }
  else
  { /* Degrees, Minutes, & Seconds */
    integer_Degrees = (long)degrees;
    minutes = (degrees - integer_Degrees) * 60.0;
    integer_Minutes = (long)minutes;
    seconds = (minutes - integer_Minutes) * 60.0;
    Round_DMS(&seconds, Lat_Long_Prec - 4);
    integer_Seconds = (long)seconds;
    if (integer_Seconds >= 60)
    {
      integer_Seconds -= 60;
      integer_Minutes += 1;
      if (integer_Minutes >= 60)
      {
        integer_Degrees += 1;
        integer_Minutes -= 60;
      }
    }

    if (Lat_Long_Prec <= 4)
    {
      if(leading_zeros)
      {
        if(Type == Lat_String)
          if(fabs(degrees) < 10)
            j = sprintf(str,"0%ld%c",integer_Degrees,Lat_Long_Sep);
          else
            j = sprintf(str,"%ld%c",integer_Degrees,Lat_Long_Sep);
        else
          if(fabs(degrees) < 10)
            j = sprintf(str,"00%ld%c",integer_Degrees,Lat_Long_Sep);
          else if(fabs(degrees) < 100)
            j = sprintf(str,"0%ld%c",integer_Degrees,Lat_Long_Sep);
          else
            j = sprintf(str,"%ld%c",integer_Degrees,Lat_Long_Sep);

        if(integer_Minutes < 10)
          j += sprintf(str + j,"0%ld%c",integer_Minutes,Lat_Long_Sep);
        else
          j += sprintf(str + j,"%ld%c",integer_Minutes,Lat_Long_Sep);

        if(integer_Seconds < 10)
          j += sprintf(str + j,"0%ld",integer_Seconds);
        else
          j += sprintf(str + j,"%ld",integer_Seconds);
      }
      else
        sprintf(str,"%ld%c%ld%c%ld",integer_Degrees,Lat_Long_Sep,integer_Minutes,Lat_Long_Sep,integer_Seconds);
    }
    else
    {
      if (seconds >= 60)
      {
        seconds -= 60;
      }
      if(leading_zeros)
      {
        if(Type == Lat_String)
          if(fabs(degrees) < 10)
            j = sprintf(str,"0%ld%c",integer_Degrees,Lat_Long_Sep);
          else
            j = sprintf(str,"%ld%c",integer_Degrees,Lat_Long_Sep);
        else
          if(fabs(degrees) < 10)
            j = sprintf(str,"00%ld%c",integer_Degrees,Lat_Long_Sep);
          else if(fabs(degrees) < 100)
            j = sprintf(str,"0%ld%c",integer_Degrees,Lat_Long_Sep);
          else
            j = sprintf(str,"%ld%c",integer_Degrees,Lat_Long_Sep);

        if(integer_Minutes < 10)
          j += sprintf(str + j,"0%ld%c",integer_Minutes,Lat_Long_Sep);
        else
          j += sprintf(str + j,"%ld%c",integer_Minutes,Lat_Long_Sep);

        if(integer_Seconds < 10)
          j += sprintf(str + j,"0%1.*lf",(int)Lat_Long_Prec-4,seconds);
        else
          j += sprintf(str + j,"%1.*lf",(int)Lat_Long_Prec-4,seconds);
      }
      else
        sprintf(str,"%ld%c%ld%c%1.*lf",integer_Degrees,Lat_Long_Sep,integer_Minutes,Lat_Long_Sep,(int)Lat_Long_Prec-4,seconds);
    }
  }
}


SVC_Status String_to_Latitude(const char *str, double *val)
{
  SVC_Status error_Code = SVC_Success;

  double degrees = 0.0;
  double minutes = 0.0;
  double seconds = 0.0;
  long sign = 1;
  char *reference_Pointer;
  char *parse_String;
  char *next_Str = 0;
  /* Longitudes may have the following format :

     PDD/MM/SS.FFH
     PDD/MM.FFFFH
     PDD.FFFFFFH

     where these are defined as follows
     P = optional plus/minus
     D = degrees (up to two places)
     M = minutes (up to two places)
     S = seconds (up to two places)
     F = floating-point precision (up to 6 places)
     H = optional hemisphere (NSEW)
     / = separator character, one of / : sp
  */

  if (strlen(str))
  {
    reference_Pointer = strdup_(str);
    parse_String = reference_Pointer;
    if (Valid_Coord(reference_Pointer,Lat_String))
    {
      if (parse_String[0] == '-')
      {
        sign = -1;
      }

      next_Str = strtok(parse_String, ":/ ");

      if (next_Str != NULL)
      {
        degrees = atof(next_Str);
      }

      next_Str = strtok(NULL, ":/ ");

      if (next_Str != NULL)
      {
        minutes = atof(next_Str);
      }

      next_Str = strtok(NULL, ":/ ");

      if (next_Str != NULL)
      {
        seconds = atof(next_Str);
      }

      if ((strchr(str, 'W') != NULL) ||
          (strchr(str, 'E') != NULL))
      {
        error_Code = SVC_Inappropriate_Hemisphere;
      }

      if (((next_Str = strchr(str, 'N')) != NULL)
          || ((next_Str = strchr(str, 'n')) != NULL))
      {
        if (sign == -1)
        {
          error_Code = SVC_Sign_and_Hemisphere;
        }

        if (next_Str[1] != '\0')
        {
          error_Code = SVC_Misplaced_Hemisphere;
        }
      }

      if (((next_Str = strchr(str, 'S')) != NULL)
          || ((next_Str = strchr(str, 's')) != NULL))
      {
        if (sign == -1)
        {
          error_Code = SVC_Sign_and_Hemisphere;
        }

        if (next_Str[1] == '\0')
        {
          sign = -1;
        }
        else
        {
          error_Code = SVC_Misplaced_Hemisphere;
        }
      }

      if (seconds >= 60 || seconds < 0)
      {
        error_Code = SVC_Seconds_out_of_Bounds;
      }

      if (minutes >= 60 || minutes < 0)
      {
        error_Code = SVC_Minutes_out_of_Bounds;
      }

      if (degrees < -90 || degrees > 90)
      {
        error_Code = SVC_Degrees_out_of_Bounds;
      }

      if ((degrees == -90 || degrees == 90) &&
          ((minutes != 0) || (seconds != 0)))
      {
        error_Code = SVC_Minutes_or_Seconds_Overflow;
      }

      /* Convert DMS to fractional degrees */
      *val = (double)( fabs(degrees) + (minutes / 60) + (seconds / 3600) ) * sign;

      if (error_Code != SVC_Success)
      {
        *val = 0;
      }
    }
    else
      error_Code = SVC_Error;

    free(reference_Pointer);
  }
  return error_Code;
}


SVC_Status Latitude_to_String(const double in_latitude, char str[14],
                              boole use_NSEW, boole use_Minutes, boole use_Seconds)
{
  double degrees = fabs(in_latitude);
  double latitude;
  char degrees_As_String[14];
  long starting_Index = 1;
  SVC_Status error_Code = SVC_Success;
  long ending_Index = 12;

  latitude = in_latitude;
  if ((latitude > -0.00000001) && (latitude < 0.00000001))
  {
    latitude = 0.0;
  }
  strcpy(degrees_As_String,"             ");
  Degrees_to_String(degrees, &degrees_As_String[1], use_Minutes, use_Seconds, Lat_String);
  ending_Index = strlen(&degrees_As_String[1]) + 1;

  if (use_NSEW)
  {
    if (latitude < 0)
    {
      degrees_As_String[ending_Index] = 'S';
    }
    else
    {
      degrees_As_String[ending_Index] = 'N';
    }
  }
  else
  {
    if (latitude < 0)
    {
      degrees_As_String[0] = '-';
      starting_Index = 0;
    }
  }
  degrees_As_String[ending_Index+1] = '\0';
  strcpy(str, &degrees_As_String[starting_Index]);
  return error_Code;
}


SVC_Status Zone_to_String(const long zone, char str[3])
{
  SVC_Status error_Code = SVC_Success;

  if( zone < 10 )
  {
    if (sprintf(str, "%1d", zone) <= 0)
    {
      error_Code = SVC_Zone_to_String;
    }
  }
  else
  {
    if (sprintf(str, "%2d", zone) <= 0)
    {
      error_Code = SVC_Zone_to_String;
    }
  }

  return error_Code;
}


SVC_Status Ellipsoidal_Height_to_String(const double ellipsoidal_Height, char str[15])
{
  return Long_Meter_to_String(ellipsoidal_Height, str);
}


SVC_Status Scale_Factor_to_String(const double scale_Factor, char str[8])
{
  SVC_Status error_Code = SVC_Success;

  if (sprintf(str, "%.5f", scale_Factor) <= 0)
  {
    error_Code = SVC_Scale_Factor_to_String;
  }

  return error_Code;
}


void Error_Prefix
( const Input_or_Output Direction,
  const Coordinate_Type System,
  char  *Separator,
  char  *String)
{
  char   *in_out;
  if (Direction == Input)
    in_out = "Input";
  else
    in_out = "Output";
  switch (System)
  {
  case Geocentric:
    {
      sprintf(String,"%s%s%s%s",in_out," Geocentric Coordinates:",Separator,Separator);
      break;
    }
  case Geodetic:
    {
      sprintf(String,"%s%s%s%s",in_out," Geodetic Coordinates:",Separator,Separator);
      break;
    }
  case GEOREF:
    {
      sprintf(String,"%s%s%s%s",in_out," GEOREF Coordinates:",Separator,Separator);
      break;
    }
  case Albers_Equal_Area_Conic:
    {
      sprintf(String,"%s%s%s%s",in_out," Albers Equal Area Conic Projection:",Separator,Separator);
      break;
    }
  case Azimuthal_Equidistant:
    {
      sprintf(String,"%s%s%s%s",in_out," Azimuthal Equidistant Projection:",Separator,Separator);
      break;
    }
  case BNG:
    {
      sprintf(String,"%s%s%s%s",in_out," British National Grid Coordinates:",Separator,Separator);
      break;
    }
  case Bonne:
    {
      sprintf(String,"%s%s%s%s",in_out," Bonne Projection:",Separator,Separator);
      break;
    }
  case Cassini:
    {
      sprintf(String,"%s%s%s%s",in_out," Cassini Projection:",Separator,Separator);
      break;
    }
  case Cylindrical_Equal_Area:
    {
      sprintf(String,"%s%s%s%s",in_out," Cylindrical Equal Area Projection:",Separator,Separator);
      break;
    }
  case Eckert4:
    {
      sprintf(String,"%s%s%s%s",in_out," Eckert IV Projection:",Separator,Separator);
      break;
    }
  case Eckert6:
    {
      sprintf(String,"%s%s%s%s",in_out," Eckert VI Projection:",Separator,Separator);
      break;
    }
  case Equidistant_Cylindrical:
    {
      sprintf(String,"%s%s%s%s",in_out," Equidistant Cylindrical Projection:",Separator,Separator);
      break;
    }
  case GARS:
    {
      sprintf(String,"%s%s%s%s",in_out," GARS Coordinates:",Separator,Separator);
      break;
    }
  case Gnomonic:
    {
      sprintf(String,"%s%s%s%s",in_out," Gnomonic Projection:",Separator,Separator);
      break;
    }
  case Lambert_Conformal_Conic_1:
    {
      sprintf(String,"%s%s%s%s",in_out," Lambert Conformal Conic (1 parallel) Projection:",Separator,Separator);
      break;
    }
  case Lambert_Conformal_Conic_2:
    {
      sprintf(String,"%s%s%s%s",in_out," Lambert Conformal Conic (2 parallel) Projection:",Separator,Separator);
      break;
    }
  case Local_Cartesian:
    {
      sprintf(String,"%s%s%s%s",in_out," Local Cartesian Coordinates:",Separator,Separator);
      break;
    }
  case Mercator:
    {
      sprintf(String,"%s%s%s%s",in_out," Mercator Projection:",Separator,Separator);
      break;
    }
  case MGRS:
    {
      sprintf(String,"%s%s%s%s",in_out," MGRS Coordinates:",Separator,Separator);
      break;
    }
  case Miller_Cylindrical:
    {
      sprintf(String,"%s%s%s%s",in_out," Miller Cylindrical Projection:",Separator,Separator);
      break;
    }
  case Mollweide:
    {
      sprintf(String,"%s%s%s%s",in_out," Mollweide Projection:",Separator,Separator);
      break;
    }
  case Neys:
    {
      sprintf(String,"%s%s%s%s",in_out," Ney's Projection:",Separator,Separator);
      break;
    }
  case NZMG:
    {
      sprintf(String,"%s%s%s%s",in_out," New Zealand Map Grid Projection:",Separator,Separator);
      break;
    }
  case Oblique_Mercator:
    {
      sprintf(String,"%s%s%s%s",in_out," Oblique Mercator Projection:",Separator,Separator);
      break;
    }
  case Orthographic:
    {
      sprintf(String,"%s%s%s%s",in_out," Orthographic Projection:",Separator,Separator);
      break;
    }
  case Polar_Stereo:
    {
      sprintf(String,"%s%s%s%s",in_out," Polar Stereographic Projection:",Separator,Separator);
      break;
    }
  case Polyconic:
    {
      sprintf(String,"%s%s%s%s",in_out," Polyconic Projection:",Separator,Separator);
      break;
    }
  case Sinusoidal:
    {
      sprintf(String,"%s%s%s%s",in_out," Sinusoidal Projection:",Separator,Separator);
      break;
    }
  case Stereographic:
    {
      sprintf(String,"%s%s%s%s",in_out," Stereographic Projection:",Separator,Separator);
      break;
    }
  case Transverse_Cylindrical_Equal_Area:
    {
      sprintf(String,"%s%s%s%s",in_out," Transverse Cylindrical Equal Area Projection:",Separator,Separator);
      break;
    }
  case Transverse_Mercator:
    {
      sprintf(String,"%s%s%s%s",in_out," Transverse Mercator Projection:",Separator,Separator);
      break;
    }
  case UPS:
    {
      sprintf(String,"%s%s%s%s",in_out," UPS Coordinates:",Separator,Separator);
      break;
    }
  case USNG:
    {
      sprintf(String,"%s%s%s%s",in_out," USNG Coordinates:",Separator,Separator);
      break;
    }
  case UTM:
    {
      sprintf(String,"%s%s%s%s",in_out," UTM Coordinates:",Separator,Separator);
      break;
    }
  case Van_der_Grinten:
    {
      sprintf(String,"%s%s%s%s",in_out," Van der Grinten Projection:",Separator,Separator);
      break;
    }
  } /* switch */
}

void Error_Append (char *New_String,
                   char *Separator,
                   char *String)
{
  strcat(String,New_String);
  strcat(String,Separator);
}
