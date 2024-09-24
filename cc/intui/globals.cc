

#include "lus/support/colors.h"
#include <sys/epoll.h>
#include <unistd.h>
#include "lus/intui/globals.h"

namespace lus::intui::globals::colors
{

static int _milisec_{-1};

attr_db::themes attr_db::s_data = 
{
    {
        "Default",
        {
            {
                "Widget",
                {
                    {wstate::Active, {ui::color::grey100, ui::color::grey27}},
                    {wstate::Disable, {ui::color::grey30, ui::color::grey35}}, // keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::grey27}},
                    {wstate::Focus, {ui::color::red4, ui::color::grey27}}
                    //...
                }
            },
            {
                "Frame",
                {
                    {wstate::Active, {ui::color::lightcyan3, ui::color::darkblue}},
                    {wstate::Disable, {ui::color::grey30, ui::color::darkblue}}, // keep coherance with widget base
                    {wstate::Normal, {ui::color::grey100, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::greenyellow, ui::color::darkblue}}
                    //...
                }
            },
            {
                "Label",
                {
                    {wstate::Active, {ui::color::indianred, ui::color::blue}},
                    {wstate::Disable, {ui::color::grey19, ui::color::grey35}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::blue}}, // Keep coherance with widget base
                    {wstate::Focus, {ui::color::yellow, ui::color::blue}}
                }
            },
            {
                "Shortkey",
                {
                    {wstate::Active, {ui::color::hotpink4, ui::color::grey27}},
                    {wstate::Disable, {ui::color::grey19, ui::color::grey35}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::grey27}},
                    {wstate::Focus, {ui::color::red4, ui::color::grey27}}
                }
            },
            {
                "Icon",
                {
                    {wstate::Active, {ui::color::blue1, ui::color::grey27}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::grey19, ui::color::grey35}},
                    {wstate::Normal, {ui::color::blue1, ui::color::grey35}},
                    {wstate::Focus, {ui::color::aquamarine3, ui::color::grey27}},
                    {wstate::Success, {ui::color::green5, ui::color::grey27}}
                }
            },
            {
                "Input-Area", // widget::text_input
                {
                    {wstate::Active, {ui::color::white, ui::color::grey30}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::grey39, ui::color::grey35}},
                    {wstate::Normal, {ui::color::grey37, ui::color::grey30}},
                    {wstate::Focus, {ui::color::white, ui::color::grey30}}
                }
            },
            {
                "Input-Field",
                {
                    {wstate::Active, {ui::color::grey70, ui::color::grey27}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::grey39, ui::color::grey35}},
                    {wstate::Normal, {ui::color::grey70, ui::color::grey27}},
                    {wstate::Focus, {ui::color::white, ui::color::grey27}}
                }
            }
        }
    },
    {
        "C64",
        {
            {
                "Widget",
                {
                    {wstate::Active, {ui::color::darkturquoise, ui::color::darkblue}},
                    {wstate::Disable, {ui::color::grey30, ui::color::darkblue}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::red4, ui::color::darkblue}}
                    //...
                }
            },
            {
                "Frame",
                {
                    {wstate::Active, {ui::color::blue4, ui::color::darkblue}},
                    {wstate::Disable, {ui::color::grey30, ui::color::darkblue}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey100, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::greenyellow, ui::color::darkblue}}
                    //...
                }
            },
            {
                "Label",
                {
                    {wstate::Active, {ui::color::lightcyan3, ui::color::darkblue}},
                    {wstate::Disable, {ui::color::grey19, ui::color::grey35}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::darkblue}}, // Keep coherance with widget base
                    {wstate::Focus, {ui::color::yellow, ui::color::darkblue}}
                }
            },
            {
                "Shortkey",
                {
                    {wstate::Active, {ui::color::hotpink4, ui::color::darkblue}},
                    {wstate::Disable, {ui::color::grey19, ui::color::darkblue}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::red4, ui::color::darkblue}}
                }
            },
            {
                "Icon",
                {
                    {wstate::Active, {ui::color::blue1, ui::color::darkblue}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::grey19, ui::color::darkblue}},
                    {wstate::Normal, {ui::color::blue1, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::aquamarine3, ui::color::darkblue}},
                    {wstate::Success, {ui::color::green5, ui::color::darkblue}}
                }
            },
            {
                "Input-Area", // widget::text_input
                {
                    {wstate::Active, {ui::color::white, ui::color::blue}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::grey39, ui::color::blue}},
                    {wstate::Normal, {ui::color::grey37, ui::color::blue}},
                    {wstate::Focus, {ui::color::white, ui::color::blue}}
                }
            },
            {
                "Input-Field",
                {
                    {wstate::Active, {ui::color::lightcyan3, ui::color::blue4}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::blue, ui::color::darkblue}},
                    {wstate::Normal, {ui::color::blue, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::blue, ui::color::darkblue}}
                },

            },
            {
                "Input-Field:Placeholder",
                {
                    {wstate::Active, {ui::color::darkcyan, ui::color::blue4}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::blue, ui::color::darkblue}},
                    {wstate::Normal, {ui::color::blue, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::blue, ui::color::darkblue}}
                },

            }
        }
    },
    {
        "C128",
        {
            {
                "Widget",
                {
                    {wstate::Active, {ui::color::darkseagreen, ui::color::grey15}},
                    {wstate::Disable, {ui::color::grey30, ui::color::grey15}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::grey15}},
                    {wstate::Focus, {ui::color::red4, ui::color::grey15}}
                    //...
                }
            },
            {
                "Frame",
                {
                    {wstate::Active, {ui::color::darkseagreen, ui::color::grey15}},
                    {wstate::Disable, {ui::color::grey30, ui::color::grey15}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::lightcyan3, ui::color::grey15}},
                    {wstate::Focus, {ui::color::greenyellow, ui::color::grey15}}
                    //...
                }
            },
            {
                "Label",
                {
                    {wstate::Active, {ui::color::darkseagreen4, ui::color::grey15}},
                    {wstate::Disable, {ui::color::grey19, ui::color::grey35}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::darkblue}}, // Keep coherance with widget base
                    {wstate::Focus, {ui::color::yellow, ui::color::darkblue}}
                }
            },
            {
                "Shortkey",
                {
                    {wstate::Active, {ui::color::hotpink4, ui::color::darkblue}},
                    {wstate::Disable, {ui::color::grey19, ui::color::darkblue}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::red4, ui::color::darkblue}}
                }
            },
            {
                "Icon",
                {
                    {wstate::Active, {ui::color::blue1, ui::color::darkblue}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::grey19, ui::color::darkblue}},
                    {wstate::Normal, {ui::color::blue1, ui::color::darkblue}},
                    {wstate::Focus, {ui::color::aquamarine3, ui::color::darkblue}},
                    {wstate::Success, {ui::color::green5, ui::color::darkblue}}
                }
            },
            {
                "Input-Area", // widget::text_input
                {
                    {wstate::Active, {ui::color::darkseagreen, ui::color::grey15}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::darkseagreen, ui::color::grey15}},
                    {wstate::Normal, {ui::color::darkseagreen, ui::color::grey15}},
                    {wstate::Focus, {ui::color::darkseagreen, ui::color::grey15}}
                }
            },
            {
                "Input-Field",
                {
                    {wstate::Active, {ui::color::darkseagreen, ui::color::grey11}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::darkseagreen, ui::color::grey15}},
                    {wstate::Normal, {ui::color::darkseagreen, ui::color::grey15}},
                    {wstate::Focus, {ui::color::darkseagreen, ui::color::grey15}}
                }
            },
            {
                "Input-Field:Placeholder",
                {
                    {wstate::Active, {ui::color::grey23, ui::color::grey11}}, // Keep coherance with widget base
                    {wstate::Disable, {ui::color::darkseagreen, ui::color::grey15}},
                    {wstate::Normal, {ui::color::darkseagreen, ui::color::grey15}},
                    {wstate::Focus, {ui::color::darkseagreen, ui::color::grey15}}
                }
            },
            {
                "StatusBar",
                {
                    {wstate::Active, {ui::color::lime, ui::color::grey15}},
                    {wstate::Disable, {ui::color::grey30, ui::color::grey15}}, // Keep coherance with widget base
                    {wstate::Normal, {ui::color::grey70, ui::color::grey15}},
                    {wstate::Focus, {ui::color::red4, ui::color::grey15}}
                    //...
                }
            }
        }
    }
};


attr_db::themes::iterator attr_db::get_theme(std::string_view Tname)
{
    auto it = attr_db::s_data.begin();
    auto it_end = attr_db::s_data.end();
    while (it != it_end)
    {
        if (it->first == Tname) break;
        ++it;
    }
    // ReSharper disable once CppDFALocalValueEscapesFunction
    return it;
}


bool attr_db::end(attr_db::themes::iterator it)
{
    return it == attr_db::s_data.end();
}

attr_db::themes &lus::intui::globals::colors::attr_db::theme()
{
    return attr_db::s_data;
}

}
