//
// Created by oldlonecoder on 8/19/24.
//




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



#include "lus/est/expression.h"



namespace lus::est 
{


expr::expr(const std::string& _id_):est::bloc(nullptr,_id_, nullptr,nullptr){}


lus::est::expr::~expr()
{
    _token_table_.production_table().clear();
}


expr& expr::operator=(std::string_view expr_text)
{
    if(!_src_.empty() || !_token_table_.production_table().empty()) clear();
    _src_ = expr_text;
    return *this;
}


book::code expr::compile()
{
    try
    {
        if(auto r = lex(); !r) return r;

        //book::info() << book::fn::function << book::fn::endl << " Entering parse tokens:";
        _root_ = {nullptr};
        book::test() << book::fn::function;
        book::out() << " testing node tree_begin(lex_token*) with valgrind leak and wr errors:";
        if(_token_table_.production_table().empty())
        {
            book::status() << " the production tokens is empty. Leaving ";
            return book::code::empty;
        }
        // auto& token = *_token_table_.production_table().begin();
        // auto* ins = node::tree_begin(this,&token, [this](lex_token* a_token) -> node*{
        //     return make_node(a_token);
        // });
        node* tmp{nullptr};
        for(auto& token: _token_table_.production_table())
        {
            if(!_root_) 
            {   
                _root_ = node::tree_begin(this,&token, [this](lex_token* a_token)->node* {
                    return make_node(a_token);
                });

                if(!_root_) return book::code::rejected;
                tmp = _root_;
                continue;
            }
            
            if(tmp) // true, prevent potential crash here...
                tmp = tmp->tree_input(this, &token, [this](lex_token* a_token)->node* {
                    return make_node(a_token);
                });

            if(!tmp)
                break;
            _root_ = tmp;
        }
        _root_  = _root_->close_tree();
        return book::code::success;
    }catch(book::exception& e){
        std::cerr << "a book::exception was thrown during the execution of the lexer. Descriptions are available after the book::purge(...) call." << std::endl;
    }catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }

    return book::code::ok;
}



book::code expr::lex()
{
    _lexer_.config() =
    {
        .text = _src_,               // Yes the arithmetic expr is held into object::id()
        .production = &_token_table_
    };

    try
    {
        auto r = _lexer_.exec();
        auto [ic,a] = book::return_code_attributes(r);
        book::status() << "lexer returns: " << a << ic  << book::to_string(r) << ui::color::reset << " -> ";
        _token_table_.dump_production_table();    /* code */
    }
    catch(const std::exception& e)
    {
        std::cerr << "a book::exception was thrown during the execution of the lexer. Descriptions are available after the book::purge(...) call." << std::endl;
        return book::code::rejected;
    }
    
    return book::code::accepted;
    
}



node *expr::make_node(lex_token *a_token)
{
    book::debug() << book::fn::function << book::fn::endl << " token:" << a_token->text();

    if(a_token->has_type(lex::type::Id))
    {
        book::out() << "handling identifier '" << ui::color::yellow << a_token->text() << ui::color::reset << "' :";
        variable* lvar = new variable(this, a_token,nullptr);
        variable* v = query_variable(a_token);
        if(v)
        {
            lvar->mem.acc = 1;
            lvar->_a_ = v->_a_;
            lvar->mem.ref = 1;
            return lvar;
        }
        add_local_variable(lvar);
        return lvar;
    }
    return new est::node(this,a_token);
    
}

alu expr::exec(std::string_view _text_)
{
    if(!_text_.empty() && _src_.empty())
        _src_ = _text_;

    if(auto r = compile(); !r) return {};
    if(_root_) 
        *_a_ = _root_->JSR();
    return *_a_;

}


book::code expr::clear()
{
    if(_src_.empty()) return book::code::rejected;
    _token_table_.production_table().clear(); // duh...
    return book::code::accepted;
}
} // est
