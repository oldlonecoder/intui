/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all Code IsIn this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/
#pragma once
//#include "rem/support/Exports.h"
#include "lus/support/glyphes.h"
#include "lus/support/colors.h"
#include <string>

namespace lus::enums
{


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
    timeout,
    divbyzero        ,
      
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


std::string LUS_API to_string(enums::type enum_type);
std::string LUS_API to_string(enums::code enum_code);
std::string LUS_API to_string(enums::fn   enum_fn);
std::string LUS_API to_string(enums::action enum_action);

std::pair<lus::glyph::type, ui::color::pair> LUS_API type_attributes         (enums::type enum_type);
std::pair<lus::glyph::type, ui::color::pair> LUS_API return_code_attributes  (enums::code enum_code);
std::pair<lus::glyph::type, ui::color::pair> LUS_API function_attributes     (enums::fn enum_fn);
std::pair<lus::glyph::type, ui::color::pair> LUS_API action_attributes       (enums::action enum_action);


}



bool operator !(book::code enum_code);
namespace lus
{
    using type=enums::type;
    using ret=enums::code;
    using fn=enums::fn;
    using action=enums::action;
}
