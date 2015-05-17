# game-events-sdk
Overwolf Game Events SDK


- libowgameevents\include - contains the C language include files (relevant for C/CPP developers)
- libowgameevents\lib - contains the per-platform DLL file (libowgameevents.dll) - you'll need this DLL file as part of your deployment
- libowgameevents\csharp - contains the OwGameEventsDllWrapper.cs file, which is a CSharp wrapper (p-invoke) around libowgameevents.dll
- libowgameevents\bin - contains utilities that help the development process:
  - consumer.exe - a consumer application that shows real-time triggered events and info key changes
- libowgameevents\samples - contains CPP and CSharp sample applications and code