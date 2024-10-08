// Created by oldlonecoder on 8/13/24.
//

//#ifndef INTUI_GLOBALS_H
//#define INTUI_GLOBALS_H
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


#include "intui/support/object.h"
#include "csignal"
#include <memory>

namespace lus::intui
{

class INTUI_API application : public object
{
    OBJECT_REFLECT(application)

    static void sig_interrupted(int);
    static void sig_aborted(int);
    static void sig_crash(int);

    
    static std::shared_ptr<application> _app_;
public:
    application() = delete;
    ~application() override;
    application(const std::string& app_name, int arc, char **argv);
    virtual book::code run();

    static std::shared_ptr<application> create(const std::string& app_name, int args, char** argv);
    static std::shared_ptr<application> instance();


protected:
    virtual book::code setup();
    virtual book::code install_signals();
    

};



}
