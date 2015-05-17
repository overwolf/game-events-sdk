#include "pdll.h"

PDLL::PDLL() :
dll_handle_(nullptr),
ref_count_(0) {
}

PDLL::~PDLL() {
  //force this to be a true uninitialize
  ref_count_ = 1;
  Uninitialize();
}

bool PDLL::Initialize(
  const wchar_t* dll,
  const wchar_t* directory/* = nullptr*/) {

  bool retVal = false;

  //Add one to our internal reference counter
  ref_count_++;

  if (ref_count_ == 1) {
    //we are assuming the name is already set
    if (nullptr != directory) {
      SetDllDirectoryW(directory);
    }

    dll_handle_ = LoadLibraryW(dll);
    retVal = (dll_handle_ != nullptr);
  }

  return retVal;
}

//virtual 
void PDLL::Uninitialize(void) {
  //If we're already completely unintialized, early exit
  if (!ref_count_)
    return;

  //if this is the last time this instance has been unitialized, 
  //then do a full uninitialization
  ref_count_--;

  if (ref_count_ < 1) {
    if (dll_handle_) {
      FreeLibrary(dll_handle_);
      dll_handle_ = nullptr;
    }
  }
}