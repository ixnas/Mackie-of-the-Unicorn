//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_STATEMACHINE_H
#define MACKIE_OF_THE_UNICORN_STATEMACHINE_H

#include <memory>

namespace MackieOfTheUnicorn
{
	template <class StateType>
	class StateMachine
	{
	  public:
		virtual ~StateMachine() = default;
		virtual void SetState(std::unique_ptr<StateType> nextState) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_STATEMACHINE_H
