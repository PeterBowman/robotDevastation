// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __RD_RPC_RESPONDER__
#define __RD_RPC_RESPONDER__

#include <yarp/os/Port.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Time.h>
#include <yarp/os/Vocab.h>

#include <vector>

#include "RdUtils.hpp"
#include "RdPlayer.hpp"

#define VOCAB_RD_LOGIN VOCAB3('l','o','g')
#define VOCAB_RD_OK VOCAB2('o','k')
#define VOCAB_RD_FAIL VOCAB('f','a','i','l')

namespace rd
{

class RdRpcResponder : public yarp::os::PortReader {
  protected:
    /**
    * Implement the actual responder (callback on RPC).
    */
    virtual bool read(yarp::os::ConnectionReader& connection);

  public:
    std::vector <RdPlayer>* players;
    void setPlayers(std::vector<RdPlayer> *value);
};

}

#endif
