#ifndef WXCOMMON_H
#define WXCOMMON_H

#include <wx/string.h>

inline wxString _U(const char String[]) {
  return wxString(String, wxConvUTF8);
}
inline string _S(wxString s) {
  char buf[s.Length()];
  strcpy(buf, (const char*)s.mb_str(wxConvUTF8) );
  return string(buf);
}

#endif // WXCOMMON_H
