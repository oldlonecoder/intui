//
// Created by oldlonecoder on 8/21/24.
//

//#ifndef ANSI_32_H
//#define ANSI_32_H
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

#include "intui/support/colors.h"
#include "intui/support/glyphes.h"
#include "intui/support/cadres.h"

namespace lus
{

using namespace integers;

/*!
 * @brief Compacted/Encoded ansi true color terminal chars.
 *
 * @note Does NOT support UTF encoded data. Only one-byte utf-8 chars such as accent and glyphes encoded as index into my own table of hardcoded "utf-8 strings",
 *       using std::string data as automatic/implicit conversion.
 */
struct INTUI_API ansi32 final
{
    U32 chr = 0x8003A020;
    using string                   = std::vector<ansi32>;
    
    static constexpr U32 CharMask  = 0x800000FF;
    static constexpr U32 FGMask    = 0x0000FF00;
    static constexpr U32 BGMask    = 0x00FF0000;
    static constexpr U32 CMask     = 0x00FFFF00;
    static constexpr U32 ColorsMask= 0x00FFFF00;
    static constexpr U32 AttrMask  = 0xFF000000;
    static constexpr U32 UtfMask   = 0xB10000FF;
    static constexpr U32 StyleMask = 0x0E000000;
    // ==================attributes==========================
    static constexpr U32 UGlyph    = 0x01000000;
    static constexpr U32 Underline = 0x02000000;
    static constexpr U32 Stroke    = 0x04000000;
    static constexpr U32 Blink     = 0x08000000;
    static constexpr U32 Accent    = 0x10000000;
    static constexpr U32 Frame     = 0x20000000;
    static constexpr U32 TRGB      = 0x40000000;
    /// This will make use of true-color RGB command instead of the re-routed terminal GUI colors profile
    static constexpr U32 ASCII     = 0x80000000;
    static constexpr U32 UTFBITS   = Accent | Frame | UGlyph;
    // ==============Bit Shift ============================
    static constexpr int FGShift = 0x08;
    static constexpr int BGShift = 0x10;
    static constexpr int ATShift = 0x18;



    ansi32() = default;

    explicit ansi32(U32 Ch);
    explicit ansi32(ansi32* C);
    ~ansi32() = default;

    ansi32& set_fg(ui::color::code fg_);
    ansi32& set_bg(ui::color::code bg_);

    ansi32& set_attributes(U32 Ch);
    ansi32& set_colors(ui::color::pair&&Ch);
    // ansi32& ResetAttributes(ansi32::Type bits_);

    ansi32& set_colors(ui::color::pair&CP);

    ansi32& operator=(U32 Ch);
    ansi32& operator=(ansi32 Ch) { chr = Ch.chr; return *this;}
    ansi32& operator=(U32* Ch);
    ansi32& operator=(char Ch);
    ansi32& operator=(int Ch)
    {
        chr = Ch;
        return *this;
    };

    std::string get_utf_string() const;

    ui::color::code     foreground() const;
    ui::color::code     background() const;
    ui::color::pair     colors() const;
    lus::glyph::type     icon_id() const;
    lus::accent_fr::type accent_id() const;
    ui::cadre::index    frame_id() const;
    char     ascii() const;
    ansi32&  operator*() { return *this; }
    uint16_t attributes() const;
    ansi32&  operator <<(lus::glyph::type gl);
    ansi32&  operator <<(lus::accent_fr::type ac);
    ansi32& operator << (ui::cadre::index fr);
    ansi32& operator <<(ui::color::pair cp);


    ansi32& operator <<(ansi32 Ch)
    {
        chr = Ch.chr;
        return *this;
    }

    static std::string render(const ansi32::string& _string);
    static std::string render(const ansi32* _blk, int _width);
    
    ansi32&     operator <<(char Ch);
    std::string render_colors() const;
    explicit    operator std::string() const;

    std::string details() const;
};
}

//#endif //ANSI_32_H
