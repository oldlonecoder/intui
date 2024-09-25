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

#include "element.h"
#include <memory>

namespace lus::ui
{

class screen : public element
{

    static std::shared_ptr<screen> _screen_;
public:
    screen();
    ~screen() override;

    static std::shared_ptr<screen> instance();

};

} // namespace lus::ui



