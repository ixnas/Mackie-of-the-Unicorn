//
// Created by Sjoerd Scheffer on 28/02/2022.
//

#ifndef MACKIE_OF_THE_UNICORN_STATEMACHINE_H
#define MACKIE_OF_THE_UNICORN_STATEMACHINE_H

#include <memory>

namespace MackieOfTheUnicorn
{
	/// @brief Interface classes that implement a state machine pattern.
	/// @tparam StateType Type of the state implementation.
	/// @tparam AdditionalArguments Additional arguments for setting the next state that may be required by the state machine.
	template <class StateType, class... AdditionalArguments>
	class StateMachine
	{
	  public:
		virtual ~StateMachine() = default;

		/// Sets the next state of the state machine.
		virtual void SetState(std::unique_ptr<StateType> nextState, AdditionalArguments... additionalArguments) = 0;
	};
}

#endif // MACKIE_OF_THE_UNICORN_STATEMACHINE_H
