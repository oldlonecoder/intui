//
// Created by oldlonecoder on 8/21/24.
//

#include "lus/support/ansi_32.h"
#include "lus/support/string.h"
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
#include "lus/support/ansi_32.h"
#include "lus/book/book.h"



namespace lus
{

#pragma region ansi32

[[maybe_unused]] ansi32::ansi32(U32 Ch) : chr(Ch){}

ansi32::ansi32(ansi32* C): chr(C->chr){}

ansi32 &ansi32::set_fg(ui::color::code fg)
{
    chr = (chr & ~FGMask) | (static_cast<integers::U8>(fg) << FGShift);
    return *this;
}


ansi32 &ansi32::set_bg(ui::color::code bg)
{
    chr = (chr & ~BGMask) | (static_cast<integers::U8>(bg) << BGShift);
    return *this;
}

[[maybe_unused]] ansi32 &ansi32::set_attributes(U32 d)
{
    chr = (chr & ~AttrMask) | d;
    return *this;
}


[[maybe_unused]] ansi32 &ansi32::set_colors(ui::color::pair &&CP)
{
    return set_fg(CP.fg).set_bg(CP.bg);
}

[[maybe_unused]] ansi32 &ansi32::set_colors(ui::color::pair &CP)
{
    return set_fg(CP.fg).set_bg(CP.bg);
}

ansi32 &ansi32::operator=(U32 Ch)
{
    chr = Ch;
    return *this;
}

ansi32 &ansi32::operator=(U32* Ch)
{
    chr = *Ch;
    return *this;
}


std::string ansi32::get_utf_string() const
{
    if(chr & UTFBITS)
    {
        switch(chr&UTFBITS)
        {
            case UGlyph:
                return  lus::glyph::data[icon_id()];
            case Accent:
                return  lus::accent_fr::data[accent_id()];
            break;
            // case Frame:
            //     return ui::cadre()[frame_id()];
            break;
            default: break;
                //throw rem::exception() [rem::fatal() << " Memory corruption into screen::ansi32 data!"];
        }
    }
    std::string d;
    d+= ascii();
    return d;
}


ansi32 &ansi32::operator=(char Ch)
{
    chr = (chr & (CMask|Underline|Stroke|Blink|TRGB))  | ASCII | Ch;
    return *this;
}

ui::color::code ansi32::foreground() const
{
    return static_cast<ui::color::code>((chr & FGMask) >> FGShift);
}

ui::color::code ansi32::background() const
{
    return static_cast<ui::color::code>((chr & BGMask) >> BGShift);
}

[[maybe_unused]] ui::color::pair ansi32::colors() const
{
    return {foreground(),background()};
}

[[maybe_unused]] lus::glyph::type ansi32::icon_id() const
{
    if (!(chr & ansi32::UGlyph))
        throw book::exception() [ book::except() << book::code::rejected << "attempt to use this ansi32 cell as a glyph which is not,"];

    auto Ic = chr & ansi32::CharMask;
    if (Ic > lus::glyph::log)
        throw book::exception()[book::except() << book::fn::function << book::code::oob << ':' << Ic];
    return  Ic;
}


[[maybe_unused]] lus::accent_fr::type ansi32::accent_id() const
{
    auto AID = chr & ansi32::CharMask;
    if (AID > lus::accent_fr::Ucirc)
         throw book::exception()[book::fatal() << book::fn::function << book::code::oob << ':' << AID];

    return static_cast<lus::accent_fr::type>(AID);
}




ui::cadre::index ansi32::frame_id() const
{
    auto c = chr & 0xff;
    if(c > 11)
        throw book::exception() [book::except() << book::code::oob << book::fn::function << " invalid frame index: " << ui::color::red4 << c];

    return static_cast<ui::cadre::index>(chr & 0xFF);
}

char ansi32::ascii() const
{
    return static_cast<char>(chr & CharMask);
}

[[maybe_unused]] uint16_t ansi32::attributes() const
{
    return (chr & AttrMask) >> ATShift;
}

ansi32 &ansi32::operator<<(lus::glyph::type i_)
{
    chr = (chr & ~(UtfMask|CharMask)) | UGlyph | i_;
    //Rem::Debug() << "Glyph: %s" << lus::Glyph::Data[i_];
    return *this;
}


ansi32 &ansi32::operator<<(lus::accent_fr::type a_)
{
    chr = (chr& ~(AttrMask|CharMask)) | (chr & (Underline|Stroke|Blink)) | Accent | a_;
    return *this;
}


ansi32& ansi32::operator<<(ui::cadre::index fr)
{
    chr = (chr & ~(UtfMask|CharMask|Frame)) | Frame | fr;
    return *this;
}


// ansi32& ansi32::operator<<(ui::cadre::index F)
// {
//     //Rem::Debug() << " Frame ID[%d] : '%s'." << F << ui::cadre()[F];
//     chr = (chr & ~(UtfMask|CharMask)) | (F&0xFF) | Frame;
//     return *this;
// }

ansi32& ansi32::operator<<(ui::color::pair CP)
{
    set_colors(CP);
    return *this;
}


ansi32& ansi32::operator<<(char Ch)
{
    *this = (chr & ~(UTFBITS|CharMask)) | (chr & (Underline|Stroke|Blink)) | ASCII | Ch;
    return *this;
}


[[maybe_unused]] std::string ansi32::render_colors() const
{
    std::string str;
    str += ui::color::render({background(),foreground()});
    return str;
}

//[[maybe_unused]] ansi32 &ansi32::ResetAttributes(ansi32::Type bits_)
//{
//    chr &= ~bits_;
//    return *this;
//}

ansi32::operator std::string() const
{
    return details();
}




std::string ansi32::render(const ansi32::string& _string)
{
    ui::color::pair _cp = _string[0].colors();
    std::string _o = _cp();
    for(auto ch : _string)
    {
        auto cc = ch.colors();
        if(_cp.bg != cc.bg)
        {
            _o += ui::color::render_background(_cp.bg);
            if(_cp.fg != cc.fg)
                _o += ui::color::render(_cp.fg);
            _cp = cc;
        }
        if(ch.chr& ansi32::UTFBITS)
        {
            if(ch.chr & ansi32::Frame)
                _o += ui::cadre()[ch.frame_id()];
            else
                if(ch.chr & ansi32::Accent)
                    _o += lus::accent_fr::data[ch.accent_id()];
                else 
                    if(ch.chr & ansi32::UGlyph)
                        _o += lus::glyph::data[ch.icon_id()];
        }   
    }
    return _o;
}

std::string ansi32::render(const ansi32* _blk, int _width)
{
    ui::color::pair _cp = _blk->colors();
    std::string _o = _cp();
    const ansi32* c = _blk;
    ansi32 ch;
    for(int x =0; x< _width; x++)
    {
        ch = *c++;
        auto cc = ch.colors();
        if(_cp.bg != cc.bg)
        {
            _o += ui::color::render_background(_cp.bg);
            if(_cp.fg != cc.fg)
                _o += ui::color::render(_cp.fg);
            _cp = cc;
        }
        if(ch.chr& ansi32::UTFBITS)
        {
            if(ch.chr & ansi32::Frame)
                _o += ui::cadre()[ch.frame_id()];
            else
                if(ch.chr & ansi32::Accent)
                    _o += lus::accent_fr::data[ch.accent_id()];
                else 
                    if(ch.chr & ansi32::UGlyph)
                        _o += lus::glyph::data[ch.icon_id()];
        }   
    }
    return _o;
}


std::string ansi32::details() const
{

    lus::string infos;
    lus::string utf_info{};
    if(chr & UTFBITS)
    {
        switch(chr&UTFBITS)
        {
            case UGlyph:
                utf_info | "icon index:" | icon_id();
                break;
            case Accent:
                utf_info | "accent (fr) index:" | accent_id();
                break;
            case Frame:
                utf_info << "frame index:" << frame_id();
                break;
            default:break;
                //throw rem::exception() [rem::fatal() << " Memory corruption into screen::ansi32 data!"];
        }
    }
    else
        utf_info << ascii();
    infos << "| foreground color:" << ui::color::name(foreground()) << "| background color:" << ui::color::name(background());
    infos << " char code:'" << utf_info << "';";
    if(chr & Underline) infos << "|Underline";
    if(chr & Stroke) infos << "|Stroke";
    if(chr & Blink) infos << "|Blink";
    
    return infos();
}

#pragma endregion ansi32




}
