/*
  This is a tester that links with the libowgameevents dll and has no 
  information of the internals of the library
*/
#include <owgame_events.h>
#include "pdll.h"
#include <string>
#include <conio.h>

// Kudos to Jorg Brown for this simple and elegant implementation.
//
// - wan 2005-11-16
//
// Starting with Visual C++ 2005, WinNT.h includes ARRAYSIZE.
#define MACRO_ARRAYSIZE(a) \
  ((sizeof(a) / sizeof(*(a))) / \
   static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

using namespace owgame_events;

class OWGameEventsDll : public PDLL {
  DECLARE_FUNCTION4(__stdcall, OWGameEventsErrors, owgame_events_create, owgame_id, unsigned int, owgame_info_category*, owgame_events_handle*)
  DECLARE_FUNCTION5(__stdcall, OWGameEventsErrors, owgame_events_set_info_key, owgame_events_handle, const char*, const char*, unsigned int, const char*)
  DECLARE_FUNCTION2(__stdcall, OWGameEventsErrors, owgame_events_trigger_event, owgame_events_handle, owgame_event*)
  DECLARE_FUNCTION1(__stdcall, OWGameEventsErrors, owgame_events_begin_info_transaction, owgame_events_handle)
  DECLARE_FUNCTION1(__stdcall, OWGameEventsErrors, owgame_events_commit_info_transaction, owgame_events_handle)
  DECLARE_FUNCTION1(__stdcall, OWGameEventsErrors, owgame_events_close, owgame_events_handle)
};

const char kCategoryPlayer[] = "player";
const char kInfoKeyPlayerUsername[] = "username";
const char kInfoKeyPlayerLevel[] = "level";
const char kInfoKeyPlayerXp[] = "xp";

const char kCategoryLocation[] = "location";
const char kInfoKeyLocationLongitude[] = "longitude";
const char kInfoKeyLocationLatitude[] = "latitude";

int main(int argc, const char* argv[]) {
  OWGameEventsDll dll;
  bool loaded = dll.Initialize(L"libowgameevents.dll");
  if (!loaded) {
    return - 1;
  }

  // 1. initialize meta data
  owgame_id id = 1234; // get your owgame_id from %localappdata%\Overwolf\GamesList.[version number].xml
  owgame_events_handle owgameevents; // our one and only handle

  // declare info categories and keys:
  // We'll have one info category: "player"
  // that will contain three info key-values: "username", "level", "xp"
  owgame_info_key player_keys[] = {
    { kInfoKeyPlayerUsername, 1024 },
    { kInfoKeyPlayerLevel, 11 },
    { kInfoKeyPlayerXp, 11 }
  };

  owgame_info_key location_keys[] = {
    { kInfoKeyLocationLongitude, 11 },
    { kInfoKeyLocationLatitude, 11 }
  };

  owgame_info_category categories[] = {
    { kCategoryPlayer, MACRO_ARRAYSIZE(player_keys), player_keys },
    { kCategoryLocation, MACRO_ARRAYSIZE(location_keys), location_keys }
  };

  // create handle
  OWGameEventsErrors err = dll.owgame_events_create(id, 2, categories, &owgameevents);
  
  if (SUC_OK != err) {
    return -1;
  }



  // 2. set info keys without a transaction
  err = dll.owgame_events_set_info_key(
    owgameevents, kCategoryLocation, kInfoKeyLocationLongitude, 10, "-74.000573");
  
  err = dll.owgame_events_set_info_key(
    owgameevents, kCategoryLocation, kInfoKeyLocationLatitude, 9, "40.733291");


  // 3. set info keys in a transaction (more efficient)
  err = dll.owgame_events_begin_info_transaction(owgameevents);

  // stack allocated value
  char convert[12] = { 0 };
  for (int i = 0; i < 10; i++) {
    sprintf_s(convert, 12, "+%d", i);
    err = dll.owgame_events_set_info_key(
      owgameevents, kCategoryPlayer, kInfoKeyPlayerLevel, 2, convert);
  }

  err = dll.owgame_events_set_info_key(
    owgameevents, kCategoryPlayer, kInfoKeyPlayerXp, 3, "101");

  // test passing a heap allocated value
  char* test = new char[9];
  strcpy_s(test, 9, "wolfgang");
  err = dll.owgame_events_set_info_key(
    owgameevents, kCategoryPlayer, kInfoKeyPlayerUsername, 8, test);
  delete[] test;

  // commit
  err = dll.owgame_events_commit_info_transaction(owgameevents);

  printf("Done updating info db - press any key to trigger events...\n");
  _getch();

  // 3. trigger events:
  owgame_event event = {
    "level up",
    "+1"
  };
  
  int level = 1;

  while (level < 20) {
    sprintf_s((char*)event.data, kMaxEventDataLength, "+%d", level++);
    err = dll.owgame_events_trigger_event(owgameevents, &event);
    Sleep(50);
  }

  printf("Done triggering events.\nPress any key to end...");
  _getch();

  // 3. uninitialize
  dll.owgame_events_close(owgameevents);

  return 0;
}