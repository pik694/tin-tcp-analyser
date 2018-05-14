//
// Created by Daniel Bigos on 04.05.18.
//

#ifndef UNIX_TCP_ANALYSER_TCPOPTIONS_H
#define UNIX_TCP_ANALYSER_TCPOPTIONS_H

namespace tcp_analyser::utils::system_api::options
{
    enum class TCPOptions_E
    {
        SACK = 4
    };

    class Option
    {
    public:
        Option() = default;
        virtual ~Option() = default;

    protected:
        bool enabled_ { false };
    };
}

#endif //UNIX_TCP_ANALYSER_TCPOPTIONS_H
