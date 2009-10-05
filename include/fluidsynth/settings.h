/* FluidSynth - A Software Synthesizer
 *
 * Copyright (C) 2003  Peter Hanappe and others.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */

#ifndef _FLUIDSYNTH_SETTINGS_H
#define _FLUIDSYNTH_SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file settings.h
 * @brief Synthesizer settings
 * @defgroup SettingsFunctions Functions for settings management
 *
 * To create a synthesizer object you will have to specify its
 * settings. These settings are stored in a fluid_settings_t object.
 * @code
 *     void
 *     my_synthesizer ()
 *     {
 *       fluid_settings_t *settings;
 *       fluid_synth_t *synth;
 *       fluid_audio_driver_t *adriver;
 *
 *       settings = new_fluid_settings ();
 *       fluid_settings_setstr(settings, "audio.driver", "alsa");
 *       // ... change settings ...
 *       synth = new_fluid_synth (settings);
 *       adriver = new_fluid_audio_driver (settings, synth);
 *       // ...
 *     }
 * @endcode
 * @sa @ref CreatingSettings
 * @{
 */

/** Hint FLUID_HINT_BOUNDED_BELOW indicates that the LowerBound field
   of the FLUID_PortRangeHint should be considered meaningful. The
   value in this field should be considered the (inclusive) lower
   bound of the valid range. If FLUID_HINT_SAMPLE_RATE is also
   specified then the value of LowerBound should be multiplied by the
   sample rate. */
#define FLUID_HINT_BOUNDED_BELOW   0x1

/** Hint FLUID_HINT_BOUNDED_ABOVE indicates that the UpperBound field
   of the FLUID_PortRangeHint should be considered meaningful. The
   value in this field should be considered the (inclusive) upper
   bound of the valid range. If FLUID_HINT_SAMPLE_RATE is also
   specified then the value of UpperBound should be multiplied by the
   sample rate. */
#define FLUID_HINT_BOUNDED_ABOVE   0x2

/** Hint FLUID_HINT_TOGGLED indicates that the data item should be
   considered a Boolean toggle. Data less than or equal to zero should
   be considered `off' or `false,' and data above zero should be
   considered `on' or `true.' FLUID_HINT_TOGGLED may not be used in
   conjunction with any other hint except FLUID_HINT_DEFAULT_0 or
   FLUID_HINT_DEFAULT_1. */
#define FLUID_HINT_TOGGLED         0x4

/** Hint FLUID_HINT_SAMPLE_RATE indicates that any bounds specified
   should be interpreted as multiples of the sample rate. For
   instance, a frequency range from 0Hz to the Nyquist frequency (half
   the sample rate) could be requested by this hint in conjunction
   with LowerBound = 0 and UpperBound = 0.5. Hosts that support bounds
   at all must support this hint to retain meaning. */
#define FLUID_HINT_SAMPLE_RATE     0x8

/** Hint FLUID_HINT_LOGARITHMIC indicates that it is likely that the
   user will find it more intuitive to view values using a logarithmic
   scale. This is particularly useful for frequencies and gains. */
#define FLUID_HINT_LOGARITHMIC     0x10

/** Hint FLUID_HINT_INTEGER indicates that a user interface would
   probably wish to provide a stepped control taking only integer
   values. Any bounds set should be slightly wider than the actual
   integer range required to avoid floating point rounding errors. For
   instance, the integer set {0,1,2,3} might be described as [-0.1,
   3.1]. */
#define FLUID_HINT_INTEGER         0x20


#define FLUID_HINT_FILENAME        0x01
#define FLUID_HINT_OPTIONLIST      0x02


/**
 * Settings type
 *
 * Each setting has a defined type: numeric (double), integer, string or a
 * set of values. The type of each setting can be retrieved using the
 * function fluid_settings_get_type()
 */
enum fluid_types_enum {
  FLUID_NO_TYPE = -1,//!< Undefined type
  FLUID_NUM_TYPE,    //!< Numeric (double)
  FLUID_INT_TYPE,    //!< Integer
  FLUID_STR_TYPE,    //!< String
  FLUID_SET_TYPE     //!< Set of values
};


FLUIDSYNTH_API fluid_settings_t* new_fluid_settings(void);
FLUIDSYNTH_API void delete_fluid_settings(fluid_settings_t* settings);

FLUIDSYNTH_API
int fluid_settings_get_type(fluid_settings_t* settings, char* name);

FLUIDSYNTH_API
int fluid_settings_get_hints(fluid_settings_t* settings, char* name);

FLUIDSYNTH_API
int fluid_settings_is_realtime(fluid_settings_t* settings, char* name);

FLUIDSYNTH_API
int fluid_settings_setstr(fluid_settings_t* settings, char* name, char* str);

FLUIDSYNTH_API
int fluid_settings_copystr(fluid_settings_t* settings, char* name, char* str, int len);

FLUIDSYNTH_API
int fluid_settings_dupstr(fluid_settings_t* settings, char* name, char** str);

FLUIDSYNTH_API
int fluid_settings_getstr(fluid_settings_t* settings, char* name, char** str);

FLUIDSYNTH_API
char* fluid_settings_getstr_default(fluid_settings_t* settings, char* name);

FLUIDSYNTH_API
int fluid_settings_str_equal(fluid_settings_t* settings, char* name, char* value);

FLUIDSYNTH_API
int fluid_settings_setnum(fluid_settings_t* settings, char* name, double val);

FLUIDSYNTH_API
int fluid_settings_getnum(fluid_settings_t* settings, char* name, double* val);

FLUIDSYNTH_API
double fluid_settings_getnum_default(fluid_settings_t* settings, char* name);

FLUIDSYNTH_API
void fluid_settings_getnum_range(fluid_settings_t* settings, char* name,
				double* min, double* max);

FLUIDSYNTH_API
int fluid_settings_setint(fluid_settings_t* settings, char* name, int val);

FLUIDSYNTH_API
int fluid_settings_getint(fluid_settings_t* settings, char* name, int* val);

FLUIDSYNTH_API
int fluid_settings_getint_default(fluid_settings_t* settings, char* name);

FLUIDSYNTH_API
void fluid_settings_getint_range(fluid_settings_t* settings, char* name,
				int* min, int* max);

/**
 * Callback function type used with fluid_settings_foreach_option()
 */
typedef void (*fluid_settings_foreach_option_t)(void* data, char* name, char* option);

FLUIDSYNTH_API
void fluid_settings_foreach_option(fluid_settings_t* settings,
				  char* name, void* data,
				  fluid_settings_foreach_option_t func);
FLUIDSYNTH_API
void fluid_settings_foreach_option_alpha (fluid_settings_t* settings,
                                          char* name, void* data,
                                          fluid_settings_foreach_option_t func);
FLUIDSYNTH_API
int fluid_settings_option_count (fluid_settings_t* settings, char* name);

/**
 * Callback function type used with fluid_settings_foreach()
 */
typedef void (*fluid_settings_foreach_t)(void* data, char* s, int type);

FLUIDSYNTH_API
void fluid_settings_foreach(fluid_settings_t* settings, void* data,
			   fluid_settings_foreach_t func);
FLUIDSYNTH_API
void fluid_settings_foreach_alpha(fluid_settings_t* settings, void* data,
                                  fluid_settings_foreach_t func);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _FLUIDSYNTH_SETTINGS_H */
