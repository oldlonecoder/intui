//
// Created by oldlonecoder on 8/21/24.
//

//#ifndef BOOK_H
//#define BOOK_H
/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all Code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/


#pragma once

#include "intui/support/string.h"
//#include "intui/book/enums.h"
#include <source_location>

#include <functional>
#include <intui/support/geometry.h>





class LUS_API book
{
public:
    struct header_component
    {
         integers::U8 type  : 1;
         integers::U8 stamp : 1;
         integers::U8 func  : 1;
         integers::U8 file  : 1;
         integers::U8 line  : 1;
         integers::U8 col   : 1;
       //...
    };


    enum class type : integers::U8{
        none, err, warning, fatal, except, message, output, debug, info, comment, syntax, status, test, interrupted, aborted, segfault, log
    };



    enum class code : integers::U8
    {
        ok  =0           , ///< Obviously;
        accepted         ,
        success          ,
        rejected         ,
        failed           ,
        empty            ,
        full             ,
        notempty         ,
        implemented      , ///< Like notimplemented or already implemented
        notimplemented   , ///< "Please, implement"
        untested         ,
        eof              , ///< End of file
        eos              , ///< End of stream or string or statement or Status ( machine Status )
        null_ptr         , ///< It will happen. Trust me :)
        notexist         , ///< does not exist
        exist            , ///< does already exist
        unexpected       , ///< unexpected
        expected         , ///< expected
        blocked          , ///< thread trying To lock A mutex has failed because the mutex is already locked IsIn another thread...
        locked           , ///< thread trying To lock A mutex has became the owner of the lock.
        overflow         , ///< buffer overflow
        oob              , ///< buffer overflow
        reimplement      ,
        done             ,
        complete         ,
        finish           ,
        undefined        ,
        ready            ,
        terminate        ,
        timeout          ,
        divbyzero        ,
        notvisible       ,

        //...

    };


    enum class fn : integers::U8
    {
        function         ,
        endl             , ///< End of line Code, input format
        file             ,
        line             ,
        stamp            , ///< fully detailed timestamp
        hour             ,
        minute           ,
        seconds          ,
        weekday          ,
        dayname          ,
        monthname        ,
        day              ,
        month            ,
        year
    };

    enum class action : integers::U8
    {
        enter            , ///< enter bloc or indent
        leave            , ///< End (logger: End of entry accumulators, so do commit); End of (sel)Section, STMLAttribute ( auto- color::Reset ) and unindent
        ci               , ///< Commit...
        begin            , ///< Begin (sel)Section or augment indent level
        end              , ///< End   Loop/Action or End selection or Unindent one level
        continu          , ///< Continue Loop or continue Signals::Action iteration.
    };


    static std::string LUS_API to_string(book::type enum_type);
    static std::string LUS_API to_string(book::code enum_code);
    static std::string LUS_API to_string(book::fn   enum_fn);
    static std::string LUS_API to_string(book::action enum_action);

    static std::pair<lus::glyph::type, lus::ui::color::pair> LUS_API type_attributes         (book::type enum_type);
    static std::pair<lus::glyph::type, lus::ui::color::pair> LUS_API return_code_attributes  (book::code enum_code);
    static std::pair<lus::glyph::type, lus::ui::color::pair> LUS_API function_attributes     (book::fn enum_fn);
    static std::pair<lus::glyph::type, lus::ui::color::pair> LUS_API action_attributes       (book::action enum_action);


    



    
    
private:
    book::type _type_{};
    book::code _code_{};
    std::source_location location{};
    // ---------------------------------
    lus::string  text{};

    header_component _headercomp_{1,0,1,1,1};
public:
    static book& error       (std::source_location src = std::source_location::current());
    static book& warning     (std::source_location src = std::source_location::current());
    static book& fatal       (std::source_location src = std::source_location::current());
    static book& except      (std::source_location src = std::source_location::current());
    static book& message     (std::source_location src = std::source_location::current());
    static book& out         (std::source_location src = std::source_location::current());
    static book& debug       (std::source_location src = std::source_location::current());
    static book& info        (std::source_location src = std::source_location::current());
    static book& comment     (std::source_location src = std::source_location::current());
    static book& syntax      (std::source_location src = std::source_location::current());
    static book& status      (std::source_location src = std::source_location::current());
    static book& test        (std::source_location src = std::source_location::current());
    static book& interrupted (std::source_location src = std::source_location::current());
    static book& aborted     (std::source_location src = std::source_location::current());
    static book& segfault    (std::source_location src = std::source_location::current());
    static book& log         (std::source_location src = std::source_location::current());

    book& operator << (const std::string& txt);
    book& operator << (const char* txt);
    book& operator << (char ch);
    book& operator << (std::string_view txt);
    book& operator << (const lus::ui::rectangle& r);
    book& operator << (lus::ui::cxy pt);
    book& operator << (lus::ui::color::code col);
    book& operator << (lus::ui::color::pair fgbg);
    book& operator << (lus::glyph::type gh);
    book& operator << (lus::accent_fr::type ac);
    book& operator << (book::type ty);
    book& operator << (book::code cod);
    book& operator << (book::fn fn);
    book& operator << (book::action a_action);
    template<typename T> book& operator << (const T& v)
    {
        text << v;
        return *this;
    }

private:
    static std::vector<book> _mem_stream_;

    void init_header();
public:
    static void purge(const std::function<void(book &)>& f);

    struct LUS_API section
    {
        std::string id;
        std::vector<book> contents{};
        using list = std::vector<book::section>;
        book::section& operator *();
        book& operator << (book&& r);
    };

private:
    static book::section::list sections;
    static book::section::list::iterator current_section;
public:
    static book::section& select(const std::string& section_id);
    static book::code init(std::function<book::code()> inifn = nullptr);
    static book::code append_section(const std::string& section_id);

    class LUS_API exception :  public std::exception
    {
    public:

        explicit exception():std::exception() { _e_ = true; }
        explicit exception(const char *txt) { _msg_ = txt; _e_ = false; }
        explicit exception(const std::string &txt) { _msg_ = txt; _e_ = false; }

        ~exception() noexcept override {
            _msg_.clear();
        }

        [[nodiscard]] const char *what() const noexcept override;

        book::exception operator[](book& el);
    private:
        bool _e_;
        std::string _msg_;
        book *_book_instance_{nullptr};
    };

    book() = default;
    book(book::type message, book::code code, std::source_location src);
};

 bool operator !(book::code enum_code);

//#endif //BOOK_H
