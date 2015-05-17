/********************************************************************************************
* Overwolf Game Events Library
*
* Copyright (c) 2015 Overwolf Ltd.
*********************************************************************************************/
#ifndef LIBOWGAMEEVENTS_ERRORS_H_
#define LIBOWGAMEEVENTS_ERRORS_H_

namespace owgame_events {

typedef enum _OWGameEventsErrors {
  /*****************************************************************************/
  WRN_UNKNOWN = -1000,
  WRN_FAILED_TO_TRIGGER_CONNECT, // couldn't notify Overwolf to connect
  WRN_FAILED_TO_CLEAR_MEM,       // couldn't clear memory when shutting down

  /*****************************************************************************/
  SUC_OK = 0,

  /*****************************************************************************/
  ERR_UNKNOWN = 1000,
  ERR_UNKNOWN_CATASTROPHIC,     // contact Overwolf...
  ERR_INVALID_HANDLE,
  ERR_NOT_INITIALIZED,          // calling a function on an uninitialized handle
  ERR_ALREADY_INITIALIZED,      // currently not possible to receive
  ERR_GENERAL_INIT_FAILURE,     // couldn't start dispatcher thread
  ERR_SAHRED_MEM_INIT_FAILURE,  // check that you don't already have a handle to this game_id
  ERR_INVALID_PARAMS,           // passed invalid parameters (value_length > what you passed in create?)
  ERR_DISPATCHER,               // failed to dispatch request (might happen when closing handle)
  ERR_THROTTLING,               // we limit amount of events: 10 event per 200 ms
} OWGameEventsErrors;

}; // namespace owgame_events

#endif // LIBOWGAMEEVENTS_ERRORS_H_

