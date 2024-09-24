//
// Created by oldlonecoder on 24-03-08.
//

#include "intui/lexer/lexer.h"

namespace lus
{



book::code lexer::exec()
{
    book::debug() << " Verify config data:";
    if(!m_config.production)
    {
        book::error() << " config data is empty!";
        return book::code::null_ptr;
    }



    book::debug() << " Now Building the Tokens Reference Table:";
    m_config.production->set_reference_table();
    if(m_config.text.empty() || m_config.production->reference_table().empty())
    {
        book::error() << " config data is empty!";
        return book::code::empty;
    }

    book::debug() << " Here is the ref_table Table Dump:" ;
    m_config.production->dump_reference_table();

    //return book::code::Ok;

    scanner = m_config.text;
    scanner.skip_ws();

    return loop();
}


/*!
 * @brief Virtual loop
 *
 * @return book::code::Code...
 */
book::code lexer::loop()
{
    book::debug() << "Before entering the loop: ";
    book::out() << " scanner position set at (col:" << scanner()-scanner.begin() << "):{" << scanner.mark() << book::fn::endl << "}";
    book::test() << " now entering in the loop:";
    //return book::code::Ok;
    auto Cursor = scanner(); // Save current position.
    while(!scanner.eof() && (state != book::code::eof))
    {
        book::debug() << " lexer::loop [Next Token]: " << scanner.mark();
        lex_token Token{};
        if(!tokenize(m_config.production->scan(scanner())))
        {
            book::debug() << book::fn::function << " token not in table: " << scanner.mark();
            if(!!tokenize_numeric(Token))
            {
                if(scanner.eof() || (state == book::code::eof))
                    return book::code::accepted;
            }
        }

        if(Cursor == scanner())
        {
            book::error() << " loop: no scanning (unhandled yet or bug ;) )" << book::fn::endl << scanner.mark();
            return book::code::rejected;
        }

        Cursor = scanner();
    }

    return book::code::accepted;

}




book::code lexer::tokenize(lex_token Token)
{
    book::debug() << book::fn::function << scanner.mark(); //not scanned yet that's why it doen's have line and col numbers ...yet

    static std::map<lex::type::T, book::code (lexer::*)(lex_token&)> ScanFn = {
        {lex::type::Binary           , &lexer::tokenize_binary_operator},
        {lex::type::Null             , &lexer::tokenize_default},
        {lex::type::Unary            , &lexer::tokenize_unary_operator},
        {lex::type::Punc             , &lexer::tokenize_punctuation},
        {lex::type::Keyword          , &lexer::tokenize_keyword},
        {lex::type::Text             , &lexer::tokenize_string},
        {lex::type::Prefix           , &lexer::tokenize_prefix},
        {lex::type::Postfix          , &lexer::tokenize_postfix},
        {lex::type::LineComment      , &lexer::tokenize_cpp_comment},
        {lex::type::BlocComment      , &lexer::tokenize_comment_bloc}
    };

    book::code r{book::code::rejected};
    for(auto [T, Fn] : ScanFn)
    {
        if(T & Token.sem)
           return (this->*Fn)(Token);
    }
    return r;
}




book::code lexer::tokenize_binary_operator(lex_token &newtoken)
{
    book::debug() << newtoken.details() << scanner.mark();
    (void)tokenize_sign_prefix(newtoken);
    newtoken.token_location = scanner.sync();
    scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    push_token(newtoken); // s'occupera de mettre à jour le token et d'avancer le tscanner. ;)

    return book::code::accepted;
}

book::code lexer::tokenize_default(lex_token &newtoken)
{
    book::debug() << " entering with:" << (newtoken ? newtoken.details() : scanner.mark());

    book::debug() << " test scannumber:";
    // auto r = scanner.scannumber();
    // if(!!r.first)
    // {
    //     newtoken.num_data = new lus::StrScanner::Numeric::details{R.second};
    //     newtoken.token_location = scanner.Sync();
    //     newtoken.token_location.length = newtoken.num_data->Seq.length();
    //     newtoken.token_location.begin  = newtoken.num_data->Seq.begin();
    //     newtoken.token_location.end    = newtoken.num_data->Seq.end();
    //     newtoken.Prim       =lex::type::Number;
    //     newtoken.name       = lex::lexem::Numeric;
    //     state = scanner.Step(static_cast<int32_t>(newtoken.num_data->Seq.length()));
    //     newtoken.numeric_tr();
    //     (*m_config.production) << newtoken;
    //     state = scanner.SkipWS() ? book::code::Eof : book::code::Ok;
    //     book::debug() << "Pushed: " << newtoken.details();
    // }
    //else
    //{
        // auto [Ic,C] = Enums::ReturnCodeAttributes(R.first);
        // book::debug() << " ScanNumber:" << C << Ic << Enums::ToString(R.first);
        // book::debug() << " test scan identifier token:";
    return tokenize_identifier(newtoken);
    //}
   // return book::code::Accepted;
}


book::code lexer::tokenize_unary_operator(lex_token &newtoken)
{
    newtoken.token_location = scanner.sync();
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    book::debug() << newtoken.details();
    push_token(newtoken);
    book::debug() << "pushed: " << newtoken.details();
    return book::code::accepted;
}

book::code lexer::tokenize_punctuation(lex_token &newtoken)
{
    book::debug() << book::fn::function << " sync'ing the scanner:";
    newtoken.token_location = scanner.sync();
    //newtoken.token_location.begin = scanner();
    //newtoken.token_location.end = newtoken.token_location.begin + newtoken.token_location.length-1;
    //newtoken.name    = newtoken.token_location();
    book::debug() << "pushing new [punctuation] token";
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    push_token(newtoken);
    book::debug() << "pushed: " << book::fn::function << newtoken.details();
    return book::code::accepted;
}

book::code lexer::tokenize_keyword(lex_token &newtoken)
{
    book::debug() << " sync'ing the scanner:";
    newtoken.token_location = scanner.sync();
    //newtoken.token_location.begin = scanner();
    //newtoken.token_location.end = newtoken.token_location.begin + newtoken.token_location.length-1;
    //newtoken.name    = newtoken.token_location();
    state = scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    book::debug() << "pushing new [keyword] token";
    push_token(newtoken);
    book::debug() << "pushed: " << newtoken.details();
    return book::code::accepted;
}


book::code lexer::tokenize_string(lex_token &newtoken)
{
    return book::code::ok;
}


book::code lexer::tokenize_identifier(lex_token &newtoken)
{
    book::debug() << scanner(); //scanner.Mark();
    auto i = scanner.scan_identifier();
    if(!i.first) return i.first;


    book::debug() << " Fill newtoken Numeric literal Infos (scanner's LocationData -> newtoken::location_data):";
    newtoken.token_location = scanner.sync();
    newtoken.token_location.length = i.second.length();
    newtoken.token_location.begin = i.second.begin();
    newtoken.token_location.end = i.second.end() - 1;
    newtoken.name    = lex::lexem::Identifier;
    newtoken.prim    =lex::type::Id;
    newtoken.sem     =lex::type::Id|lex::type::Leaf;
    newtoken.flags = { .V = 1 };
    book::debug() << "Pushing New [Identifier] Token";
    (*m_config.production) << newtoken;
    scanner.step(static_cast<int32_t>(newtoken.token_location.length));
    scanner.skip_ws();
    book::debug() << "Pushed: " << newtoken.details();

    return book::code::accepted;
}

book::code lexer::tokenize_sign_prefix(lex_token &newtoken)
{
    book::debug() << book::fn::function << ":";
    if ((newtoken.m != lex::mnemonic::Sub) && (newtoken.m != lex::mnemonic::Add))
    {
        book::out() << " rejected (not subtract or addition operator).";
        return book::code::rejected;
    }
    
    if(!m_config.production->empty())
    {
        auto &token = m_config.production->production_table().back();
        book::out() << "prev: " << token.details(true);
        if((!token.has_type(lex::type::Binary |lex::type::Punc)) || (token.m == lex::mnemonic::ClosePar))
        {
            book::out() << " rejected: previous token is not an operator or a expression-terminating punctuation token";
            return book::code::rejected;
        }
    }

    book::out() << " conditions met for unary prefix sign operator:";
    newtoken.prim =lex::type::Sign;
    newtoken.sem = (newtoken.sem & ~(lex::type::Postfix|lex::type::Binary)) | lex::type::Prefix |lex::type::Unary | lex::type::Operator| lex::type::Sign;
    newtoken.m = lex::mnemonic::Negative;
    newtoken.token_location.length = 1;
    newtoken.token_location.end = newtoken.token_location.begin + 1;
    return book::code::accepted;
}



/*!
 * @brief tokenize prefix operator after verifying that the prefix-operator is well formed and does not break the arithmetic syntax rules
 * @param newtoken
 *
 * @note a * *B;
 * @return book::code::Code
 */
book::code lexer::tokenize_prefix(lex_token &newtoken)
{
    if ((newtoken.m == lex::mnemonic::Decr) || (newtoken.m == lex::mnemonic::Incr) || (newtoken.m == lex::mnemonic::BinaryNot))
    {
        if(production().empty())
        {
            push_token(newtoken);
            return book::code::accepted;
        }
        if((production().back().flags.V) && (!production().back().has_type(lex::type::Operator)))
        {
            newtoken.prim   = lex::type::Postfix;
            newtoken.sem    &= ~lex::type::Prefix |lex::type::Postfix;
            if(newtoken.m   == lex::mnemonic::BinaryNot)
                newtoken.m  = lex::mnemonic::Factorial;
        }
        if(!production().back().flags.V)
            throw book::syntax() << newtoken.details() << ": illegal;";
    }
    push_token(newtoken);
    
    return book::code::accepted;
}




book::code lexer::tokenize_postfix(lex_token &newtoken)
{

    if((production().empty()) || (!production().back().flags.V))
        throw book::syntax() << newtoken.details() << ": Illegal;";

    push_token(newtoken);
    
    return book::code::ok;
}

book::code lexer::tokenize_cpp_comment(lex_token &newtoken)
{
    return book::code::ok;
}

book::code lexer::tokenize_comment_bloc(lex_token &newtoken)
{
    return book::code::ok;
}


book::code lexer::tokenize_numeric(lex_token& newtoken)
{
    auto R = scanner.scan_number();
    if(!!R.first)
    {
        newtoken.num_data = lus::sscan::numeric::details{R.second};
        newtoken.token_location = scanner.sync();
        newtoken.token_location.length = newtoken.num_data.seq.length();
        newtoken.token_location.begin  = newtoken.num_data.seq.begin();
        newtoken.token_location.end    = newtoken.num_data.seq.end();
        newtoken.prim       =lex::type::Number;
        newtoken.name       = lex::lexem::Numeric;
        state = scanner.step(static_cast<int32_t>(newtoken.num_data.seq.length()));
        newtoken.numeric_tr();
        (*m_config.production) << newtoken;
        state = scanner.skip_ws() ? book::code::eof : book::code::ok;
        
        return book::code::accepted;
    }
    return book::code::rejected;
}


/*!
 * @brief
 * @param Token
 *
 * @todo Assign location data here.
 */
void lexer::push_token(lex_token &newtoken)
{
    book::debug() << " Pushing newtoken : " << book::fn::endl  << newtoken.details();

    (*m_config.production) << newtoken;
    
    //scanner.Sync(newtoken.token_location.length);
    book::debug() << "SkipWS: ";
    scanner.skip_ws();
}

lex_token::list& lexer::production()
{
    return m_config.production->ref_table;
}

void lexer::update_token_location(lex_token &newtoken)
{

}




} // lex
