//
// Created by oldlonecoder on 24-01-27.
//

#include "intui/lexer/token_data.h"
#include <intui/support/sscan.h>
#include <intui/support/geometry.h>
#include <format>

static std::string_view NullMsg { "No String" };


namespace lus
{



std::map<lus::sscan::numeric::details::size_type, lex::type::T> nummap =
{
    {lus::sscan::numeric::details::size_type::I8  , lex::type::I8  },
    {lus::sscan::numeric::details::size_type::I16 , lex::type::I16 },
    {lus::sscan::numeric::details::size_type::I32 , lex::type::I32 },
    {lus::sscan::numeric::details::size_type::I64 , lex::type::I64 },
    {lus::sscan::numeric::details::size_type::U8  , lex::type::U8  },
    {lus::sscan::numeric::details::size_type::U16 , lex::type::U16 },
    {lus::sscan::numeric::details::size_type::U32 , lex::type::U32 },
    {lus::sscan::numeric::details::size_type::U64 , lex::type::U64 },
    {lus::sscan::numeric::details::size_type::F32 , lex::type::F32 },
    {lus::sscan::numeric::details::size_type::F64 , lex::type::F64 },
    {lus::sscan::numeric::details::size_type::F128, lex::type::F128}
};

std::string_view lex_token::location_data::operator()()
{
    if(!begin) return NullMsg;
    book::debug() << " length: " << length;
    if(!end)
    {
        std::string_view sv(begin);
        length = sv.length();
        return sv;
    }
    return {begin,length ? length : length+1};
}




[[maybe_unused]] std::string lex_token::location_data::position() const
{
    lus::string Txt = "%d,%d";
    return { (Txt << line << column)() };
}

lex_token::location_data &lex_token::location_data::operator=(const lus::sscan::location_data &Data)
{
    line   = Data.line;
    column = Data.col;
    offset = Data.offset;
    return *this;
}


//lex_token::~lex_token(){}

std::string lex_token::semantic_names() const
{
    return lus::lexer_component::type_name(sem);
}


std::string lex_token::type_name() const
{
    return lus::lexer_component::type_name(prim);
}


std::string lex_token::details(bool Frame) const
{
    lus::string Out;
    auto T = text();
    Out | std::format("{:>4d},{:<4d}", token_location.column, token_location.line) |
        ui::color::reset | "[" |
        ui::color::yellow | std::format("{:<20s}",name) |
        ui::color::reset | "] Primary Type:" |
        ui::color::deepskyblue7 | std::format("{:<12s}", lexer_component::type_name(prim)) |
        ui::color::reset | "{" |
        ui::color::turquoise4 | std::format("{:<32s}",lexer_component::type_name(sem)) |
        ui::color::reset | "}" | "text: " | ui::color::yellow |  std::string(T.begin(), T.end()) | ui::color::reset;

    return Out();
}


std::string lex_token::mark(bool a_colorize) const
{
    // 1 - Locate Beginning of the line:
    lus::string Str;
    // auto LBegin = token_location.begin;
    // auto LEnd   = token_location.end;
    // // Beginning of the line:
    // while((LBegin > token_location.begin) && (*LBegin != '\n') && (*LBegin != '\r')) --LBegin;
    // if(LBegin < token_location.begin) LBegin = token_location.begin;
    // // m_end of line:
    // while((LEnd < token_location.end) && (*LEnd != '\n') && (*LEnd != '\r')) ++LEnd;
    // if(LEnd > token_location.end) LEnd = token_location.end;
    // auto spc = std::string(token_location.column-1<=0? 0 : token_location.column-1, ' ');
    // //Book::Debug() << ":---> nbspace: " << spc.length() << ":";
    // Str , '\n' , std::string(LBegin, LEnd+1) , '\n' , spc , lus::glyph::c_arrow_up;
    return Str();
}


void lex_token::numeric_tr()
{
    if(num_data.seq.empty())
        throw book::exception()[ book::error() << " Cannot call lex_token::numeric_tr on un-scanned or non-numeric token." ];
    sem = lex::type::Number | lex::type::Const | nummap[num_data.size] | lex::type::Leaf;
}


} // lex
