//
// Created by oldlonecoder on 24-03-08.
//

/******************************************************************************************
 *   Copyright (C) /.../2024 by Serge Lussier                                             *
 *   lussier.serge@gmail.com                                                              *
 *                                                                                        *
 *   Unless otherwise specified, all code in this project is written                      *
 *   by the author (Serge Lussier)                                                        *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply to the code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 *****************************************************************************************/

#pragma once

#include "intui/lexer/tokens_table.h"
#include "intui/support/sscan.h"

//#ifndef LEXER_LEXER_H
//#define LEXER_LEXER_H

namespace lus
{

class INTUI_API lexer
{
public:

    struct INTUI_API config_data
    {
        std::string_view text{};
        token_table*      production{nullptr};
    };
    config_data& config() { return m_config; }

    lexer() = default;
    virtual ~lexer() = default;

    virtual book::code exec();




protected:
    lus::sscan scanner{};
    virtual book::code loop();
    book::code state{book::code::ok};
    void push_token(lex_token&);


    void update_token_location(lex_token&);
    book::code tokenize(lex_token);

    config_data m_config;

    virtual book::code tokenize_identifier    (lex_token &);
    virtual book::code tokenize_binary_operator(lex_token&);
    virtual book::code tokenize_default       (lex_token&);
    virtual book::code tokenize_unary_operator (lex_token&);
    virtual book::code tokenize_punctuation   (lex_token&);
    virtual book::code tokenize_keyword       (lex_token&);
    virtual book::code tokenize_string        (lex_token&);
    virtual book::code tokenize_sign_prefix    (lex_token&);
    virtual book::code tokenize_prefix        (lex_token&);
    virtual book::code tokenize_postfix       (lex_token&);
    virtual book::code tokenize_cpp_comment    (lex_token&);
    virtual book::code tokenize_comment_bloc   (lex_token&);
    virtual book::code tokenize_numeric       (lex_token&);

    lex_token::list& production();


};

} // lex

//#endif //LEXER_LEXER_H
