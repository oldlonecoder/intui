//
// Created by oldlonecoder on 14/06/24.
//

#include "lus/book/book.h"




/******************************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                                        *
 *   serge.lussier@oldlonecoder.club                                                      *
 *                                                                                        *
 *                                                                                        *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier)                                                        *
 *   and no one else then not even {copilot, chatgpt, or any other AI calamities}         *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply To the Code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 ******************************************************************************************/

//#pragma once



//std::vector<book> book::books{};
std::mutex book_guard{};

book::section::list book::sections{};
book::section::list::iterator book::current_section{};



bool operator !(book::code c)
{
    return (c != book::code::accepted)&&
           (c != book::code::ok)      &&
           (c != book::code::success) &&
           (c != book::code::done)    &&
           (c != book::code::ready)   &&
           (c != book::code::finish)  &&
           (c != book::code::complete);
}



std::map<book::type, const char*> enums_type_dictionary = {
    {book::type::none,        "none"},
    {book::type::err  ,       "err"},
    {book::type::warning,     "warning"},
    {book::type::fatal,       "fatal"},
    {book::type::except,      "exception"},
    {book::type::message,     "message"},
    {book::type::output,      ""},
    {book::type::debug,       "debug"},
    {book::type::info,        "info"},
    {book::type::comment,     "comment"},
    {book::type::syntax,      "syntax error"},
    {book::type::status,      "status"},
    {book::type::test,        "test"},
    {book::type::interrupted, "interrupted"},
    {book::type::aborted,     "aborted"},
    {book::type::segfault,    "segmentation fault"},
    {book::type::log,         "log"}
};


std::map<book::code, const char*> return_codes_dictionary = {
    {book::code::ok,             "ok"},
    {book::code::accepted,       "accepted"},
    {book::code::success,        "success "},
    {book::code::rejected,       "rejected"},
    {book::code::failed,         "failed"},
    {book::code::empty,          "empty"},
    {book::code::full,           "full"},
    {book::code::notempty,       "not empty"},
    {book::code::implemented,    "implemented"},
    {book::code::notimplemented, "not implemented"},
    {book::code::untested,       "untested"},
    {book::code::eof,            "end of file"},
    {book::code::eos,            "end of stream or string"},
    {book::code::null_ptr,       "null pointer"},
    {book::code::notexist,       "does not exist"},
    {book::code::exist,          "exist"},
    {book::code::unexpected,     "unexpected"},
    {book::code::expected,       "expected"},
    {book::code::blocked,        "blocked"},
    {book::code::locked,         "locked"},
    {book::code::overflow,       "buffer overflow"},
    {book::code::oob,            "out of boundaries"},
    {book::code::reimplement,    "need to be re-implemented in derived instances"},
    {book::code::done,           "done"},
    {book::code::complete,       "completed"},
    {book::code::finish,         "finished"},
    {book::code::undefined,      "undefined"},
    {book::code::ready,          "Ready"},
    {book::code::terminate,      "terminate"},
    {book::code::timeout,        "timeout"},
    {book::code::divbyzero,      "division by zero"},
    {book::code::notvisible,     "not visible"},
};


std::map<book::action, const char*> actions_dictionary= {
    {book::action::enter, "enter"},
    {book::action::leave, "leave"},
    {book::action::begin, "begin"},
    {book::action::end,   "end"},
    {book::action::ci,    "commit"},
    {book::action::continu, "continue"},

};


std::map<book::fn, const char*> functions_dictionary= {

    {book::fn::endl,           "endl"},
    {book::fn::function,       "function"},
    {book::fn::file,           "file"},
    {book::fn::line,           "line"},
    {book::fn::stamp,          "stamp"},
    {book::fn::hour,           "hour"},
    {book::fn::minute,         "minute"},
    {book::fn::seconds,        "seconds"},
    {book::fn::weekday,        "weekday"},
    {book::fn::monthname,      "monthname"},
    {book::fn::dayname,        "dayname"},
    {book::fn::day,            "day"},
    {book::fn::month,          "month"},
    {book::fn::year,           "year"}
};



