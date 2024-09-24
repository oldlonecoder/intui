#include "intui/application.h"
#include "intui/io/linux/terminal.h"
#include <csignal>


namespace lus::intui
{

std::shared_ptr<application> application::_app_{nullptr};

void application::sig_interrupted(int)
{
    book::interrupted();
    lus::intui::terminal::end();
    book::purge(nullptr);
}

void application::sig_aborted(int)
{
    book::aborted();
    lus::intui::terminal::end();
    book::purge(nullptr);
}

void application::sig_crash(int)
{
    book::segfault();
    lus::intui::terminal::end();
    book::purge(nullptr);
}

std::shared_ptr<application> application::create(const std::string &app_name, int args, char **argv)
{
    if(application::_app_ != nullptr)
        throw book::exception() [book::except() << book::fn::function << book::fn::endl << " multiple instanciation of application!"];

    std::shared_ptr<application> app{new application(app_name,args,argv)};
    app.swap(application::_app_);
    return application::_app_;
}


std::shared_ptr<application> application::instance()
{
    if(!application::_app_)
        throw book::exception() [book::except() << book::fn::function << book::fn::endl << " no instance of application!"];
    return application::_app_;
}



book::code application::install_signals()
{

    std::signal(SIGSEGV, &application::sig_crash);
    std::signal(SIGABRT, &application::sig_aborted);
    std::signal(SIGINT, &application::sig_interrupted);

    return book::code::done;
}

book::code application::setup()
{
    //...
    book::init();
    install_signals();
    //...
    return book::code::done;
}


}
