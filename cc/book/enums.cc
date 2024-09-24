
#include "intui/book/enums.h"
#include <source_location>
#include <map>


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

namespace lus
{


std::map<enums::type, const char*> enums_type_dictionary = {
    {enums::type::none,        "none"},
    {enums::type::err  ,       "err"},
    {enums::type::warning,     "warning"},
    {enums::type::fatal,       "fatal"},
    {enums::type::except,      "exception"},
    {enums::type::message,     "message"},
    {enums::type::output,      ""},
    {enums::type::debug,       "debug"},
    {enums::type::info,        "info"},
    {enums::type::comment,     "comment"},
    {enums::type::syntax,      "syntax error"},
    {enums::type::status,      "status"},
    {enums::type::test,        "test"},
    {enums::type::interrupted, "interrupted"},
    {enums::type::aborted,     "aborted"},
    {enums::type::segfault,    "segmentation fault"},
    {enums::type::log,         "log"}
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
};


std::map<lus::action, const char*> actions_dictionary= {
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



std::map<lus::type, std::pair<lus::glyph::type, ui::color::pair>> types_database={

    {lus::type::none,        {lus::glyph::computer,  {ui::color::aquamarine1         , ui::color::reset }}},
    {lus::type::err,         {lus::glyph::err1,      {ui::color::red4                , ui::color::reset }}},
    {lus::type::warning,     {lus::glyph::warning,   {ui::color::yellow              , ui::color::reset }}},
    {lus::type::fatal,       {lus::glyph::dead_head, {ui::color::hotpink4            , ui::color::reset }}},
    {lus::type::except,      {lus::glyph::bolt,      {ui::color::skyblue3            , ui::color::reset }}},
    {lus::type::message,     {lus::glyph::comment,   {ui::color::green4              , ui::color::reset }}},
    {lus::type::output,      {lus::glyph::notepad,   {ui::color::grey39              , ui::color::reset }}},
    {lus::type::debug,       {lus::glyph::bug,       {ui::color::pink3               , ui::color::reset }}},
    {lus::type::info,        {lus::glyph::info,      {ui::color::lightskyblue4       , ui::color::reset }}},
    {lus::type::comment,     {lus::glyph::comment,   {ui::color::grey42              , ui::color::reset }}},
    {lus::type::syntax,      {lus::glyph::handwrite, {ui::color::lighcoreateblue     , ui::color::reset }}},
    {lus::type::status,      {lus::glyph::admin,     {ui::color::lightcyan3          , ui::color::reset }}},
    {lus::type::test,        {lus::glyph::file,      {ui::color::aquamarine3         , ui::color::reset }}},
    {lus::type::interrupted, {lus::glyph::circle_x,  {ui::color::khaki3              , ui::color::reset }}},
    {lus::type::aborted,     {lus::glyph::stop,      {ui::color::red4                , ui::color::reset }}},
    {lus::type::segfault,    {lus::glyph::bomb,      {ui::color::sandybrown          , ui::color::reset }}},
    {lus::type::log,         {lus::glyph::log,       {ui::color::orangered1          , ui::color::reset }}}
    //...
};


std::map<lus::action      , std::pair<lus::glyph::type, ui::color::pair>> actions_color_db = {
    {lus::action::enter   , {lus::glyph::enter        , {ui::color::white               , ui::color::reset}}},
    {lus::action::leave   , {lus::glyph::file         , {ui::color::white               , ui::color::reset}}},
    {lus::action::begin   , {lus::glyph::chronos      , {ui::color::white               , ui::color::reset}}},
    {lus::action::end     , {lus::glyph::dead_head    , {ui::color::white               , ui::color::reset}}},
    {lus::action::ci      , {lus::glyph::pencil_dr    , {ui::color::white               , ui::color::reset}}},
    {lus::action::continu , {lus::glyph::success      , {ui::color::white               , ui::color::reset}}},
};

std::map<book::code, std::pair<lus::glyph::type, ui::color::pair>> codes_database={
    {book::code::ok,              {lus::glyph::thumb_up,        {ui::color::lime              ,ui::color::reset }}},
    {book::code::accepted,        {lus::glyph::thumb_up,        {ui::color::lime              ,ui::color::reset }}},
    {book::code::success,         {lus::glyph::success,         {ui::color::darkgreen         ,ui::color::reset }}},
    {book::code::rejected,        {lus::glyph::thumb_down,      {ui::color::hotpink4          ,ui::color::reset }}},
    {book::code::failed,          {lus::glyph::poop,            {ui::color::darkgoldenrod     ,ui::color::reset }}},
    {book::code::empty,           {lus::glyph::arrowright,      {ui::color::lighcoreategrey   ,ui::color::reset }}},
    {book::code::full,            {lus::glyph::small_dot,       {ui::color::white             ,ui::color::reset }}},
    {book::code::notempty,        {lus::glyph::big_dot,         {ui::color::white             ,ui::color::reset }}},
    {book::code::implemented,     {lus::glyph::arrow_head_right,{ui::color::lime              ,ui::color::reset }}},
    {book::code::notimplemented,  {lus::glyph::err1,            {ui::color::orange3           ,ui::color::reset }}},
    {book::code::untested,        {lus::glyph::flag,            {ui::color::yellow            ,ui::color::reset }}},
    {book::code::eof,             {lus::glyph::baseline,        {ui::color::white             ,ui::color::reset }}},
    {book::code::eos,             {lus::glyph::baseline,        {ui::color::white             ,ui::color::reset }}},
    {book::code::null_ptr,        {lus::glyph::circle_x,        {ui::color::hotpink4          ,ui::color::reset }}},
    {book::code::notexist  ,      {lus::glyph::circle_x ,       {ui::color::white             ,ui::color::reset }}},
    {book::code::exist     ,      {lus::glyph::star5 ,          {ui::color::white             ,ui::color::reset }}},
    {book::code::unexpected,      {lus::glyph::flag ,           {ui::color::yellow            ,ui::color::reset }}},
    {book::code::expected  ,      {lus::glyph::cat ,            {ui::color::white             ,ui::color::reset }}},
    {book::code::blocked   ,      {lus::glyph::unauth ,         {ui::color::indianred3        ,ui::color::reset }}},
    {book::code::locked    ,      {lus::glyph::err3 ,           {ui::color::white             ,ui::color::reset }}},
    {book::code::overflow  ,      {lus::glyph::dead_head,       {ui::color::red4              ,ui::color::reset }}},
    {book::code::oob       ,      {lus::glyph::alien,           {ui::color::red4              ,ui::color::reset }}},
    {book::code::reimplement,     {lus::glyph::books,           {ui::color::yellow            ,ui::color::reset }}},
    {book::code::done       ,     {lus::glyph::ok,              {ui::color::yellow            ,ui::color::reset }}},
    {book::code::complete   ,     {lus::glyph::ok,              {ui::color::yellow            ,ui::color::reset }}},
    {book::code::finish     ,     {lus::glyph::ok,              {ui::color::lime              ,ui::color::reset }}},
    {book::code::undefined  ,     {lus::glyph::err3,            {ui::color::red               ,ui::color::reset }}},
    {book::code::ready      ,     {lus::glyph::ok,              {ui::color::lime              ,ui::color::reset }}},
    {book::code::terminate  ,     {lus::glyph::flag,            {ui::color::hotpink4          ,ui::color::reset }}},
    {book::code::timeout    ,     {lus::glyph::chronos,         {ui::color::lime              ,ui::color::reset }}},
    {book::code::divbyzero  ,     {lus::glyph::circle_x,        {ui::color::red4              ,ui::color::reset }}},
};


std::map<book::fn, std::pair<lus::glyph::type, ui::color::pair>> functions_database={

    {book::fn::stamp     ,      {lus::glyph::chronos  ,   {ui::color::skyblue3          ,ui::color::reset }}},
    {book::fn::function  ,      {lus::glyph::function ,   {ui::color::skyblue3          ,ui::color::reset }}},
    {book::fn::file      ,      {lus::glyph::file     ,   {ui::color::lightcyan3        ,ui::color::reset }}},
    {book::fn::line      ,      {lus::glyph::baseline ,   {ui::color::lime              ,ui::color::reset }}},
    {book::fn::stamp     ,      {lus::glyph::chronos  ,   {ui::color::yellow            ,ui::color::reset }}},
    {book::fn::hour      ,      {lus::glyph::chronos  ,   {ui::color::white             ,ui::color::reset }}},
    {book::fn::minute    ,      {lus::glyph::chronos  ,   {ui::color::white             ,ui::color::reset }}},
    {book::fn::seconds   ,      {lus::glyph::chronos  ,   {ui::color::white             ,ui::color::reset }}},
    {book::fn::weekday   ,      {lus::glyph::fabric   ,   {ui::color::yellow            ,ui::color::reset }}},
    {book::fn::monthname ,      {lus::glyph::chronos  ,   {ui::color::white             ,ui::color::reset }}},
    {book::fn::dayname   ,      {lus::glyph::star5    ,   {ui::color::white             ,ui::color::reset }}},
    {book::fn::day       ,      {lus::glyph::star5    ,   {ui::color::white             ,ui::color::reset }}},
    {book::fn::month     ,      {lus::glyph::star5    ,   {ui::color::white             ,ui::color::reset }}},
    {book::fn::year      ,      {lus::glyph::star5    ,   {ui::color::white             ,ui::color::reset }}}

};

}

namespace lus
{
std::string enums::to_string(enums::type ty)
{
    return enums_type_dictionary[ty];
}

std::string enums::to_string(enums::code cod)
{
    return return_codes_dictionary[cod];
}


std::pair<lus::glyph::type, ui::color::pair> enums::type_attributes(enums::type ty)
{
    return types_database[ty];
}

std::pair<lus::glyph::type, ui::color::pair> enums::return_code_attributes(enums::code cod)
{
    return codes_database[cod];
}

std::pair<lus::glyph::type, ui::color::pair> enums::function_attributes(enums::fn fn)
{
    return functions_database[fn];
}

std::pair<lus::glyph::type, ui::color::pair> enums::action_attributes(enums::action a)
{
    return actions_color_db[a];
}

std::string enums::to_string(enums::fn fn)
{
    return functions_dictionary[fn];
}

std::string enums::to_string(enums::action ac)
{
    return actions_dictionary[ac];
}

}
