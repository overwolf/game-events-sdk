/********************************************************************************************
* Overwolf Game Events Library
*
* Copyright (c) 2015 Overwolf Ltd.
*********************************************************************************************/
#ifndef LIBOWGAMEEVENTS_OWGAME_EVENTS_H_
#define LIBOWGAMEEVENTS_OWGAME_EVENTS_H_

#include "errors.h"
#include "types.h"

#ifdef __cplusplus

namespace owgame_events {
extern "C" {

// Step 1: create an owgame_events_handle object
//
// game_id - the Overwolf game id as received from Overwolf Ltd.
//
// categories_count - number of items pass in info_categories
//
// info_categories - predefined array of info categories (and keys) that
// the game will be updating
//
// handle - out param - an owgame_events_handle object to be used with other
// functions (see below)
//
// returns:
//  SUC_OK
OWGameEventsErrors owgame_events_create(
  owgame_id game_id, 
  unsigned int categories_count,
  owgame_info_category* info_categories,
  owgame_events_handle* handle);

// Step 2: update information keys with persistent (as long as the game is 
// running) data that can be accessed by Overwolf apps
//
// handle - an owgame_events_handle that was created with 
// |owgame_events_create|
//
// info_category_name
//
// info_key
//
// value_length
//
// utf8_value
//
// returns:
//  SUC_OK - if succeeded, otherwise >= ERR_UNKNOWN
OWGameEventsErrors owgame_events_set_info_key(
  owgame_events_handle handle,
  const char* category_name,
  const char* info_key,
  unsigned int value_length,
  const char* utf8_value);

// Step 3: trigger real-time game events so that the Overwolf apps can
// perform immediate actions
//
// handle - an owgame_events_handle that was created with 
// |owgame_events_create|
//
// event - an event structure that contains the event name and, optionally,
// an event data
//
// returns:
//  SUC_OK - if succeeded, otherwise >= ERR_UNKNOWN
OWGameEventsErrors owgame_events_trigger_event(
  owgame_events_handle handle,
  owgame_event* event);

// For efficiency reasons, if you wish to update more than one key at once,
// you can begin a transaction -> set info keys -> commit the transaction.
// Once you commit, the Overwolf apps will be notified of all changes at once.
//
// NOTE: you cannot cancel a transaction.
// NOTE: this is only relevant for updating info keys - not for events
//
// handle - an owgame_events_handle that was created with 
// |owgame_events_create|
//
// returns:
//  SUC_OK - if succeeded, otherwise >= ERR_UNKNOWN
OWGameEventsErrors owgame_events_begin_info_transaction(
  owgame_events_handle handle);

// Call |owgame_events_commit_info_transaction| after calling 
// |owgame_events_begin_info_transaction|
//
// handle - an owgame_events_handle that was created with 
// |owgame_events_create|
//
// returns:
//  SUC_OK - if succeeded, otherwise >= ERR_UNKNOWN
OWGameEventsErrors owgame_events_commit_info_transaction(
  owgame_events_handle handle);


// step 4: when done, uninitialize the owgame_events_handle to
// free memory and resources
//
// handle - owgame_events_handle that was created via |owgame_events_create|
OWGameEventsErrors owgame_events_close(owgame_events_handle handle);

// writes internal logs to a file and debugout - used for debugging problems
// with the library
//
// returns:
//  ERR_INVALID_PARAMS
OWGameEventsErrors owgame_events_turn_on_logger(const wchar_t* output_file);

}; // extern "C"
}; // namespace owgame_events

#endif

#endif // LIBOWGAMEEVENTS_OWGAME_EVENTS_H_
