//
// Created by stef on 08.04.20.
//

#ifndef PROJECT_CHANNEL_H
#define PROJECT_CHANNEL_H

enum ChannelType {SAA};

class Channel {
public:
    virtual ChannelType getType() = 0;
};


#endif //PROJECT_CHANNEL_H
