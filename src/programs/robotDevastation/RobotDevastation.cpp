// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "RobotDevastation.hpp"

bool rd::RobotDevastation::configure(yarp::os::ResourceFinder &rf)
{
    //-- Show help
    //printf("--------------------------------------------------------------\n");
    if (rf.check("help")) {
        printf("RobotDevastation mandatory parameters:\n");
        printf("\t--id integer\n");
        printf("\t--name string\n");
        printf("\t--team integer\n");
        printf("\t--robotName string\n");
        printf("RobotDevastation optional parameters:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        printf("\t--mockupRobotManager  //-- Fake robot motors\n");
        printf("\t--mockupImageManager  //-- Fake robot camera\n");
        ::exit(0);
    }

    //-- Get player data
    //-----------------------------------------------------------------------------
    if( ! rf.check("id") )
    {
        RD_ERROR("No id! Please invoke with this parameter, as in 'robotDevastation --id integer --name string --team integer --robotName string'.\n");
        RD_ERROR("Type 'robotDevastation --help' for help.\n");
        return false;
    }
    RD_INFO("id: %d\n",rf.find("id").asInt());

    if( ! rf.check("name") )
    {
        RD_ERROR("No name! Please invoke with this parameter, as in 'robotDevastation --id integer --name string --team integer --robotName string'.\n");
        RD_ERROR("Type 'robotDevastation --help' for help.\n");
        return false;
    }
    RD_INFO("name: %s\n",rf.find("name").asString().c_str());

    if( ! rf.check("team") )
    {
        RD_ERROR("No team! Please invoke with this parameter, as in 'robotDevastation --id integer --name string --team integer --robotName string'.\n");
        RD_ERROR("Type 'robotDevastation --help' for help.\n");
        return false;
    }
    RD_INFO("team: %d\n",rf.find("team").asInt());

    if( ! rf.check("robotName") )
    {
        RD_ERROR("No robotName! Please invoke with this parameter, as in 'robotDevastation --id integer --name string --team integer --robotName string'.\n");
        RD_ERROR("Type 'robotDevastation --help' for help.\n");
        return false;
    }
    RD_INFO("robotName: %s\n",rf.find("robotName").asString().c_str());



    //-- Init input manager
    RdSDLInputManager::RegisterManager();
    inputManager = RdInputManager::getInputManager("SDL");
    inputManager->addInputEventListener(this);
    if (!inputManager->start() )
    {
        RD_ERROR("Could not init inputManager!\n");
        return false;
    }

    //-- Init sound
    if( ! initSound( rf ) )
        return false;

    if( ! rf.check("noMusic") )
        audioManager->play("bso", -1);

    //-- Init robot
    if( rf.check("mockupRobotManager") ) {
        robotManager = new RdMockupRobotManager(rf.find("robotName").asString());
    } else {
        robotManager = new RdYarpRobotManager(rf.find("robotName").asString());
    }
    if( ! robotManager->connect() ) {
        RD_ERROR("Could not connect to robotName \"%s\"!\n",rf.find("robotName").asString().c_str());
        RD_ERROR("Use syntax: robotDevastation --robotName %s\n",rf.find("robotName").asString().c_str());
        return false;
    }

    //-- Init image manager
    if( rf.check("mockupImageManager") ) {
        RdMockupImageManager::RegisterManager();
        imageManager = RdImageManager::getImageManager(RdMockupImageManager::id);
    } else {
        RdYarpImageManager::RegisterManager();
        imageManager = RdImageManager::getImageManager(RdYarpImageManager::id);
    }
    //-- Add the image processing listener to the image manager
    imageManager->addImageEventListener(&processorImageEventListener);
    //-- Configure the camera port
    std::ostringstream remoteCameraPortName;  //-- Default looks like "/0/rd1/img:o"
    remoteCameraPortName << "/";
    remoteCameraPortName << rf.find("robotName").asString();
    remoteCameraPortName << "/img:o";
    imageManager->configure("remote_img_port", remoteCameraPortName.str() );
    std::ostringstream localCameraPortName;  //-- Default should look like "/0/robot/img:i"
    localCameraPortName << "/";
    localCameraPortName << rf.find("id").asInt();
    localCameraPortName << "/robot/img:i";
    imageManager->configure("local_img_port", localCameraPortName.str() ); //-- Name given by me
    if( ! imageManager->start() )
        return false;

    //-- Init mentalMap
    mentalMap = RdMentalMap::getMentalMap();
    mentalMap->configure( rf.find("id").asInt() );

    std::vector< RdPlayer > players;
    players.push_back( RdPlayer(rf.find("id").asInt(),std::string(rf.find("name").asString()),100,100,rf.find("team").asInt(),0) );
    mentalMap->updatePlayers(players);

    mentalMap->addWeapon(RdWeapon("Default gun", 10, 5));

    //-- Init network manager
    RdYarpNetworkManager::RegisterManager();
    networkManager = RdYarpNetworkManager::getNetworkManager(RdYarpNetworkManager::id);
    networkManager->addNetworkEventListener(mentalMap);
    mentalMap->addMentalMapEventListener((RdYarpNetworkManager *)networkManager);
    networkManager->login(mentalMap->getMyself());

    //-- Init output thread
    rateThreadOutput.init(rf);

    return true;
}

bool rd::RobotDevastation::onKeyUp(rd::RdKey k)
{
if (k.isPrintable() )
    {
        RD_SUCCESS( "Key \"%c\" was pressed!\n", k.getChar() );

        if ( k.getChar() == 'w')
        {
            robotManager->stopMovement();
        }
        else if ( k.getChar() == 'a')
        {
            robotManager->stopMovement();
        }
        else if ( k.getChar() == 's')
        {
            robotManager->stopMovement();
        }
        else if ( k.getChar() == 'd')
        {
            robotManager->stopMovement();
        }
    }
	return true;
}

bool rd::RobotDevastation::onKeyDown(rd::RdKey k)
{
    if ( k.isControlKey() )
    {
        RD_SUCCESS( "Control key with code %d pressed!\n", k.getValue() );

        if ( k.getValue() == RdKey::KEY_SPACE)
        {
            //-- Do things to shoot
            mentalMap->shoot();
            RD_SUCCESS("Shoot!\n");
        }
        else if ( k.getValue() == RdKey::KEY_ESCAPE)
        {
            RD_SUCCESS("Exit!\n");
            this->interruptModule();
        }
    }
    else if (k.isPrintable() )
    {
        RD_SUCCESS( "Key \"%c\" was pressed!\n", k.getChar() );

        if ( k.getChar() == 'r')
        {
            RD_SUCCESS("Reload!\n");
            mentalMap->reload();
        }
        else if ( k.getChar() == 'q')
        {
            RD_SUCCESS("Exit!\n");
            this->interruptModule();
        }
        else if ( k.getChar() == 'w')
        {
            robotManager->moveForward();
        }
        else if ( k.getChar() == 'a')
        {
            robotManager->turnLeft();
        }
        else if ( k.getChar() == 'd')
        {
            robotManager->turnRight();
        }
        else if ( k.getChar() == 's')
        {
            robotManager->moveBackwards();
        }
    }
	return true;
}

double rd::RobotDevastation::getPeriod()
{
    return 2.0;  // Fixed, in seconds, the slow thread that calls updateModule below
}

bool rd::RobotDevastation::updateModule()
{
    printf("===robotDevastation===\n");
    printf("Number of players: %zd\n",mentalMap->getPlayers().size());
    for(size_t i=0;i<mentalMap->getPlayers().size();i++)
    {
       printf("----------------------\n%s\n",mentalMap->getPlayers().at(i).str().c_str());
    }
    //printf("======================\n");
    return true;
}

bool rd::RobotDevastation::initSound(yarp::os::ResourceFinder &rf)
{
    SDLAudioManager::RegisterManager();
    audioManager = AudioManager::getAudioManager("SDL");

    std::string bsoStr( rf.findFileByName("../sounds/RobotDevastationBSO.mp3") );
    if ( ! audioManager->load(bsoStr, "bso", 0) )
        return false;

    std::string shootStr( rf.findFileByName("../sounds/01_milshot.wav") );
    if ( ! audioManager->load(shootStr, "shoot", 1) )
        return false;

    std::string explosionStr( rf.findFileByName("../sounds/15_explosion.wav") );
    if ( ! audioManager->load(explosionStr, "explosion", 1) )
        return false;

    std::string noAmmoStr( rf.findFileByName("../sounds/03_clip.wav") );
    if ( ! audioManager->load(noAmmoStr, "noAmmo", 1) )
        return false;

    std::string reloadStr( rf.findFileByName("../sounds/04_milaction.wav") );
    if ( ! audioManager->load(reloadStr, "reload", 1) )
        return false;

    return true;
}

bool rd::RobotDevastation::interruptModule()
{
    RD_INFO("Closing program...\n");

    rateThreadOutput.stop();

    //-- Detach listeners to avoid segmentation faults
    inputManager->removeInputEventListeners();
    networkManager->removeNetworkEventListeners();
    mentalMap->removeMentalMapEventListeners();
    imageManager->removeImageEventListeners();

    //-- Closing input manager:
    RdInputManager::destroyInputManager();
    inputManager = NULL;

    //-- Closing network system
    networkManager->logout(mentalMap->getMyself());
    networkManager->stop();
    RdNetworkManager::destroyNetworkManager();
    networkManager = NULL;

    //-- Closing audio system:
    AudioManager::destroyAudioManager();
    audioManager = NULL;

    //-- Closing mental map:
    RdMentalMap::destroyMentalMap();
    mentalMap = NULL;

    //-- Close img related ports:
    imageManager->stop();
    RdImageManager::destroyImageManager();
    imageManager = NULL;

    robotManager->disconnect();

    return true;
}

