#include "gtest/gtest.h"
#include <string>
#include <vector>

#include "RdMentalMap.hpp"
#include "RdEnemy.hpp"
#include "RdPlayer.hpp"

using namespace rd;

class RdMentalMapTest : public testing::Test
{
    public:
        virtual void SetUp()
        {
            player1 = new RdPlayer(0, "Myself", 100, 100, 0, 0);
            player2 = new RdPlayer(1, "Enemy", 100, 100, 1, 0);
            player3 = new RdPlayer(2, "Enemy2", 100, 100, 1, 0);

            enemy1 = new RdEnemy(1, RdVector2d(100, 100), RdVector2d(50, 50));
            enemy2 = new RdEnemy(2, RdVector2d( 20,  20), RdVector2d( 5,  5));
        }

        virtual void TearDown()
        {
            delete player1; player1 = NULL;
            delete player2; player2 = NULL;
            delete player3; player3 = NULL;

            delete enemy1; enemy1 = NULL;
            delete enemy2; enemy2 = NULL;
        }

        RdPlayer * player1, * player2, * player3;

        RdEnemy * enemy1, * enemy2;

    protected:
        RdMentalMap * mentalMap;
};



TEST_F( RdMentalMapTest, CreateCreatesMentalMap)
{
    //-- Create a mental map for two players:
    const int n_players = 2;
    const int id = 0;
    mentalMap = new RdMentalMap(id, n_players);
    ASSERT_FALSE(!mentalMap);

    //-- Check the number of players
    std::vector<RdPlayer> players = mentalMap->getPlayers();
    EXPECT_EQ(0, (int) players.size());

    //-- Check the number of enemies
    std::vector<RdEnemy> enemies = mentalMap->getEnemies();
    EXPECT_EQ(0, (int) enemies.size());

    //-- Destroy the mentalMap
    EXPECT_TRUE(mentalMap->destroy());
    delete mentalMap;
    mentalMap = NULL;

}



//---------------------------------------------------------------------------------------
//-- Player-related
//---------------------------------------------------------------------------------------

