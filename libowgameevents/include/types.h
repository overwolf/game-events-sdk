/********************************************************************************************
* Overwolf Game Events Library
*
* Copyright (c) 2015 Overwolf Ltd.
*********************************************************************************************/
#ifndef LIBOWGAMEEVENTS_TYPES_H_
#define LIBOWGAMEEVENTS_TYPES_H_

namespace owgame_events {

typedef void* owgame_events_handle;
typedef unsigned int owgame_id;

typedef struct _owgame_info_key {
  const char* key; // key name
  unsigned int size; // size in bytes
} owgame_info_key;

typedef struct _owgame_info_category {
  const char* name; // category name
  unsigned int items; // number of key items in |keys|
  owgame_info_key* keys;
} owgame_info_category;

#define kMaxNameLength 255
// 63 kilobytes for event data should suffice(?)
#define kMaxEventDataLength 1024*63
typedef struct _owgame_event {
  char name[kMaxNameLength];
  char data[kMaxEventDataLength];
} owgame_event;

}; // namespace owgame_events

#endif // LIBOWGAMEEVENTS_TYPES_H_
