#pragma once
/***************************************
* This is where our actors of our game environment come from. An actor is
* defined as some item in our game world that have behaviors designed to 
* perform functions within a specified of states. For example: A player Actor
* or AI Actor, or Light Actor. These actors all will have:
* -States
* -Behaviors
*/
//TODO: Create a State system
namespace LunaSolEngine
{
    class GameActor
    {
    public:
        GameActor();
        virtual ~GameActor();
    };
}
