// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RdServer.hpp"

bool rd::RdServer::configure(yarp::os::ResourceFinder &rf)
{
    rdRpcResponder.setPlayers(&players, &players_belief, &players_mutex);
    rdBroadcast.open("/rdServer/info:o");
    rpcServer.open("/rdServer/rpc:s");
    rpcServer.setReader(rdRpcResponder);
    return true;
}

rd::RdServer::~RdServer()
{

}

double rd::RdServer::getPeriod()
{
    return 0.1;  // Fixed, in seconds, the slow thread that calls updateModule below
}

bool rd::RdServer::updateModule()
{
    //-- Broadcast player info
    players_mutex.lock();
    yarp::os::Bottle msgBroadcast;
    msgBroadcast.addVocab(VOCAB_RD_PLAYERS);
    printf("=======rdServer=======\n");
    printf("Number of players: %zd\n",players.size());

    typedef std::map<int, RdPlayer>::iterator it_type;
    for(it_type iterator = players.begin(); iterator != players.end(); iterator++)
    {
       printf("----------------------\n%s\n", (iterator->second).str().c_str());
       printf("Belief: %d\n", players_belief[iterator->first]);
       yarp::os::Bottle msgPlayer;
       msgPlayer.addInt( (iterator->second).getId() );
       msgPlayer.addString( (iterator->second).getName().c_str() );
       msgPlayer.addInt( (iterator->second).getHealth() );
       msgPlayer.addInt( (iterator->second).getMaxHealth() );
       msgPlayer.addInt( (iterator->second).getTeamId() );
       msgPlayer.addInt( (iterator->second).getScore() );
       msgBroadcast.addList() = msgPlayer;
    }

    //printf("======================\n");
    rdBroadcast.write(msgBroadcast);
    players_mutex.unlock();

    //-- Decrease players belief
    players_mutex.lock();
    for(it_type it = players.begin(); it != players.end(); )
    {
        //-- Erasing current map element only works in a loop if keeping track
        //-- of the next element by hand: http://stackoverflow.com/questions/5671733/c-map-iteration-with-deletion#5673209
        it_type next = it;
        ++next;

        //-- Decrease belief and erase if required
        int id = it->first;
        players_belief[id] -= 1;
        if (players_belief[id]<=0)
        {
            //-- Remove player from player table
            players.erase(id);
            players_belief.erase(id);
        }

        it = next;
    }
    players_mutex.unlock();

    return true;
}

bool rd::RdServer::interruptModule() {
    printf("RdServer closing...\n");
    rdBroadcast.interrupt();
    rpcServer.interrupt();
    rdBroadcast.close();
    rpcServer.close();
    return true;
}