std::map<book::type, std::pair<lus::glyph::type, lus::ui::color::pair>> types_database={

    {book::type::none,        {lus::glyph::computer,  {lus::ui::color::aquamarine1         , lus::ui::color::reset }}},
    {book::type::err,         {lus::glyph::err1,      {lus::ui::color::red4                , lus::ui::color::reset }}},
    {book::type::warning,     {lus::glyph::warning,   {lus::ui::color::yellow              , lus::ui::color::reset }}},
    {book::type::fatal,       {lus::glyph::dead_head, {lus::ui::color::hotpink4            , lus::ui::color::reset }}},
    {book::type::except,      {lus::glyph::bolt,      {lus::ui::color::skyblue3            , lus::ui::color::reset }}},
    {book::type::message,     {lus::glyph::comment,   {lus::ui::color::green4              , lus::ui::color::reset }}},
    {book::type::output,      {lus::glyph::notepad,   {lus::ui::color::grey39              , lus::ui::color::reset }}},
    {book::type::debug,       {lus::glyph::bug,       {lus::ui::color::pink3               , lus::ui::color::reset }}},
    {book::type::info,        {lus::glyph::info,      {lus::ui::color::lightskyblue4       , lus::ui::color::reset }}},
    {book::type::comment,     {lus::glyph::comment,   {lus::ui::color::grey42              , lus::ui::color::reset }}},
    {book::type::syntax,      {lus::glyph::handwrite, {lus::ui::color::lighcoreateblue     , lus::ui::color::reset }}},
    {book::type::status,      {lus::glyph::admin,     {lus::ui::color::lightcyan3          , lus::ui::color::reset }}},
    {book::type::test,        {lus::glyph::file,      {lus::ui::color::aquamarine3         , lus::ui::color::reset }}},
    {book::type::interrupted, {lus::glyph::circle_x,  {lus::ui::color::khaki3              , lus::ui::color::reset }}},
    {book::type::aborted,     {lus::glyph::stop,      {lus::ui::color::red4                , lus::ui::color::reset }}},
    {book::type::segfault,    {lus::glyph::bomb,      {lus::ui::color::sandybrown          , lus::ui::color::reset }}},
    {book::type::log,         {lus::glyph::log,       {lus::ui::color::orangered1          , lus::ui::color::reset }}}
    //...
};


std::map<book::action      , std::pair<lus::glyph::type, lus::ui::color::pair>> actions_color_db = {
    {book::action::enter   , {lus::glyph::enter        , {lus::ui::color::white               , lus::ui::color::reset}}},
    {book::action::leave   , {lus::glyph::file         , {lus::ui::color::white               , lus::ui::color::reset}}},
    {book::action::begin   , {lus::glyph::chronos      , {lus::ui::color::white               , lus::ui::color::reset}}},
    {book::action::end     , {lus::glyph::dead_head    , {lus::ui::color::white               , lus::ui::color::reset}}},
    {book::action::ci      , {lus::glyph::pencil_dr    , {lus::ui::color::white               , lus::ui::color::reset}}},
    {book::action::continu , {lus::glyph::success      , {lus::ui::color::white               , lus::ui::color::reset}}},
};

