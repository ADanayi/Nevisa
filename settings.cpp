#include "settings.h"

Settings::Settings(bool autoUnlock, bool autoOpen, bool autoClose, QString rootAdr) :
  autoUnlock{autoUnlock},
  autoOpen{autoOpen},
  autoClose{autoClose},
  rootAdr{rootAdr}
{

}
