#pragma once

class Timer
{
public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();

private:
    //time at started
    double start_tick_;
    //The ticks stored when the timer was paused
    double paused_ticks_;
    bool is_paused_;
    bool is_started_;
};