TEST_F( RdMentalMapTest, UpdatePlayersUpdatesPlayers)
{
    //-- Create a mental map for two players:
    const int n_players = 2;
    const int id = 0;
    mentalMap = new RdMentalMap(id, n_players);
    ASSERT_FALSE(!mentalMap);

    //-- Update players:
    std::vector<RdPlayer> players;
    players.push_back(*player1);
    players.push_back(*player2);

    ASSERT_TRUE(mentalMap->updatePlayers(players));

    //-- Check players stored:
    std::vector<RdPlayer> players_stored = mentalMap->getPlayers();
    ASSERT_EQ(2, (int) players_stored.size());

    if (players_stored[0].getId() == 0)
    {
        EXPECT_STREQ("Myself", players_stored[0].getName().c_str());
        EXPECT_EQ(100, players_stored[0].getHealth());
        EXPECT_EQ(100, players_stored[0].getMaxHealth());
        EXPECT_EQ(0, players_stored[0].getTeamId());
        EXPECT_EQ(0, players_stored[0].getScore());

        EXPECT_EQ(1, players_stored[1].getId());
        EXPECT_STREQ("Enemy", players_stored[1].getName().c_str());
        EXPECT_EQ(100, players_stored[1].getHealth());
        EXPECT_EQ(100, players_stored[1].getMaxHealth());
        EXPECT_EQ(1, players_stored[1].getTeamId());
        EXPECT_EQ(0, players_stored[1].getScore());
    }
    else if (players_stored[1].getId() == 0)
    {
        EXPECT_STREQ("Myself", players_stored[1].getName().c_str());
        EXPECT_EQ(100, players_stored[1].getHealth());
        EXPECT_EQ(100, players_stored[1].getMaxHealth());
        EXPECT_EQ(0, players_stored[1].getTeamId());
        EXPECT_EQ(0, players_stored[1].getScore());

        EXPECT_EQ(1, players_stored[0].getId());
        EXPECT_STREQ("Enemy", players_stored[0].getName().c_str());
        EXPECT_EQ(100, players_stored[0].getHealth());
        EXPECT_EQ(100, players_stored[0].getMaxHealth());
        EXPECT_EQ(1, players_stored[0].getTeamId());
        EXPECT_EQ(0, players_stored[0].getScore());
    }
    else
    {
        //-- Break test
        ASSERT_TRUE(false);
    }


    //-- Change players & update mental map:
    players[0].setHealth(50);
    players[1].setScore(100);
    ASSERT_TRUE(mentalMap->updatePlayers(players));


    //-- Check players stored:
    players_stored = mentalMap->getPlayers();
    ASSERT_EQ(2, (int) players_stored.size());

    if (players_stored[0].getId() == 0)
    {
        EXPECT_STREQ("Myself", players_stored[0].getName().c_str());
        EXPECT_EQ(50, players_stored[0].getHealth());
        EXPECT_EQ(100, players_stored[0].getMaxHealth());
        EXPECT_EQ(0, players_stored[0].getTeamId());
        EXPECT_EQ(0, players_stored[0].getScore());

        EXPECT_EQ(1, players_stored[1].getId());
        EXPECT_STREQ("Enemy", players_stored[1].getName().c_str());
        EXPECT_EQ(100, players_stored[1].getHealth());
        EXPECT_EQ(100, players_stored[1].getMaxHealth());
        EXPECT_EQ(1, players_stored[1].getTeamId());
        EXPECT_EQ(100, players_stored[1].getScore());
    }
    else if (players_stored[1].getId() == 0)
    {
        EXPECT_STREQ("Myself", players_stored[1].getName().c_str());
        EXPECT_EQ(50, players_stored[1].getHealth());
        EXPECT_EQ(100, players_stored[1].getMaxHealth());
        EXPECT_EQ(0, players_stored[1].getTeamId());
        EXPECT_EQ(0, players_stored[1].getScore());

        EXPECT_EQ(1, players_stored[0].getId());
        EXPECT_STREQ("Enemy", players_stored[0].getName().c_str());
        EXPECT_EQ(100, players_stored[0].getHealth());
        EXPECT_EQ(100, players_stored[0].getMaxHealth());
        EXPECT_EQ(1, players_stored[0].getTeamId());
        EXPECT_EQ(100, players_stored[0].getScore());
    }
    else
    {
        //-- Break test
        ASSERT_TRUE(false);
    }

    //-- Destroy the mentalMap
    EXPECT_TRUE(mentalMap->destroy());
    delete mentalMap;
    mentalMap = NULL;
}

TEST_F( RdMentalMapTest, MyselfPointsToMe)
{
    //-- Create a mental map for two players:
    const int n_players = 2;
    const int id = 0;
    mentalMap = new RdMentalMap(id, n_players);
    ASSERT_FALSE(!mentalMap);

    //-- Update players:
    std::vector<RdPlayer> players;
    players.push_back(*player1);
    players.push_back(*player2);

    ASSERT_TRUE(mentalMap->updatePlayers(players));

    //-- Check players stored:
    std::vector<RdPlayer> players_stored = mentalMap->getPlayers();
    ASSERT_EQ(2, (int) players_stored.size());

    //-- Check if myself is me:
    RdPlayer me = mentalMap->getMyself();
    EXPECT_EQ(0, me.getId());
    EXPECT_STREQ("Myself", me.getName().c_str());
    EXPECT_EQ(0, me.getTeamId());

    //-- Destroy the mentalMap
    EXPECT_TRUE(mentalMap->destroy());
    delete mentalMap;
    mentalMap = NULL;

}



//---------------------------------------------------------------------------------------
//-- Enemy-related
//---------------------------------------------------------------------------------------

