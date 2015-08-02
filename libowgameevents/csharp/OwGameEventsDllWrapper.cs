using System;
using System.Runtime.InteropServices;

namespace OWGameEvents
{
    public class OwGameEventsDllWrapper {
      #region Consts
      private const string kDllName = "libowgameevents.dll";
      #endregion Consts

      #region Structs

      public struct Key
        {
            public string Name;
            public uint Size;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct OwGameInfoKey
        {
            public IntPtr KeyPtr;
            public uint Size;
        }

        public struct OwGameInfoCategory : IDisposable
        {
            public string Name;
            public uint NumItems;
            public IntPtr Keys;

            public OwGameInfoCategory(string name, Key[] keys)
            {
                CreateGameInfoCategory(name, keys, out this);
            }

            public void Dispose()
            {
                DestroyGameInfoCategory(this);
            }
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct OwGameEvent
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 255)]
            public char[] Name;

            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024 * 63)]
            public char[] Data;

            public void SetName(string i_Name)
            {
                Name = i_Name.PadRight(255, '\0').ToCharArray();
            }

            public void SetData(string i_Data)
            {
                Data = i_Data.PadRight(1024 * 63, '\0').ToCharArray();
            }
        }

        #endregion

      #region Enums
        public enum OWGameEventsErrors {
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
        }
      #endregion Enums

      #region API

        [DllImport(kDllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern OWGameEventsErrors owgame_events_create(uint game_id, uint categories_count, OwGameInfoCategory[] info_categories, ref IntPtr handle);

        [DllImport(kDllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern OWGameEventsErrors owgame_events_set_info_key(IntPtr handle, string category_name, string info_key, uint value_length, string utf8_value);

        [DllImport(kDllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern OWGameEventsErrors owgame_events_trigger_event(IntPtr handle, ref OwGameEvent owEvent);

        [DllImport(kDllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern OWGameEventsErrors owgame_events_begin_info_transaction(IntPtr handle);

        [DllImport(kDllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern OWGameEventsErrors owgame_events_commit_info_transaction(IntPtr handle);

        [DllImport(kDllName, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern OWGameEventsErrors owgame_events_close(IntPtr handle);

        [DllImport(kDllName, CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        public static extern OWGameEventsErrors owgame_events_turn_on_logger(string filename);
      
      #endregion

      #region Marshalling

        private static void CreateGameInfoCategory(string name, Key[] keys, out OwGameInfoCategory category)
        {
            category.Name = name;
            category.NumItems = (uint)keys.Length;
            category.Keys = Marshal.AllocHGlobal(keys.Length * Marshal.SizeOf(typeof(OwGameInfoKey)));
            var ptr = category.Keys;

            for (var i = 0; i < category.NumItems; i++)
            {
                OwGameInfoKey key;
                key.KeyPtr = Marshal.StringToHGlobalAnsi(keys[i].Name);
                key.Size = keys[i].Size;
                Marshal.StructureToPtr(key, ptr, false);
                ptr = new IntPtr(ptr.ToInt32() + Marshal.SizeOf(typeof(OwGameInfoKey)));
            }
        }

        private static void DestroyGameInfoCategory(OwGameInfoCategory keyHolder)
        {
            var ptr = keyHolder.Keys;

            for (var i = 0; i < keyHolder.NumItems; i++)
            {
                var key = (OwGameInfoKey)Marshal.PtrToStructure(ptr, typeof(OwGameInfoKey));
                Marshal.FreeHGlobal(key.KeyPtr);
                ptr = new IntPtr(ptr.ToInt32() + Marshal.SizeOf(typeof(OwGameInfoKey)));
            }

            Marshal.FreeHGlobal(keyHolder.Keys);
        }

        #endregion
    }
}
