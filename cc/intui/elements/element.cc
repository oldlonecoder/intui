//
// Created by oldlonecoder on 8/30/24.
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


#include "intui/elements/element.h"
#include <cstring>
#include "intui/elements/screen.h"
#include "intui/io/linux/terminal.h"

using namespace lus::intui::globals;

namespace lus::ui
{
element::element():object(nullptr, "element"){}
element::element(object* _parent_obj, const std::string a_id):object(_parent_obj, a_id){}


element::~element()
{
    book::log() << "release '" << color::yellow << id() << color::reset << "'s bloc...";
    delete [] _bloc_;
}


book::code element::set_theme(std::string_view _theme_name)
{
    _style_ = colors::attr_db::theme()[_theme_name]["Widget"];
    book::log() << color::yellow << id() << color::reset << "'s theme set to '" << color::lime << _theme_name << color::reset << ".";
    return book::code::accepted;
}

color::pair element::colors()
{
    return _style_[_state_];
}



book::code element::set_geometry(rectangle _geom)
{
    if(_rect_)
    {
        if(_rect_.dwh.area() <= _geom.dwh.area())
            return book::code::accepted;
    }
    _rect_ = std::move(_geom);
    book::log() << "element '" << color::yellow << id() << color::reset << "' geometry:" << color::lime << _rect_.tostring() << color::reset << '.';
    if(!_rect_)
        return book::code::rejected;
    
    delete  [] _bloc_;
    _bloc_ = new ansi32[_rect_.dwh.area()+ *_rect_.width()];

    _clear_();

    return book::code::accepted;
}

/**
 * @brief 'peeks' at the given xy position within the _bloc_.
 * 
 * @param xy 
 * @return ansi32* 
 * @throws book::exception& on out of boundaries. So no mercy!
 */
ansi32 *lus::ui::element::peek(ui::cxy xy)
{
    if(!local_geometry()[xy])
    {
        throw book::exception() [
            book::except() << book::code::oob 
            << ui::color::red4 << xy
            << ui::color::reset << " => "
            << ui::color::red3 << _rect_.tostring()
            << ui::color::reset  << " in method element::peek()"
        ];
        // book::error() << book::fn::function;
        // book::out() << book::code::oob << xy;
        return nullptr;
    }
    return _bloc_ + xy.y * *_rect_.width() + xy.x; 
}

ui::cxy element::top_left() const
{
    return _rect_.a;
}

ui::cxy element::top_right() const
{
    return {_rect_.b.x, _rect_.a.y};
}

ui::cxy element::bottom_left() const
{
    return{_rect_.a.x, _rect_.b.y};
}

ui::cxy element::bottom_right() const
{
    return _rect_.b;
}

element::brush::brush(element *_element, rectangle _region): _element_(_element), _rect_(_region)
{
    if(!_element)
    {
        book::fatal() << book::fn::function;
        book::out() << " Cannot construct an element::brush when the element itself is nullptr!";
        return ;
    } 

    if(!_rect_)
        _rect_ = _element->local_geometry();
    else 
    {
        if(_rect_ = _element->intersect(_region); !_rect_)
            _rect_ = _element->local_geometry();
    }

    // Init cursors and pointers:
    home();
    book::debug() << "element::brush construct region= " << _rect_.tostring();
    _colors_ = _element_->colors();
    book::debug() << book::fn::function;
    book::out() << "fg: " << color::name(_colors_.fg) << " bg: " << color::name(_colors_.bg);
}


/**
 * 
 * @param _char put_char into element's _bloc_ at the brush's current position then advance the inner cursors.
 * @return ref to self;
 */
element::brush& element::brush::operator << (char _char)
{
    **_caret_ << _char;
    ++_caret_;
    ++_rect_;   // Advance internal cursor.x; ( _rect_++; // Advance internal cursor.y; )
    return *this;
}


/**
 *
 * @param _char  put ansi32::_char into element's _bloc_ at the brush's current position then advance the inner cursors.
 * @return ref to self;
 */
element::brush& element::brush::operator << (ansi32 _char)
{
    *_caret_ = _char;
    ++_caret_;
    ++_rect_;   // Advance internal cursor.x; ( _rect_++; // Advance internal cursor.y; )
    return *this;
}


/**
 * @brief Write string onto the element bloc, the update the cursors positions.
 * 
 * @param _str 
 * @return element::brush& 
 */
element::brush &lus::ui::element::brush::operator<<(const char *_str)
{
    if(!_caret_) home();
    if(!_caret_)
    {
        throw book::exception() [
            book::except() 
            << book::code::null_ptr  
            << ui::color::reset  << " in method element::peek()"
        ];
    }

    // put the text at the _caret_, confine the text into our geometry.
    auto ci = _str;

    // NoWrap and stops at the brush's width:
    //while(*ci && (ci - _str) < (*_rect_.width()-(ci-_str))) **(_caret_++) << *ci++;
    // else
    while(*ci) **(_caret_++) << *ci++;
    _caret_ += ::strlen(_str);
    _rect_.goto_xy(_rect_.cursor + ui::cxy{static_cast<int>(strlen(_str)),0});
    return *this;
}


/**
 * @brief writes string into the bloc with the current attributes and at the current cursor position.
 * 
 *        - Advance(updates) the inner cursor.
 * 
 * @param _txt 
 * @return element& 
 */

inline book::code element::brush::home()
{
    _rect_.home();
    _caret_ = _element_->peek(_rect_.a);

    return book::code();
}

book::code element::brush::cursor(ui::cxy xy)
{
    if(!_rect_.goto_xy(xy)) return book::code::rejected;
    _rect_.goto_xy(xy);
    _caret_ = _element_->peek(_rect_.cursor + _rect_.top_left());
    return book::code::accepted;
}

void element::brush::clear()
{
    home();
    _caret_ = _element_->peek({0,0});
    ansi32 ch;
    ch.set_colors(_colors_);
    ch = ' ';
    book::debug() << book::fn::function;
    book::out() << "clear with attributes: " << ch.details();
    for(int i = 0; i<_rect_.dwh.area(); i++){_caret_->chr = ch.chr; ++_caret_; }
    home();
}


ui::cxy element::brush::get_local_xy() const
{
    return _rect_.cursor;
}

ui::cxy element::brush::get_element_xy()
{
    return _rect_.cursor + _rect_.top_left();
}


void element::dealloc()
{
    delete [] _bloc_;
    _bloc_ = nullptr;
}




/**
 * @brief ...
 * 
 * @param _region 
 * @return element::brush 
 * 
 * @todo throw book::exception() on invalid data : 
 */
element::brush element::begin_paint(rectangle _region) 
{
    return element::brush{this, _region};
}

book::code element::end_paint(element::brush& _brush)
{
    _dirty_rect_ = _dirty_rect_ | _brush._rect_;
    book::log() << book::fn::function;
    book::out() << "Brush area was:" << color::lime << _brush._rect_.tostring() << color::reset;
    book::out() << "dirty rect: " << color::lime << _dirty_rect_.tostring() << color::reset;
    if(this != screen::instance().get())
    {
        ;
    }
    //...
    return book::code::done;
}



book::code element::update()
{

    for(int y=0; y < *height(); y++)
    {
        intui::terminal::cursor({top_left() + cxy{0,y} });
        renderline(y);
    }

    return book::code::accepted;
}

book::code element::update_child(element *_child_element)
{
    rectangle r;
    if(!_child_element->_dirty_rect_) return book::code::rejected;
    if(!_dirty_rect_)
        r = _dirty_rect_ = rectangle{_child_element->_dirty_rect_ + _child_element->_rect_.a};
    else     
        r = rectangle{_child_element->_dirty_rect_ + _child_element->_rect_.a} | _dirty_rect_;
    
    
    return book::code::accepted;
}

void element::renderline(int line_num)
{
    auto* s = peek({0,line_num});
    book::debug() << "renderline: peek details :" << s->details();
    auto out = ansi32::render(s, *width());
    std::cout << out;
    fflush(stdout);

}

void element::_clear_()
{
    ansi32 C;
    auto colors = _style_[_state_];
    C.set_colors(colors);
    C << ' ';
    ansi32* w = _bloc_;
    auto sz = _rect_.dwh.area();

    book::debug() << book::fn::function;
    book::out() << "clear with attributes: " << C.details();
    for(int i=0; i < sz; i++)
    {
        w->chr = C.chr;
        ++w;
    }
}

element::brush::operator bool() const
{
    return _rect_ && _element_;
}


} // namespace lus::ui
