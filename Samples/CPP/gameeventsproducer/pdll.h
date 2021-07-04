//////////////////////////////////////////////////////////////////////////     Class: PDll     
//
// Authors: MicHael Galkovsky // Date: April 14, 1998 
// Company: Pervasive Software 
// Purpose: Base class to wrap dynamic use of dll 
//
// https://msdn.microsoft.com/en-us/library/ms810279.aspx
////////////////////////////////////////////////////////////////////////

#if !defined (_PDLL_H_)
#define PDLLH_

#include <windows.h>
#include <winbase.h>
#include <string>

#define FUNC_LOADED 3456

//function declarations according to the number of parameters
//define the type
//declare a variable of that type
//declare a member function by the same name as the dll function
//check for dll handle
//if this is the first call to the function then try to load it
//if not then if the function was loaded successfully make a call to it
//otherwise return a NULL cast to the return parameter.

#define DECLARE_FUNCTION0(convention, retVal, FuncName) \
public: \
  typedef retVal (convention* TYPE_##FuncName)(); \
  TYPE_##FuncName m_##FuncName; \
  short m_is##FuncName; \
  retVal FuncName() \
     { \
     if (dll_handle_) \
          { \
          if (FUNC_LOADED != m_is##FuncName) \
               {\
               m_##FuncName = NULL; \
               m_##FuncName = (TYPE_##FuncName)GetProcAddress(dll_handle_, #FuncName); \
               m_is##FuncName = FUNC_LOADED;\
               }\
               if (NULL != m_##FuncName) \
               return m_##FuncName(); \
               else \
               return (retVal)NULL; \
          } \
          else \
          return (retVal)NULL; \
     }      

#define DECLARE_FUNCTION1(convention, retVal, FuncName, Param1) \
public: \
  typedef retVal (convention* TYPE_##FuncName)(Param1); \
  TYPE_##FuncName m_##FuncName = NULL; \
  short m_is##FuncName = 0;\
  retVal FuncName(Param1 p1) \
     { \
     if (dll_handle_) \
          { \
          if (FUNC_LOADED != m_is##FuncName) \
               {\
               m_##FuncName = NULL; \
               m_##FuncName = (TYPE_##FuncName)GetProcAddress(dll_handle_, #FuncName); \
               m_is##FuncName = FUNC_LOADED;\
               }\
               if (NULL != m_##FuncName) \
               return m_##FuncName(p1); \
               else \
               return (retVal)NULL; \
          } \
          else \
          return (retVal)NULL; \
     }


// add macros for FUNCTION with 2, 3, 4 params
#define DECLARE_FUNCTION2(convention, retVal, FuncName, Param1, Param2) \
public: \
  typedef retVal (convention* TYPE_##FuncName)(Param1, Param2); \
  TYPE_##FuncName m_##FuncName = NULL; \
  short m_is##FuncName = 0;\
  retVal FuncName(Param1 p1, Param2 p2) \
     { \
     if (dll_handle_) \
          { \
          if (FUNC_LOADED != m_is##FuncName) \
               {\
               m_##FuncName = NULL; \
               m_##FuncName = (TYPE_##FuncName)GetProcAddress(dll_handle_, #FuncName); \
               m_is##FuncName = FUNC_LOADED;\
               }\
               if (NULL != m_##FuncName) \
               return m_##FuncName(p1, p2); \
               else \
               return (retVal)NULL; \
          } \
          else \
          return (retVal)NULL; \
     }

#define DECLARE_FUNCTION3(convention, retVal, FuncName, Param1, Param2, Param3) \
public: \
  typedef retVal (convention* TYPE_##FuncName)(Param1, Param2, Param3); \
  TYPE_##FuncName m_##FuncName = NULL; \
  short m_is##FuncName = 0;\
  retVal FuncName(Param1 p1, Param2 p2, Param3 p3) \
     { \
     if (dll_handle_) \
          { \
          if (FUNC_LOADED != m_is##FuncName) \
               {\
               m_##FuncName = NULL; \
               m_##FuncName = (TYPE_##FuncName)GetProcAddress(dll_handle_, #FuncName); \
               m_is##FuncName = FUNC_LOADED;\
               }\
               if (NULL != m_##FuncName) \
               return m_##FuncName(p1, p2, p3); \
               else \
               return (retVal)NULL; \
          } \
          else \
          return (retVal)NULL; \
     }

#define DECLARE_FUNCTION4(convention, retVal, FuncName, Param1, Param2, Param3, Param4) \
public: \
  typedef retVal (convention* TYPE_##FuncName)(Param1, Param2, Param3, Param4); \
  TYPE_##FuncName m_##FuncName = NULL; \
  short m_is##FuncName = 0;\
  retVal FuncName(Param1 p1, Param2 p2, Param3 p3, Param4 p4) \
     { \
     if (dll_handle_) \
          { \
          if (FUNC_LOADED != m_is##FuncName) \
               {\
               m_##FuncName = NULL; \
               m_##FuncName = (TYPE_##FuncName)GetProcAddress(dll_handle_, #FuncName); \
               m_is##FuncName = FUNC_LOADED;\
               }\
               if (NULL != m_##FuncName) \
               return m_##FuncName(p1, p2, p3, p4); \
               else \
               return (retVal)NULL; \
          } \
          else \
          return (retVal)NULL; \
     }

#define DECLARE_FUNCTION5(convention, retVal, FuncName, Param1, Param2, Param3, Param4, Param5) \
public: \
  typedef retVal (convention* TYPE_##FuncName)(Param1, Param2, Param3, Param4, Param5); \
  TYPE_##FuncName m_##FuncName = NULL; \
  short m_is##FuncName = 0;\
  retVal FuncName(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) \
     { \
     if (dll_handle_) \
          { \
          if (FUNC_LOADED != m_is##FuncName) \
               {\
               m_##FuncName = NULL; \
               m_##FuncName = (TYPE_##FuncName)GetProcAddress(dll_handle_, #FuncName); \
               m_is##FuncName = FUNC_LOADED;\
               }\
               if (NULL != m_##FuncName) \
               return m_##FuncName(p1, p2, p3, p4, p5); \
               else \
               return (retVal)NULL; \
          } \
          else \
          return (retVal)NULL; \
     }

#define DECLARE_FUNCTION6(convention, retVal, FuncName, Param1, Param2, Param3, Param4, Param5, Param6) \
public: \
  typedef retVal (convention* TYPE_##FuncName)(Param1, Param2, Param3, Param4, Param5, Param6); \
  TYPE_##FuncName m_##FuncName = NULL; \
  short m_is##FuncName = 0;\
  retVal FuncName(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) \
     { \
     if (dll_handle_) \
          { \
          if (FUNC_LOADED != m_is##FuncName) \
               {\
               m_##FuncName = NULL; \
               m_##FuncName = (TYPE_##FuncName)GetProcAddress(dll_handle_, #FuncName); \
               m_is##FuncName = FUNC_LOADED;\
               }\
               if (NULL != m_##FuncName) \
               return m_##FuncName(p1, p2, p3, p4, p5, p6); \
               else \
               return (retVal)NULL; \
          } \
          else \
          return (retVal)NULL; \
     }

class PDLL {
public:
  PDLL();
  virtual ~PDLL();

  virtual bool Initialize(
    const wchar_t* dll,
    const wchar_t* directory = nullptr);
  virtual void Uninitialize(void);

protected:
  HINSTANCE dll_handle_;
  int ref_count_;
}; // PDLL

#endif