std::map<book::code, std::pair<lus::glyph::type, lus::ui::color::pair>> codes_database={
    {book::code::ok,              {lus::glyph::thumb_up,        {lus::ui::color::lime              ,lus::ui::color::reset }}},
    {book::code::accepted,        {lus::glyph::thumb_up,        {lus::ui::color::lime              ,lus::ui::color::reset }}},
    {book::code::success,         {lus::glyph::success,         {lus::ui::color::darkgreen         ,lus::ui::color::reset }}},
    {book::code::rejected,        {lus::glyph::thumb_down,      {lus::ui::color::hotpink4          ,lus::ui::color::reset }}},
    {book::code::failed,          {lus::glyph::poop,            {lus::ui::color::darkgoldenrod     ,lus::ui::color::reset }}},
    {book::code::empty,           {lus::glyph::arrowright,      {lus::ui::color::lighcoreategrey   ,lus::ui::color::reset }}},
    {book::code::full,            {lus::glyph::small_dot,       {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::code::notempty,        {lus::glyph::big_dot,         {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::code::implemented,     {lus::glyph::arrow_head_right,{lus::ui::color::lime              ,lus::ui::color::reset }}},
    {book::code::notimplemented,  {lus::glyph::err1,            {lus::ui::color::orange3           ,lus::ui::color::reset }}},
    {book::code::untested,        {lus::glyph::flag,            {lus::ui::color::yellow            ,lus::ui::color::reset }}},
    {book::code::eof,             {lus::glyph::baseline,        {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::code::eos,             {lus::glyph::baseline,        {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::code::null_ptr,        {lus::glyph::circle_x,        {lus::ui::color::hotpink4          ,lus::ui::color::reset }}},
    {book::code::notexist  ,      {lus::glyph::circle_x ,       {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::code::exist     ,      {lus::glyph::star5 ,          {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::code::unexpected,      {lus::glyph::flag ,           {lus::ui::color::yellow            ,lus::ui::color::reset }}},
    {book::code::expected  ,      {lus::glyph::cat ,            {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::code::blocked   ,      {lus::glyph::unauth ,         {lus::ui::color::indianred3        ,lus::ui::color::reset }}},
    {book::code::locked    ,      {lus::glyph::err3 ,           {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::code::overflow  ,      {lus::glyph::dead_head,       {lus::ui::color::red4              ,lus::ui::color::reset }}},
    {book::code::oob       ,      {lus::glyph::alien,           {lus::ui::color::red4              ,lus::ui::color::reset }}},
    {book::code::reimplement,     {lus::glyph::books,           {lus::ui::color::yellow            ,lus::ui::color::reset }}},
    {book::code::done       ,     {lus::glyph::ok,              {lus::ui::color::yellow            ,lus::ui::color::reset }}},
    {book::code::complete   ,     {lus::glyph::ok,              {lus::ui::color::yellow            ,lus::ui::color::reset }}},
    {book::code::finish     ,     {lus::glyph::ok,              {lus::ui::color::lime              ,lus::ui::color::reset }}},
    {book::code::undefined  ,     {lus::glyph::err3,            {lus::ui::color::red               ,lus::ui::color::reset }}},
    {book::code::ready      ,     {lus::glyph::ok,              {lus::ui::color::lime              ,lus::ui::color::reset }}},
    {book::code::terminate  ,     {lus::glyph::flag,            {lus::ui::color::hotpink4          ,lus::ui::color::reset }}},
    {book::code::timeout    ,     {lus::glyph::chronos,         {lus::ui::color::lime              ,lus::ui::color::reset }}},
    {book::code::divbyzero  ,     {lus::glyph::circle_x,        {lus::ui::color::red4              ,lus::ui::color::reset }}},
    {book::code::notvisible ,     {lus::glyph::circle_x,        {lus::ui::color::yellow            ,lus::ui::color::reset }}},
};


std::map<book::fn, std::pair<lus::glyph::type, lus::ui::color::pair>> functions_database={

    {book::fn::stamp     ,      {lus::glyph::chronos  ,   {lus::ui::color::skyblue3          ,lus::ui::color::reset }}},
    {book::fn::function  ,      {lus::glyph::function ,   {lus::ui::color::skyblue3          ,lus::ui::color::reset }}},
    {book::fn::file      ,      {lus::glyph::file     ,   {lus::ui::color::lightcyan3        ,lus::ui::color::reset }}},
    {book::fn::line      ,      {lus::glyph::baseline ,   {lus::ui::color::lime              ,lus::ui::color::reset }}},
    {book::fn::stamp     ,      {lus::glyph::chronos  ,   {lus::ui::color::yellow            ,lus::ui::color::reset }}},
    {book::fn::hour      ,      {lus::glyph::chronos  ,   {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::fn::minute    ,      {lus::glyph::chronos  ,   {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::fn::seconds   ,      {lus::glyph::chronos  ,   {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::fn::weekday   ,      {lus::glyph::fabric   ,   {lus::ui::color::yellow            ,lus::ui::color::reset }}},
    {book::fn::monthname ,      {lus::glyph::chronos  ,   {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::fn::dayname   ,      {lus::glyph::star5    ,   {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::fn::day       ,      {lus::glyph::star5    ,   {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::fn::month     ,      {lus::glyph::star5    ,   {lus::ui::color::white             ,lus::ui::color::reset }}},
    {book::fn::year      ,      {lus::glyph::star5    ,   {lus::ui::color::white             ,lus::ui::color::reset }}}

};


std::string book::to_string(book::type ty)
{
    return enums_type_dictionary[ty];
}

std::string book::to_string(book::code cod)
{
    return return_codes_dictionary[cod];
}


std::pair<lus::glyph::type, lus::ui::color::pair> book::type_attributes(book::type ty)
{
    return types_database[ty];
}

std::pair<lus::glyph::type, lus::ui::color::pair> book::return_code_attributes(book::code cod)
{
    return codes_database[cod];
}

std::pair<lus::glyph::type, lus::ui::color::pair> book::function_attributes(book::fn fn)
{
    return functions_database[fn];
}

std::pair<lus::glyph::type, lus::ui::color::pair> book::action_attributes(book::action a)
{
    return actions_color_db[a];
}

std::string book::to_string(book::fn fn)
{
    return functions_dictionary[fn];
}

std::string book::to_string(book::action ac)
{
    return actions_dictionary[ac];
}


















book &book::error(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::err, book::code::failed, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::warning(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::warning, book::code::ok, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::fatal(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::fatal, book::code::failed, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::except(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::except, book::code::rejected, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::message(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::message, book::code::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::out(std::source_location src)
{
    book_guard.lock();
    if(book::sections.empty())
    {
        book::init();
        auto& r = **book::current_section << book{book::type::warning, book::code::empty, src};
        r << " using uninitialized book storage -  Initializing with default: 'globals'";
        r << "\r\n";
        book_guard.unlock();
        return r;
    }

    if(!book::current_section->contents.empty())
    {
        //@todo apply encoded newline : either ascii or html
        book::current_section->contents.back().text | "\r\n"; // this way we make sure that we set new line for all oses.
        book_guard.unlock();
        return book::current_section->contents.back();
    }
    auto& r = **book::current_section << book{book::type::output, book::code::empty, src};
    book_guard.unlock();
    return r;
}

book &book::debug(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::debug, book::code::ok, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::info(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::info, book::code::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::comment(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::comment, book::code::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::syntax(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::syntax, book::code::rejected, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::status(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::status, book::code::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::test(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::test, book::code::implemented, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::interrupted(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::interrupted, book::code::rejected, src};
    r.init_header();
    book_guard.unlock();
    return r;
}

book &book::aborted(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::aborted, book::code::rejected, src};
    r.init_header();
    book_guard.unlock();
    return r;
}


book &book::segfault(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::segfault, book::code::blocked, src};
    r.init_header();
    book_guard.unlock();
    return r;
}


book& book::log(std::source_location src)
{
    book_guard.lock();
    auto& r = **book::current_section << book{book::type::log, book::code::blocked, src};
    r.init_header();
    book_guard.unlock();
    return r;

}


book &book::operator<<(const std::string &txt)
{
    text << txt;
    return *this;
}

book &book::operator<<(const char *txt)
{
    text << txt;
    return *this;
}

book &book::operator<<(std::string_view txt)
{
    text << txt;
    return *this;
}

book &book::operator<<(const lus::ui::rectangle &r)
{
    text << r.tostring();
    return *this;
}

book &book::operator<<(lus::ui::cxy pt)
{
    text | std::format("{},{}", pt.x, pt.y);
    return *this;
}

book &book::operator<<(lus::ui::color::code col)
{
    text | col;
    return *this;
}

book &book::operator<<(lus::ui::color::pair fgbg)
{
    text | fgbg();
    return *this;
}

book &book::operator<<(lus::glyph::type gh)
{
    text | gh;
    return *this;
}

book &book::operator<<(book::type ty)
{
    auto [gh,colors] = book::type_attributes(ty);
    text | colors | gh  | book::to_string(ty) | lus::ui::color::reset;
    return *this;
}


book &book::operator<<(lus::accent_fr::type ac)
{
    text | lus::accent_fr::data[ac];
    return *this;
}

void book::init_header()
{
    if(_headercomp_.type)
    {
        auto [gh,colors] = book::type_attributes(_type_);
        text | colors | gh  | ' ' | book::to_string(_type_) | lus::ui::color::reset | ' ';
    }

    if(_headercomp_.file)
    {
        auto [gh, colors] = book::function_attributes(book::fn::file);
        lus::string txt = location.file_name();
        lus::string::word::list words;
        if(auto count = txt.words(words, false, "/"); !count) return ;
        text | lus::ui::color::reset | " in " | colors | gh;
        if(words.size() > 1)
        {
            auto i = words.end();
            i--; // filename 
            auto filename = *i;
            i--; // parent dir
            text | **i;
            ++i;
            text | '/' | **i | ' ';
        }
        words.clear();
    }
    // disable uncontrollable and potentially insane length of function signature given by std::source_location.
    // instead, using it explicitly into a distinct book input
    //------------------------------------------------------------------------------------------------------------
    //    if(headercomp.func)
    //    {
    //        auto [gh, colors] = book::functionattributes(book::fn::function);
    //        text << colors << gh << ' ' << location.function_name() << lus::ui::color::reset;
    //    }
    //------------------------------------------------------------------------------------------------------------
    if(_headercomp_.line)
    {
        auto [gh, colors] = book::function_attributes(book::fn::line);
        text | colors | "line: " | std::format("{}", location.line()) | lus::ui::color::reset;
    }
    text | ' ';
}


book &book::operator<<(char ch)
{
    text | ch;
    return *this;
}

void book::purge(const std::function<void(book &)>& f)
{
    std::cout << " Purge book::sections->contents:\n\r";
    for(auto& [id, contents]: book::sections)
    {
        std::cout << " Section: [" << id << "]:\n\r--------------------------------------------------------\n\r";
        for(auto& r : contents)
        {
            if (f)
                f(r);
            else
                std::cout << r.text() << "\r\n";

            r.text.clear();
        }
        book::sections[0].contents.clear();
    }
}


book &book::operator<<(book::code cod)
{
    auto [gh,colors] = book::return_code_attributes(cod);
    text
        | colors()
        | gh
        | book::to_string(cod)
        | lus::ui::color::reset | ' ';
    return *this;
}

book &book::operator<<(book::fn fn)
{
    switch (fn) {
        case book::fn::endl:
            text | '\n';
//            switch (appbook::format()) ///@todo create book::format(); directly instead.
//            {
//                case color::format::ansi256:
//                    input("\n");
//                    break;
//                case color::format::html:
//                    input("<br />");
//                    break;
//            }
            break;
        case book::fn::stamp: {
            /*
                 * %d %f ou %d %m %y
                 * %r %t %h %m %s
                 * %a {monday} %a {mon}
                 * %b {june}   %b {jun}
            */


            //std::chrono::zoned_time date{"america/toronto", std::chrono::system_clock::now()};
            //const auto tp{std::chrono::system_clock::now()};
            //auto txt{lus::string::now("{:%h:%m:%s}", tp)};
            auto [ic, a] = book::function_attributes(book::fn::stamp);
            lus::string acc;
            acc | a.fg | lus::glyph::data[ic] | lus::ui::color::reset | lus::string::now("%t");
            text | acc();
            return *this;
        }

        case book::fn::file:
            text | location.file_name();
            return *this;
        case book::fn::weekday: {
            auto [ic, a] = book::function_attributes(book::fn::weekday);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | lus::string::now("%a");
            text | acc();
            return *this;
        }

        case book::fn::day : {
            auto [ic, a] = book::function_attributes(book::fn::day);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | lus::string::now("%d");
            text | acc();
            return *this;
        }

        case book::fn::month: {
            auto [ic, a] = book::function_attributes(book::fn::month);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | lus::string::now("%m");
            text | acc();
            return *this;
        }
        case book::fn::monthname: {
            auto [ic, a] = book::function_attributes(book::fn::month);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | lus::string::now("%b");
            text | acc();
            return *this;
        }
        case book::fn::year: {
            auto [ic, a] = book::function_attributes(book::fn::year);
            //auto today{std::chrono::system_clock::now()};
            lus::string acc;
            acc | /*utf::glyph::data[ic] <<*/ a.fg | lus::string::now("%y");
            text | acc();
            return *this;
        }
        case book::fn::function:
            auto [gh, colors] = book::function_attributes(book::fn::function);
            text | "\n[" | colors | location.function_name() | lus::ui::color::reset | "]\n";
            break;

        //default: break;
    }
    return *this;
}


book::exception book::exception::operator[](book& el)
{
    _book_instance_ = &el;
    return *this;
}


book::book(book::type in_type, book::code code, std::source_location src):_type_(in_type), _code_(code), location(std::move(src)){}


const char *book::exception::what() const noexcept
{
    if(_book_instance_)
        return _book_instance_->text().c_str();

    return std::exception::what();
}




book::section &book::select(const std::string& section_id)
{
    if(book::sections.empty())
    {
        book::init();
        book::current_section = book::sections.begin();
        return book::sections[0];
    }
    int count=0;
    for(auto& s : book::sections)
    {
        if(s.id == section_id)
        {
            book::current_section = book::sections.begin() + count;
            return s;
        }
        ++count;
    }
    book::current_section = book::sections.begin();
    return *book::current_section;
}


book::code book::init(std::function<book::code()> inifn)
{
    book::sections.emplace_back(book::section{.id="globals"});
    book::current_section = book::sections.begin();
    if(inifn)
        return inifn();
    return book::code::done;
}

book::code book::append_section(const std::string &section_id)
{
    if(book::select(section_id).id == section_id)
    {
        book::current_section = book::sections.begin();
        book::error() << " section identified by '" << section_id << "' already exists. - request rejected";
        return book::code::rejected;
    }
    book::sections.emplace_back(book::section{.id=section_id});
    book::current_section = book::sections.end();
    --book::current_section;
    return book::code::accepted;
}

book::section &book::section::operator*()
{
    return *this;
}

book &book::section::operator<<(book &&r)
{
    contents.emplace_back(r);
    return contents.back();
}

book &book::operator<<(book::action a_action)
{
    
    return *this;
}
