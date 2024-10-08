#include "intui/book/book.h"
#include "intui/support/sscan.h"
//#include "intui/lexer/lexer.h"
//#include "intui/est/alu.h"
#include "intui/est/expression.h"
#include "intui/elements/element.h"
#include "intui/io/linux/terminal.h"
#include "intui/events.h"
#include "intui/application.h"




namespace lus::intui
{

class my_app : public application
{

    
protected:
    book::code setup() override;
};

}

using namespace lus;

void test_element()
{
    try{
        ui::element* widget = new ui::element(nullptr,"elementary");
        widget->set_theme("C128");
        //widget->set_geometry(lus::intui::terminal::geometry());
        widget->set_geometry({{1,1}, ui::size{40,5}});
        auto painter = widget->begin_paint({});
        painter.clear();
        painter << "42";
        //...

        widget->end_paint(painter);
        widget->update();
        intui::event ev{};
        intui::event::get_stdin_event(ev,-1);

        delete widget;
    }
    catch(book::exception& e)
    {
        std::cout << "book::exception: " << e.what();
    }
}


book::code expression()
{

    lus::est::expr e("est - Expression Syntax Tree");
    e = "a = 0.02 / ( 0.02 - 42);";
    //lus::est::alu aa =e.exec("a = 0.02 / ( 0.02 - 42);");
    lus::est::alu val =e.exec( );
    book::out() << lus::ui::color::reset << '\''
                << lus::ui::color::dodgerblue3 << e.id()
                << lus::ui::color::reset << "': est::alu "
                << lus::ui::color::yellow << "val="
                << lus::ui::color::lime <<  val()
                << lus::ui::color::reset;

    return book::code::ok;
}





int main()
{
    book::init();
    lus::intui::terminal terminal{};


    lus::string str = 42;
    std::cout << static_cast<std::string>(str) << std::endl;

    lus::string words = "/Hello/World!/main.cc";
    book::log() << book::fn::function << " lus::string::Words :\"" << static_cast<std::string>(words) << "\" => ";

    auto list = lus::string::word::list{};
    auto count = words.words(list,false,"/");
    book::out() << lus::ui::color::grey100 << "-------------------------" << lus::ui::color::reset;

    if(count)
        for(auto w : list)
            book::out() << lus::ui::color::lime << *w << lus::ui::color::reset;

    book::out() << lus::ui::color::grey100 << "-------------------------" << lus::ui::color::reset;
    list.clear();



    lus::string output;
    output | lus::ui::color::pair{lus::ui::color::blue, lus::ui::color::grey11} | " Hello, World! " | lus::ui::color::reset;
    std::cout << output() << std::endl;

    lus::sscan sscan;
    sscan = " 42.042";
    sscan.skip_ws();
    auto [r, ndata] = sscan.scan_number();
    if(!!r)
        book::out() << lus::ui::color::grey100 << "sscan.scan_number() returns: " << lus::ui::color::chartreuse6 <<  ndata.value << lus::ui::color::reset;

    sscan = " function()    qwoeriu";
    sscan.skip_ws();
    auto [res,iden] = sscan.scan_identifier();
    if(!!res)
        book::out() << lus::ui::color::grey100 << "sscan.scan_identifier() returns: " << lus::ui::color::chartreuse6 <<  iden << lus::ui::color::reset;

    book::log() << " expr:"    ;
    if(r = expression(); !r) 
       book::error() << r;
    else
       book::status() << book::code::success ;

    terminal.begin();
    
    //lus::intui::event event{};
    // book::code C{book::code::ok};

    // while(C != book::code::terminate)
    // {
    //     C = lus::intui::event::get_stdin_event(event,-1);
    //     if(event.event_type == lus::intui::event::type::MOUSE)
    //     {
    //         lus::intui::terminal::cursor({1,1});
    //         std::cout << event.data.mev.to_string();
    //         fflush(stdout);
    //     }
    // }
    test_element();
    terminal.stop_mouse();
    terminal.end();
    //element();
    book::purge(nullptr);

    return 0;
}
