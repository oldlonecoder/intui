//
// Created by oldlonecoder on 8/30/24.
//

//#ifndef ELEMENT_H
//#define ELEMENT_H
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


#include "intui/globals.h"
#include "intui/support/ansi_32.h"
#include "intui/support/object.h"


namespace lus::ui
{

class INTUI_API element : public object
{
    OBJECT_REFLECT(element)

protected:
    ansi32* _bloc_{nullptr}; ///< All elements have their own back/screen buffer
    ansi32* _caret_{nullptr}; ///< `caret` at the current position into the _bloc_;
    ui::rectangle _rect_;  ///< element's geometry. ( xy (relative-or-absolute)position, width, height, then inner cursor )
    intui::globals::justify::Type _just_{intui::globals::justify::word_wrap};
    std::string_view _theme_{};
    intui::globals::colors::attr_db::components _style_{};
    color::pair _color_{};
    rectangle _dirty_rect_{};
    intui::globals::wstate::Type _state_{intui::globals::wstate::Active};

public:
    element();
    element(object* _parent_obj, const std::string a_id);
    ~element() override;


    book::code set_theme(std::string_view theme_name);
    color::pair colors();

    rectangle geometry() const { return _rect_; }
    book::code set_geometry(rectangle _geom);


    template<typename T=int> std::optional<T> width() const
    {
        return _rect_.width<T>();
    }
    
    template<typename T=int> std::optional<T> height() const
    {
        return _rect_.height<T>();
    }

    element& operator*() { return *this; }
    ansi32* peek(ui::cxy xy);
    
    rectangle local_geometry() { return _rect_ - _rect_.top_left(); }
    rectangle intersect(rectangle _region) { return local_geometry() & _region; };
    ui::cxy top_left() const;
    ui::cxy top_right() const;
    ui::cxy bottom_left() const;
    ui::cxy bottom_right() const;
    
#pragma region draw


    struct INTUI_API brush final 
    {
        element* _element_{nullptr};
        rectangle _rect_{}; ///< Sub rectangle relative to the element's drawing area;
        ansi32*   _caret_{nullptr};
        color::pair _colors_{};

        brush() = default;
        brush(element* _element, rectangle _region);
        ~brush() = default;

        book::code home();
        book::code cursor(ui::cxy xy);

        brush& operator *() { return *this; }
        brush& operator << (char _char);
        brush& operator << (ansi32 _char);
        brush& operator << (const char* _str);
        brush& operator << (const std::string& _str) { return **this << _str.c_str(); }
        brush& operator << (const ansi32::string& _str);
        template<typename T> brush& operator << (const T& _T)
        {
            lus::string str;
            str << _T;
            return **this << str().c_str();
        }

        // ----  Code a tester a pour tester :
        ui::cxy get_local_xy() const;
        ui::cxy get_element_xy();
        operator bool() const;

        void clear();

    };

    void dealloc();
    
    brush       begin_paint(rectangle _region);
    book::code  end_paint(element::brush& _brush);
    book::code update();
    book::code update_child(element* _chil_element);
    void renderline(int line_num);
    
#pragma endregion draw
private:
    void _clear_();
};



} // namespace lus::ui


//#endif //ELEMENT_H
