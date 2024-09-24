#include "intui/io/linux/terminal.h"

#include <sys/ioctl.h>
#include <sys/epoll.h>   ///< linux specific input polling
#include <csignal>

//#include "terminal.h"


namespace lus::intui
{


//#pragma region static_private //  persistent termial data

//static int              _millisec_{-1};
static termios          saved_st{}, new_term{};
static ui::color::pair  _colors_{ui::color::white, ui::color::black};
static terminal*        _terminal_{nullptr};
ui::rectangle            terminal::_geometry_ = {};

// #pragma endregion static_private //  persistent termial data


terminal::terminal()
{
    if(_terminal_)
        throw book::exception() [book::except() << " terminal instance alresdy exists!"]; 
        
    _terminal_ = this;
}

terminal::~terminal()
= default;

book::code terminal::begin()
{
    if(auto c = terminal::query_size(); !c)
    {
        //throw rem::exception()[ rem::error() << tux::fn::function << " failed to get the screen geometry. aborted."];
        book::error() << book::code::failed << " to get the screen geometry - there will be no boudaries checks. ";
    }

    tcgetattr(STDIN_FILENO, &saved_st);
    new_term = saved_st;
    //new_screen_st.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | IGNCR | ICRNL | IXON );
    new_term.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | IGNCR | IXON );
    new_term.c_oflag &= ~OPOST;
    new_term.c_cflag |= (CS8);
    new_term.c_cflag &= ~PARENB;
    new_term.c_lflag &= ~(ICANON | ECHO | IEXTEN | TOSTOP | ECHONL);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 1;
    new_term.c_cc[VSTART] = 0;
    new_term.c_cc[VSTOP] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);

    switch_alternate();
    //ConIO::SaveScr();
    //ConIO::CursorON(false);
    book::out() << " console set to raw mode...";
    //SetCursorShape(ConIO::CShapes::BlockBlink);
    ::signal(SIGWINCH, &terminal::resize_signal);
    terminal::cursor_off();
    terminal::instance().start_mouse();
    return book::code::done;
}



book::code terminal::terminal::end()
{
    switch_back();
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_st);
    cursor_on();
    terminal::instance().stop_mouse();
    return book::code::done;
}

book::code terminal::query_size()
{
    winsize win{};
    ioctl(fileno(stdout), TIOCGWINSZ, &win);
    if((!win.ws_col)||(!win.ws_row))
        return book::code::notexist;

    terminal::_geometry_ = ui::rectangle{{0,0}, ui::size{static_cast<int>(win.ws_col), static_cast<int>(win.ws_row)}};
    book::out() << ui::color::yellow << std::format("{:>3d}x{:<3d}",_geometry_.dwh.w,_geometry_.dwh.h);
    return book::code::done;
}



terminal& terminal::instance()
{ 
    if(!_terminal_)
        throw book::exception()[ book::except() << book::fn::function << " request instance of nullptr"];
    return *_terminal_;
}

void terminal::resize_signal(int)
{
    terminal::query_size();
}



/**
 * @brief Activate the screen cursor.
 * 
 */
void terminal::cursor_on()
{
    write(1,"\x1b[?25h",6);
    fflush(stdout);  
}

void terminal::cursor(ui::cxy xy)
{
    std::cout << std::format("\x1b[{:d};{:d}H", xy.y,xy.x);
}

void terminal::mv(globals::direction::type dir, int d)
{
    char ch =dir==globals::direction::right ? 'C': dir==globals::direction::left  ? 'D' : dir==globals::direction::up    ? 'A' : 'B';
    std::cout << "\x1b[" << d << ch;
}


/**
 * @brief Deactivate the screen cursor
 * 
 */
void terminal::cursor_off()
{
    write(1, "\x1b[?25l",6);
    fflush(stdout);
}

/**
 * @brief Saves the screen contents 
 * 
 */
void terminal::switch_alternate()
{
    std::cout << "\x1b[0m\x1b[?1049h" << std::flush;
}


void terminal::switch_back()
{
    std::cout << "\x1b[0m\x1b[?1049l" << std::flush;
}




/*
xterm Mouse Tracking
Code	Effect	Note
CSI ? 1000 h	MTM	Enable Mouse Tracking Mode
CSI ? 1001 h	HMTM	Set Highlight Mouse Tracking Mode
CSI ? 1002 h	BMMTM	Set Button Motion Mouse Tracking Mode
CSI ? 1004 h	WFTM	Enable Window Focus Tracking Mode
CSI ? 1006 h	DMTM	Set Decimal Mouse Tracking Mode
When MTM and DMTM are enabled the terminal will begin reporting mouse events using the CSI < flag ; x ; y M format for key presses and CSI < flag ; x ; y m for key releases. The exception is WFTM which reports focus in using CSI I and focus out using CSI O.

*/
void terminal::start_mouse()
{
    std::cout << CSI << "?" << "1000h";
    std::cout << CSI << "?" << "1003h";
    std::cout << CSI << "?" << "1006h";
    std::cout << CSI << "?" << "1015h";
    fflush(stdout);
}

void terminal::stop_mouse()
{
    std::cout << CSI << "?" << "1000l";
    std::cout << CSI << "?" << "1003l";
    std::cout << CSI << "?" << "1006l";
    std::cout << CSI << "?" << "1015l";
    fflush(stdout);
}


void terminal::clear()
{
    std::cout << "\x1b[2J";
}

}//namspace lus::intui
