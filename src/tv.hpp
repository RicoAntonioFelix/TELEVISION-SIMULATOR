/*
 * Copyright 2014 Rico Antonio Felix
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef TV_HOME_EDITION
#define TV_HOME_EDITION

/*
 * Platform dependency
 */
#include <iostream>

namespace compuSUAVE_Professional {

/*
 * Using 1 byte to hold state values where:
 * 00000000
 *        ^ determine on or off
 * 00000001 = on
 * 00000000 = off
 */
const unsigned char OFF_ON = 0x1; // Set to on

/*
 * Using 1 byte to hold state values where:
 * 00000000
 *       ^ determine cable or antenna
 * 00000010 = antenna
 * 00000000 = cable
 */
const unsigned char CABLE_ANTENNA = 0x1 << 1; // Set to antenna

/*
 * Channel range [1-128]
 * minimum = 1
 * maximum = 128
 */
const unsigned char MINIMUM_CHANNEL = 0x1;
const unsigned char MAXIMUM_CHANNEL = 0x1 << 7;


class TV; // Forward declaration for Remote

class Remote
{
public:
    static constexpr void toggle_state(TV & tv); // Toggle reference on or off

    static constexpr void toggle_mode(TV & tv); // Toggle reference to cable or antenna

    static constexpr void change_channel_up(TV & tv); // Increment reference channel

    static constexpr void change_channel_down(TV & tv); // Decrement reference channel

    static constexpr void change_channel(TV & tv, unsigned char const & channel); // Set reference channel

    static void display_settings(TV & tv); // Display reference settings

    /*
     * Prevent object instantiation
     */
    Remote() = delete;
};

class TV
{
public:

    /*
     * Provide Remote's change_channel(TV&, unsigned char const&) method special
     * access privilages to perform its required operation
     */
    friend void Remote::change_channel(TV & tv, unsigned char const & channel);

    /*
     * Initialize an object of this component to default state as follows:
     * on, antenna, channel = 1
     * This is provided that no arguments was used to initialize the object
     *
     * Otherwise, initialize the object to the state of the arguments
     */
    constexpr TV(unsigned char const & initial_state_mode = OFF_ON | CABLE_ANTENNA,
                 unsigned char const & initial_channel = MINIMUM_CHANNEL)
        :  state_mode{initial_state_mode}
        ,  padding{0x0}
        ,  channel{initial_channel}
    {}

    /*
     * Toggle object on or off
     */
    constexpr void toggle_state()
    {
        state_mode ^= OFF_ON;
    }

    /*
     * Toggle object's mode between cable or antenna
     */
    constexpr void toggle_mode()
    {
        state_mode ^= CABLE_ANTENNA;
    }

    /*
     * Move channel to the next
     */
    constexpr void change_channel_up()
    {
        if (channel < MAXIMUM_CHANNEL)
            channel++;
        else
            channel = MINIMUM_CHANNEL;
    }

    /*
     * Move channel to the previous
     */
    constexpr void change_channel_down()
    {
        if (channel > MINIMUM_CHANNEL)
            channel--;
        else
            channel = MAXIMUM_CHANNEL;
    }

    /*
     * Display the object settings
     */
    void display_settings() const
    {
        if (state_mode & OFF_ON)
        {
            std::cout << "Mode: " << (state_mode & CABLE_ANTENNA ? "Antenna" : "Cable") << std::endl;
            std::cout << "Channel: " << (int)channel << std::endl;
        }
    }

private:

    /*
     * This field uses a bit field of 2 to hold the following information:
     * Bit 1: 0 = off, 1 = on
     * Bit 2: 0 = cable, 1 = antenna
     */
    unsigned char state_mode : 2;

    /*
     * This field is reserved for future requirements
     */
    unsigned char padding : 6;

    /*
     * This field is used to store channel information
     */
    unsigned char channel;
};


/*---------Implementation of Remote methods---------*/

constexpr void Remote::toggle_state(TV & tv)
{
    tv.toggle_state();
}

constexpr void Remote::toggle_mode(TV & tv)
{
    tv.toggle_mode();
}

constexpr void Remote::change_channel_up(TV & tv)
{
    tv.change_channel_up();
}

constexpr void Remote::change_channel_down(TV & tv)
{
    tv.change_channel_down();
}

constexpr void Remote::change_channel(TV & tv, unsigned char const & channel)
{
    if (channel >= MINIMUM_CHANNEL &&
        channel <= MAXIMUM_CHANNEL)
        tv.channel = channel;
}

void Remote::display_settings(TV & tv)
{
    tv.display_settings();
}

/*---------End of Implementation block---------*/

} // namespace compuSUAVE_Professional

#endif
