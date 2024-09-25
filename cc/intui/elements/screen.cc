#include "intui/elements/screen.h"

namespace lus::ui
{



std::shared_ptr<screen> screen::_screen_{nullptr};

std::shared_ptr<screen> screen::instance()
{
    return screen::_screen_; // ...
}



} // namespace lus::ui