TEST_F( RdMentalMapTest, UpdateEnemiesUpdateEnemies)
{
    //-- Create a mental map for two players:
    const int n_players = 2;
    const int id = 0;
    mentalMap = new RdMentalMap(id, n_players);
    ASSERT_FALSE(!mentalMap);


    //-- Update players:
    std::vector<RdPlayer> players;
    players.push_back(*player1);
    players.push_back(*player2);

    ASSERT_TRUE(mentalMap->updatePlayers(players));


    //-- Update enemies:
    std::vector<RdEnemy> enemies;
    enemies.push_back(*enemy1);

    ASSERT_TRUE(mentalMap->updateEnemies(enemies));


    //-- Check enemies:
    std::vector<RdEnemy> enemies_stored = mentalMap->getEnemies();
    ASSERT_EQ(1, enemies_stored.size());
    EXPECT_EQ(1, enemies_stored[0].getPlayerId());
    EXPECT_EQ(100, enemies_stored[0].getPos().x);
    EXPECT_EQ(100, enemies_stored[0].getPos().y);
    EXPECT_EQ(50, enemies_stored[0].getDimensions().x);
    EXPECT_EQ(50, enemies_stored[0].getDimensions().y);
    EXPECT_EQ(100, enemies_stored[0].getBelief());

    //-- Destroy the mentalMap
    EXPECT_TRUE(mentalMap->destroy());
    delete mentalMap;
    mentalMap = NULL;
}

TEST_F( RdMentalMapTest, UpdateEnemiesEventuallyDeletesEnemies)
{
    //-- Create a mental map for two players:
    const int n_players = 3;
    const int id = 0;
    mentalMap = new RdMentalMap(id, n_players);
    ASSERT_FALSE(!mentalMap);


    //-- Update players:
    std::vector<RdPlayer> players;
    players.push_back(*player1);
    players.push_back(*player2);
    players.push_back(*player3);
    ASSERT_TRUE(mentalMap->updatePlayers(players));


    //-- Update enemies:
    std::vector<RdEnemy> enemies;
    enemies.push_back(*enemy1);
    enemies.push_back(*enemy2);

    ASSERT_TRUE(mentalMap->updateEnemies(enemies));


    //-- Update with a single enemy until belief for the other enemy reaches 0:
    //-- (Belief decrease is hardcoded, and decreases by 10 each update)
    std::vector<RdEnemy> new_enemy_vector;
    new_enemy_vector.push_back(*enemy2);
    ASSERT_TRUE(mentalMap->updateEnemies(new_enemy_vector));

    //-- Check enemies:
    RdEnemy enemy_not_updated = mentalMap->getEnemy(1);
    EXPECT_EQ(1, enemy_not_updated.getPlayerId());
    EXPECT_EQ(100, enemy_not_updated.getPos().x);
    EXPECT_EQ(100, enemy_not_updated.getPos().y);
    EXPECT_EQ(50, enemy_not_updated.getDimensions().x);
    EXPECT_EQ(50, enemy_not_updated.getDimensions().y);
    EXPECT_EQ(90, enemy_not_updated.getBelief());


    for (int i = 0; i < 9; i++)
    {
        ASSERT_TRUE(mentalMap->updateEnemies(new_enemy_vector));
    }

    EXPECT_EQ(1, mentalMap->getEnemies().size());
    EXPECT_EQ(2, mentalMap->getEnemies()[0].getPlayerId());
    EXPECT_EQ(100, mentalMap->getEnemies()[0].getBelief());

    //-- Destroy the mentalMap
    EXPECT_TRUE(mentalMap->destroy());
    delete mentalMap;
    mentalMap = NULL;
}



//---------------------------------------------------------------------------------------
//-- Thread-safe functions
//---------------------------------------------------------------------------------------

TEST_F( RdMentalMapTest, EnemiesLockedWhenModified)
{
    ASSERT_TRUE(false);
}

TEST_F( RdMentalMapTest, PlayersLockedWhenModified)
{
    ASSERT_FALSE(true);
}