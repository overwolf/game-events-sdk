# game-events-sdk
Overwolf Game Events SDK

- libowgameevents\include - contains the C language include files (relevant for C/CPP developers)
- libowgameevents\lib - contains the per-platform DLL file (libowgameevents.dll) - you'll need this DLL file as part of your deployment
- libowgameevents\csharp - contains the OwGameEventsDllWrapper.cs file, which is a CSharp wrapper (p-invoke) around libowgameevents.dll
- libowgameevents\bin - contains utilities that help the development process:
  - consumer.exe - a consumer application that shows real-time triggered events and info key changes
- libowgameevents\samples - contains CPP and CSharp sample applications and code

# API basics

1. owgame_events_create - creates an owgame_events_handle object with pre-defined info categories structure
2. owgame_events_set_info_key - update a specific key in the info database
3. owgame_events_trigger_event - trigger a non-persistent events
4. owgame_events_begin_info_transaction - begin an info database transaction (allows updating multiple keys without triggering an update for individual owgame_events_set_info_key calls)
5. owgame_events_commit_info_transaction - commit the info database transaction
6. owgame_events_close - close the owgame_events_handle object
7. owgame_events_turn_on_logger - set a local logging file (good for debugging)

# General guidelines

1. Use owgame_events_set_info_key for persistent game information (across the match/session) - for example: player health or player name
2. Use owgame_events_trigger_event for "volatile" game events (which are only relevant for when they happen)
3. When defining the info_categories structure (see owgame_events_create): it is better to use discrete key-values (as opposed to json values).  This is good for performance (i.e. not having to constantly serialize JSON text blocks) and easier to consume by the Overwolf apps (i.e. not having to parse a JSON and figure out what changed).

For example - if you have a "player_info" category - it is better to declare the following:

  // keys
  owgame_info_key player_keys[] = {
    { "user_name", 1024 },
    { "level", 11 },
    { "xp", 11 }
  };

  // categories
  owgame_info_category categories[] = {
    { "player_info", MACRO_ARRAYSIZE(player_keys), player_keys }
  };
  
  owgame_events_create(id, 1, categories, &owgameevents);


Rather than declaring 1 key ("data") that holds JSON data: { "user_name": "...", "level": 3, "xp": 55 }


# 1.0.0.14

- Internal stability fixes

# 1.0.0.12

- Improve closing/reopening communications channel (internal)

# 1.0.0.7

- Improve producer disconnection detection

# 1.0.0.6

- Memory allocation bug fix

# 1.0.0.5

- Added internal memory pools for better performance

# 1.0.0.4

- Added owgame_events_turn_on_logger for debugging